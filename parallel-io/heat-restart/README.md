## Checkpoint/restart with MPI I/O

Add a feature to the heat equation solver program that enables one to start
the program from a completed situation (i.e. not from scratch every time). This
checkpointing will dump the situation of the simulation to disk (e.g.) after
every few tens of iterations; in a form that can be read in afterwards. If a checkpoint
file is present, the program will replace the initial state with the one in the
restart file. Use MPI I/O to accomplish this.
