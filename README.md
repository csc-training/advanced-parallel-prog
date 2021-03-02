# Advanced Parallel Programming

Exercise material and model answers for the CSC course "Advanced Parallel
Programming". The course is part of PRACE Advanced Training Center
(PATC) activity at CSC.

## Exercises

[General instructions](exercise-instructions.md)

### MPI & OpenMP recap

 - [Heat equation solver parallelized with OpenMP](openmp/heat)
 - [Heat equation solver parallelized with MPI](mpi/heat-p2p)

### Hybrid MPI+OpenMP programming

 - [Hybrid Hello World](hybrid/hello-world)
 - [Hybrid heat equation solver, part 1](hybrid/heat-fine)
 - [Multiple thread communication](hybrid/multiple-thread-communication)
 - [Hybrid heat equation solver, part 2](hybrid/heat-coarse)

### Advanced MPI

 - [Cartesian grid process topology](mpi/cartesian-grid)
 - [Datatype for a struct / derived type](mpi/struct-datatype)
 - [2D-decomposed heat equation](mpi/heat-2d)
 - [One-sided communication in a message chain](mpi/message-chain-one-sided)
 - [One-sided communication in the heat equation solver](mpi/heat-one-sided)

### Parallel I/O

 - [Parallel I/O with Posix](parallel-io/posix)
 - [Simple MPI-IO](parallel-io/mpi-io)
 - [HDF5 example](parallel-io/hdf5)
 - [Bonus: Checkpoint + restart with MPI-IO](parallel-io/heat-restart)
