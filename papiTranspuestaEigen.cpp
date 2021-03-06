# include <iostream>
# include <cstdio>
# include <cstdlib>
# include <iostream>
# include <eigen3/Eigen/Dense>
# include "papi.h"

Eigen::MatrixXd code_to_be_measured(const Eigen::MatrixXd& m);
int main(int argc, char **argv)
{
  const int N = std::atoi(argv[1]);
  // Matrix declaration : Modeled as  nD vectors
  for(int ii= 0; ii< N ; ii+=30){
    // initialize matrices 
    Eigen::MatrixXd m = Eigen::MatrixXd::Random(ii,ii);
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
    Eigen::MatrixXd r = code_to_be_measured(m);

    if((retval=PAPI_flops_rate(PAPI_FP_OPS,&real_time, &proc_time, &flpops, &mflops))<PAPI_OK)
    {
      printf("retval: %d\n", retval);
      exit(1);
    }
      
    printf("Dimensíon_Matriz: %d Real_time: %f Proc_time: %f Total flpops: %lld MFLOPS: %f Suma: %.15e\n",
    ii,real_time, proc_time,flpops,mflops, r.sum());
    // Do something here, like computing the average of the resulting matrix, to avoid the optimizer deleting the code
  
    //printf("%.15e\n", r.sum());
  }
  return 0;
}

Eigen::MatrixXd code_to_be_measured(const Eigen::MatrixXd& m)
{
// simple matrix transpose
  Eigen::MatrixXd tr = m.transpose();
  return tr;
}

