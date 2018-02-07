## 2D-decomposed heat equation

Create a two-dimensional Cartesian process topology for the halo exchange in
the heat equation. Parallelize the heat equation in two dimensions and utilize
user-defined datatypes in the halo exchange during the time evolution.

Hint: MPI contains also a contiguous datatype `MPI_Type_contiguous` that can be
used (together with `MPI_Type_Vector`) to construct the user-defined datatypes
for rows and columns to do the halo exchange in both x- and y-directions.

Utilize user-defined datatypes also in the I/O-related communication.
