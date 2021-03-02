## Simple MPI-IO

Implement parallel I/O in a test code using MPI-IO.

Write data from all MPI tasks to a single output file using MPI-IO. Each task
should write their own local part of the data directly to the correct position
in the file. Skeleton code to start from is available in `mpi-io.c` (or
`mpi-io.f90`).
