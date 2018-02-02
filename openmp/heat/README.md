## Heat equation solver parallelized with OpenMP

A serial source code for the heat equation solver can be found under
openmp/heat/ in separate directories for C and Fortran.

 * Parallelize the serial heat equation solver with OpenMP by parallelizing
   the loops in the routines for data initialization (initialize) and time 
   evolution (evolve).

 * Improve the OpenMP parallelization such that the parallel region is opened
   and closed only once during the program execution. 


