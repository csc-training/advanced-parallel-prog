#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

#define LEN 10000000

int main(int argc, char** argv)
{
  int rank, size;
  int provided;

  double *input, *output;

  double t0, t1;

  MPI_Init_thread(&argc, &argv, 0, &provided);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);

  input = (double *) malloc(LEN * sizeof(double));
  output =  (double *) malloc(LEN * sizeof(double));

  // Initialize
  for (int i=0; i < LEN; i++)
     input[i] = (rank+1)*i;

  t0 = MPI_Wtime();

  // Compute
#pragma omp parallel for
  for (int i=0; i < LEN; i++)
      output[i] = sqrt(input[i]) * 12.4*pow(i, 2.3);

  t1 = MPI_Wtime();
  
  
  printf("Time: %.5f\n", t1-t0);
  free(input);
  free(output);

  MPI_Finalize();

}
