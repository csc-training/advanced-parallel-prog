## General exercise instructions

For most of the exercises, skeleton codes are provided both for Fortran and C in the corresponding subdirectory. Some exercise skeletons have sections marked with "TODO" for completing the exercises. In addition, all of the exercises have exemplary full codes (that can be compiled and run) in the `solutions` folder. Note that these are seldom the only or even the best way to solve the problem.

The exercise material can be downloaded with the command

```
git clone https://github.com/csc-training/advanced-parallel-prog.git
```

If you have a GitHub account you can also **Fork** this repository and clone then your fork.

### Computing servers
We will use the CSC's Puhti supercomputer. See [here](https://docs.csc.fi/support/tutorials/puhti_quick/) for genera instructins on using Puhti.

Log onto Puhti using the provided username and password, for example

```
ssh -Y training000@puhti.csc.fi
```

For editing program source files you can use e.g. *nano* editor :

```
nano prog.f90
```
(`^` in nano's shortcuts refer to **Ctrl** key, *i.e.* in order to save file and exit editor press `Ctrl+X`).
Also other editors  are available.

In case you have working parallel program development environment in yourlaptop (Fortran or C compiler, MPI development library, etc.) you may also use that.

## Compilation and execution
Compilation of the source codes is performed with the `mpif90` and `mpicc` wrapper commands:
```
mpif90 -o my_mpi_exe prog.f90
```
or
```
mpicc -o my_mpi_exe prog.c
```

The wrapper commands include automatically all the flags needed for building MPI programs.


### Batch jobs
Larger and/or longer runs should be submitted via the batch system. An example batch job script (a text file, let's call it `test_job.sh`) for a MPI job with 4 processes looks like this:

```
#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=<project>
#SBATCH --partition=small
#SBATCH --reservation=training
#SBATCH --time=00:05:00
#SBATCH --ntasks=4

srun my_mpi_exe
```

The batch script is then submitted with the sbatch command as
```
sbatch test_job.sh
```
Replace `<project>` with the project id provided together with your access credentials. Save the script *e.g.* as `job.sh` and submit it with `sbatch job.sh`.  The output of job will be in file `slurm-xxxxx.out`. You can check the status of your jobs with `squeue -u $USER` and kill possible hanging applications with `scancel JOBID`.


#### Running in local workstation

In most MPI implementations parallel program can be started with the `mpiexec` launcher:
```
mpiexec -n 4 ./my_mpi_exe
```

### OpenMP

OpenMP programs can be compiled adding the `-fopenmp`
flag:
```
mpif90 -o my_omp_exe -fopenmp test.f90
```
or
```
mpicc -o my_omp_exe -fopenmp test.c
```
(With the default Intel compiler one can use also the serial compiler commands `ifort` and `icc`).

#### Running in Puhti

When running OpenMP programs via the batch job system, one needs to use the `--cpus-per-task` Slurm option and the `OMP_NUM_THREADS` environment variable. 
Simple job running with 4 OpenMP threads can be submitted with the following batch job script:
```
#!/bin/bash
#SBATCH --job-name=example
#SBATCH --account=<project>
#SBATCH --partition=small
#SBATCH --reservation=training
#SBATCH --time=00:05:00
#SBATCH --ntasks=1
#SBATCH --cpus-per-task=4

export OMP_NUM_THREADS=$SLURM_CPUS_PER_TASK
srun my_omp_exe
```

A hybrid MPI+OpenMP could be launched by increasing the value of `--ntasks`.

#### Running in local workstation

The number of threads for OpenMP programs can be specified with `OMP_NUM_THREADS` directly in command line: 

```
OMP_NUM_THREADS=4 ./my_omp_exe
```

Similarly, a hybrid MPI+OpenMP would be invoked for example as
```
export OMP_NUM_THREADS=4 
mpiexec -n 4 ./my_hybrid_exe
```
