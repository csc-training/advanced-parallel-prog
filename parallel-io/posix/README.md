## Parallel I/O with Posix

Implement parallel I/O in a test code using MPI and normal I/O calls.

1. Write data from all MPI tasks to a single file using the spokesman
   strategy, i.e. gather data to a single MPI task and write it to a file.
   The data should be kept in the order of the MPI ranks. You may start from
   the skeleton code in `c/spokesman.c` (or `fortran/spokesman.F90`).

2. Verify the above write by reading the file using the same spokesman
   strategy, but with a different number of MPI tasks than in writing.
   Skeleton code to start from is available in `c/spokesman_reader.c` (or
   `fortran/spokesman_reader.F90`).

3. Re-implement the write code so that all the MPI tasks write into separate
   files (aka "every man for himself" strategy).
