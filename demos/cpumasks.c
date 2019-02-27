#define _GNU_SOURCE
#include <stdio.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <sched.h>
#include <mpi.h>
#include <math.h>

#ifdef _OPENMP
#include <omp.h>
#endif

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

void print_mask(int rank)
{
    int i, mythread, thread_turn, nthreads, nrcpus = 1024;
    cpu_set_t *mask;
    size_t size;
    char hostname[HOST_NAME_MAX];

    if ((gethostname(hostname, HOST_NAME_MAX) != 0)) {
        printf("Could not read host name!\n");
    }

#pragma omp parallel private(mask, size, mythread, i, nthreads, thread_turn)
    {
#ifdef _OPENMP
        mythread = omp_get_thread_num();
        nthreads = omp_get_num_threads();
#else
        mythread = 0;
        nthreads = 1;
#endif

        for (thread_turn = 0; thread_turn < nthreads; thread_turn++) {
#pragma omp barrier
            if (mythread == thread_turn) {
              realloc:
                mask = CPU_ALLOC(nrcpus);
                size = CPU_ALLOC_SIZE(nrcpus);
                CPU_ZERO_S(size, mask);
                if (sched_getaffinity(0, size, mask) == -1) {
                    CPU_FREE(mask);
                    if (errno == EINVAL && nrcpus < (1024 << 8)) {
                        nrcpus = nrcpus << 2;
                        printf("nrcpus: %i\n", nrcpus);
                        goto realloc;
                    }
                    perror("sched_getaffinity");
                }

                printf("%s: task %4i, thread %2i, ccount %2i, cores: ",
                       hostname, rank, mythread, CPU_COUNT_S(size, mask));
                for (i = 0; i < nrcpus; i++) {
                    if (CPU_ISSET_S(i, size, mask)) {
                        printf("%2i ", i);
                    }
                }
                printf("\n");

                CPU_FREE(mask);
            }
#pragma omp barrier
        }
    }                           /* end of task specific part */
}


int main(int argc, char *argv[])
{
    int rank, ntasks;
    int provided, turn_rank;

    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);

    if (provided < MPI_THREAD_FUNNELED) {
        printf("Thread funneled not supported!\n");
        MPI_Abort(MPI_COMM_WORLD, -1);
    }

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);

    for (turn_rank = 0; turn_rank < ntasks; turn_rank++) {

        MPI_Barrier(MPI_COMM_WORLD);

        if (rank == turn_rank) {
            print_mask(rank);
        }
        fflush(stdout);
        MPI_Barrier(MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
}
