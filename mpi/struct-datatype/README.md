## Datatype for a struct / derived type

Start from the skeleton code for a program that sends an array of structures
(derived types in Fortran) between two tasks.

 1. Implement a user-defined datatype that can be used for sending the
	structured data and verify that the communication is performed
    successfully. Check the size and true extent of your type.
 2. Implement the same send by sending just a stream of bytes (type `MPI_BYTE`).
    Verify correctness and compare the performance of these two approaches.
