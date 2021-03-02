#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>


int main(int argc, char *argv[])
{
    int i, myid, ntasks;
    int size = 10000000;
    int *message;
    int *receiveBuffer;
    MPI_Status status;

    MPI_Win rma_window;

    double t0, t1;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    /* Allocate message */
    message = malloc(sizeof(int) * size);
    receiveBuffer = malloc(sizeof(int) * size);
    /* Initialize message */
    for (i = 0; i < size; i++)
        message[i] = myid;

    /* Print out the messages to be communicated */
    if (myid < ntasks - 1) {
        printf("Sender:   %d   # of elements: %d\n", myid, size);
    }

    /* Create RMA window */
    MPI_Win_create(message, size *  sizeof(int), sizeof(int),
                   MPI_INFO_NULL, MPI_COMM_WORLD, &rma_window);

    /* Start measuring the time spend in communication */
    MPI_Barrier(MPI_COMM_WORLD);
    t0 = MPI_Wtime();

    /* Send and receive messages */
    MPI_Win_fence(0, rma_window);
    if (myid > 0) {
        MPI_Get(receiveBuffer, size, MPI_INT, myid - 1, 0, size, MPI_INT,
                rma_window);
    }
    MPI_Win_fence(0, rma_window);

    /* Stop measuring the time */
    t1 = MPI_Wtime();

    /* Print out the messages that were communicated */
    if (myid > 0) {
        printf("Receiver: %d   first element: %d\n", myid, receiveBuffer[0]);
    }

    /* Print out the time spent in communication */
    MPI_Barrier(MPI_COMM_WORLD);
    fflush(stdout);
    printf("Time elapsed in rank %2d: %6.3f\n", myid, t1 - t0);

    free(message);
    free(receiveBuffer);
    MPI_Finalize();
    return 0;
}
