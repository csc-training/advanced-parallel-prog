/*
  This demo code creates a binary file that should look
  like this when run on least significant byte system and
  opened with a binary editor:

  87654321  0011 2233 4455 6677 8899 aabb ccdd eeff  0123456789abcdef
  00000000: 000a 080a 100a 180a 200b 280b 300b 380b  ........ .(.0.8.
  00000010: 010a 090a 110a 190a 210b 290b 310b 390b  ........!.).1.9.
  00000020: 020a 0a0a 120a 1a0a 220b 2a0b 320b 3a0b  ........".*.2.:.
  00000030: 030a 0b0a 130a 1b0a 230b 2b0b 330b 3b0b  ........#.+.3.;.
  00000040: 040c 0c0c 140c 1c0c 240d 2c0d 340d 3c0d  ........$.,.4.<.
  00000050: 050c 0d0c 150c 1d0c 250d 2d0d 350d 3d0d  ........%.-.5.=.
  00000060: 060c 0e0c 160c 1e0c 260d 2e0d 360d 3e0d  ........&...6.>.
  00000070: 070c 0f0c 170c 1f0c 270d 2f0d 370d 3f0d  ........'./.7.?.

  Here uppermost bytes denote the rank (0xA is rank 0, 0xB rank 1 and
  so on).
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <inttypes.h>
#include <mpi.h>

#define LOCALSIZE 4

int main(int argc, char *argv[])
{
    int my_id, ntasks;
    uint16_t localarray[LOCALSIZE][LOCALSIZE];
    int localsize = LOCALSIZE;
    int fullsize = 2*LOCALSIZE;

    MPI_File fh;
    MPI_Offset offset = 0;
    MPI_Datatype filetype;

    MPI_Comm cart_comm;
    int dims[2] = {2, 2};
    int periods[2] = {0, 0};
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
        for (int j = 0; j < localsize; j++) {
            localarray[i][j] = (i + coords[0]*localsize) +
                    fullsize * (j + coords[1]*localsize);
            // Create bit mask for upper bits according to the rank.
            // Rank 0 is 0xA, 1 is 0xB and so on.
            localarray[i][j] |= 0x0A00 + 0x0100 * my_id;
        }

    MPI_File_open(MPI_COMM_WORLD, "output.dat",
                  MPI_MODE_CREATE | MPI_MODE_WRONLY, MPI_INFO_NULL, &fh);

    // Write on line at the time
    for (int i = 0; i < localsize; i++) {
        offset = ((coords[0] * localsize + i) * fullsize +
                   coords[1] * localsize) * sizeof(uint16_t);
        MPI_File_write_at(fh, offset, localarray[i], localsize,
                          MPI_UINT16_T, MPI_STATUS_IGNORE);
    }
    MPI_File_close(&fh);

    MPI_Finalize();
    return 0;
}
