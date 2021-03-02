## Heat equation solver hybridized with MPI+OpenMP

Implement a hybrid MPI+OpenMP heat equation solver using OpenMP to parallelize
the kernel loops.

Refer back to the two OpenMP-parallelized implementations of the
[heat equation solver](../../openmp/heat), and combine the loop-level
parallelization with an MPI implementation of the solver, e.g.
[heat-p2p](../../mpi/heat-p2p). All MPI communication is handled by the
main process (no OpenMP threads active), i.e. using the
MPI_THREAD_FUNNELED mode.
