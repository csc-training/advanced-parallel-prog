#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#include <mpi.h>


int main(int argc, char *argv[])
{
    int provided, rank, ntasks;
    int tid;

    /* TODO: Initialize MPI with thread support. Investigate different
     * thread support levels */

    /* Check the thread support level */
    if (provided == MPI_THREAD_MULTIPLE) {
        printf("MPI library supports MPI_THREAD_MULTIPLE\n");
    } else if (provided == MPI_THREAD_SERIALIZED) {
        printf("MPI library supports MPI_THREAD_SERIALIZED\n");
    } else if (provided == MPI_THREAD_FUNNELED) {
        printf("MPI library supports MPI_THREAD_FUNNELED\n");
    } else {
        printf("No multithreading support\n");
    }
    

    /* TODO: Find out the number of MPI tasks, MPI rank, and thread id,
     * and print out the results */


    MPI_Finalize();
    return 0;
}
