## Parallel I/O with Posix

a) Write data from all MPI tasks to a single file using the spokesman
strategy, i.e. gather data to a single MPI task and write it to a file. The
data should be kept in the order of the MPI ranks. You may start from the
skeleton code in `parallel-io/posix/`

b) Verify the above write by reading the file using the spokesman strategy.
Use different number of MPI tasks than in writing.

c) Implement the above write so that all the MPI tasks write in to separate
files (this was the “every man for himself” strategy).

