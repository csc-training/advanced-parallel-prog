## One-sided communication in a message chain

Write a simple program where every MPI task communicates data with its
neighbouring tasks.

Let *ntasks* be the number of the tasks, and *myid* the rank of the
current process. Your program should work as follows:

- Every task (except the last one, i.e. rank *ntasks*-1) sends a message to
  the next task (rank *myid*+1). For example, task 0 sends a message to
  task 1.
- All tasks (except rank 0) receive a message.
- The message content should be an integer array where each element is
  initialized to *myid*.
- Each sender prints out their rank and the number of elements it sends.
- Each receiver prints out their rank and the first element in the received
  array.

1. Implement the program described above using MPI_Put
2. Implement the program described above using MPI_Get

Skeleton code to start from is available in `c/skeleton.c` (or
`fortran/skeleton.F90`).
