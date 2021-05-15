
# include <iostream>
# include <cstdio>
# include <cstdlib>
# include "papi.h"
#include <armadillo>
using namespace std;
using namespace arma;
mat code_to_be_measured(const mat& m,const mat& n);
int main(int argc, char **argv)
{
const int N = std::atoi(argv[1]);
for(int ii = 0; ii < N; ii++){

// Matrix declaration : Modeled as  nD vectors

// initialize matrices
  mat A(ii, ii, fill::randu);
  mat B(ii,ii, fill::randu);
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
mat b = code_to_be_measured(A,B);
double suma = accu(b);
if((retval=PAPI_flops_rate(PAPI_FP_OPS,&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
{
printf("retval: %d\n", retval);
exit(1);
}
printf("Real_time: %f Proc_time: %f Total flpops: %lld MFLOPS: %f\n",
real_time, proc_time,flpops,mflops);
// Do something here, like computing the average of the resulting matrix, to avoid the optimizer deleting the code
printf("%.15e\n", b);
}
return 0;
}

mat code_to_be_measured(const mat& m,const mat& n)
{
mat multi = m*n;
return multi;
}

    