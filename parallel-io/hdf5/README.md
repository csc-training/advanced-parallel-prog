## HDF5 example

Study the HDF5 example at `parallel-io/hdf5`  where the case of Exercise “Simple
MPI I/O”  is written with HDF5 using collective parallel write. On Sisu, you
will need to load the module cray-hdf5-parallel before compilation:

```
module load cray-hdf5-parallel
```

Compile and run the program. You can use the `h5dump` command to check the
values in a HDF5 file.
