#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <mpi.h>

#define LOCALSIZE 4

int main(int argc, char *argv[])
{
    int my_id, ntasks;
    int localarray[LOCALSIZE][LOCALSIZE];
    int localsize = LOCALSIZE;
    int fullsize = 2*LOCALSIZE;

    MPI_File fh;
    MPI_Offset offset = 0;
    MPI_Datatype filetype;

    MPI_Comm cart_comm;
    int dims[2] = {2, 2};
    int periods[2] = {0,0};
    int coords[2];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ntasks);
    if (ntasks != 4) {
      printf("This example works only with 4 MPI tasks!\n");
      MPI_Abort(MPI_COMM_WORLD, -1); 
    }

    // Create cartesian communicator
    MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, 0, &cart_comm);
    MPI_Comm_rank(cart_comm, &my_id);
    MPI_Cart_coords(cart_comm, my_id, 2, coords);

    // Generate local data
    for (int i = 0; i < localsize; i++)
      for (int j = 0; j < localsize; j++)
        localarray[i][j] = (i + coords[0]*localsize) * 10 + j + 
                            coords[1] * localsize;

    MPI_File_open(MPI_COMM_WORLD, "output.dat",
                  MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

    // Write on line at the time
    for (int i = 0; i < localsize; i++) {
      offset = ((coords[0] * localsize + i) * fullsize + 
                coords[1] * localsize) * sizeof(int);
      MPI_File_write_at(fh, offset, localarray[i], localsize, MPI_INT,
                        MPI_STATUS_IGNORE);
    }
    MPI_File_close(&fh);

    MPI_Finalize();
    return 0;
}
