# include <iostream>
# include <cstdio>
# include <cstdlib>
# include "papi.h"

int code_to_be_measured(const double * M, double * MT,const int N);
int main(int argc, char **argv)
{

        double suma;  
        const int a = std::atoi(argv[1]);

        for(int N=0;N<=a;N+=30){
            // Matrix declaration : Modeled as 1D array
            // Declare as pointers and ask for memory to use the heap
            double *A = new double [N*N], *AT = new double [N*N];
            // initialize matrices
            for (int ii = 0; ii < N; ++ii) {
                for (int jj = 0; jj < N; ++jj) {
                    A[ii*N + jj] = ii + jj + 0.99+rand() % 100;
                    AT[ii*N + jj] = 0.0;
                }
            }
            // PAPI vars
            float real_time, proc_time,mflops;
            long long flpops;
            float ireal_time, iproc_time, imflops;
            long long iflpops;
            int retval;
            // PERFOMANCE MEASURE
            // start PAPI counters
            if((retval=PAPI_flops_rate(PAPI_FP_OPS,&ireal_time,&iproc_time,&iflpops,&imflops)) < PAPI_OK)
            {
            printf("Could not initialise PAPI_flops \n");
            printf("Your platform may not support floating point operation event.\n");
            printf("retval: %d\n", retval);
            exit(1);
            }
            code_to_be_measured(A, AT, N);
            if((retval=PAPI_flops_rate(PAPI_FP_OPS,&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
            {
            printf("retval: %d\n", retval);
            exit(1);
            }
            printf("Dimensíon_Matriz: %d Real_time: %f Proc_time: %f Total flpops: %lld MFLOPS: %f Suma: %lf\n",
            N,real_time, proc_time,flpops,mflops,suma);
            // Do something here, like computing the average of the resulting matrix, to avoid the optimizer deleting the code
            //printf("%.15e\n", AT[0]);

            for (int ii = 0; ii < N; ++ii) {
            for (int jj = 0; jj < N; ++jj) {
                suma += AT[ii*N +jj]; // use temporal floating point operation to count mflops
            }
            }
            delete [] A;
            delete [] AT;
        }
            return 0;
    }
        
    int code_to_be_measured(const double * M, double * MT, const int N)
    {
        // simple matrix transpose
        for (int ii = 0; ii < N; ++ii) {
        for (int jj = 0; jj < N; ++jj) {
            MT[ii*N +jj] = 2.3456*M[jj*N + ii]; // use temporal floating point operation to count mflops
        }
            
        }
        return 0;
    }