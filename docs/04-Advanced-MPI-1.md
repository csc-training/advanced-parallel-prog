---
title:  MPI Process topologies
author: CSC Training
date:   2019-02
lang:   en
---


# Process topologies

- MPI process topologies allow for simple referencing scheme of processes
    - Process topology defines a new communicator
    - We will focus on Cartesian topologies, although graph topologies are
      also supported
- MPI topologies are virtual
    - No relation to the physical structure of the computer
    - Data mapping "more natural" only to the programmer
- Usually no performance benefits
    - But code becomes more compact and readable


# Two dimensional domain decomposition

![](img/two-d-cartesian-grid.svg){width=50%}


# Communicator in Cartesian grid: MPI_Cart_create {.split-definition}

`MPI_Cart_create(oldcomm, ndims, dims, periods, reorder, newcomm)`
  : `oldcomm` {.input}
    : communicator

    `ndims` {.input}
    : number of dimensions

    `dims` {.input}
    : integer array (size ndims) that defines the number of processes in each
      dimension

    `periods` {.input}
    : array that defines the periodicity of each dimension

    `reorder` {.input}
    : is MPI allowed to renumber the ranks

    `newcomm` {.output}
    : new Cartesian communicator


# Translating rank to coordinates

- Checking the Cartesian communication topology coordinates for a
  specific rank

`MPI_Cart_coords(comm, rank, maxdim, coords)`
  : `comm` {.input}
    : Cartesian communicator
  : `rank` {.input}
    : rank to convert
  : `maxdim` {.input}
    : dimension of coords
  : `coords` {.output}
    : coordinates in Cartesian topology that corresponds to rank


# Translating coordinates to rank

- Checking the rank of the process at specific Cartesian communication
  topology coordinates

`MPI_Cart_rank(comm, coords, rank)`
  : `comm` {.input}
    : Cartesian communicator
  : `coords` {.input}
    : array of coordinates
  : `rank` {.output}
    : a rank corresponding to coords


# Creating a Cartesian communication topology

```fortran
dims(1)=4
dims(2)=4
period=(/ .true., .true. /)

call mpi_cart_create(mpi_comm_world, 2, dims, period, .true., comm2d, rc)
call mpi_comm_rank(comm2d, my_id, rc)
call mpi_cart_coords(comm2d, my_id, 2, coords, rc)
```


# How to communicate in a Cartesian topology

`MPI_Cart_shift(comm, direction, displ, source, dest)`
  : `comm` {.input}
    : Cartesian communicator
  : `direction` {.input}
    : shift direction (0 or 1 in 2D)
  : `displ` {.input}
    : shift displacement (1 for next cell etc, < 0 for source from "down"/"right" directions)
  : `source` {.output}
    : rank of source process
  : `dest` {.output}
    : rank of destination process

- "Shifts" (steps) within the grid define sources/destinations


# How to communicate in a Cartesian topology

- Note! *Both* `source` and `dest` are *output* parameters. The
  coordinates of the calling task is implicit input.
- With a non-periodic grid, source or dest can land outside of the grid;
  then `MPI_PROC_NULL` is returned.


# Halo exchange

```fortran
call mpi_cart_shift(comm2d, 0, 1, nbr_up, nbr_down, rc)
call mpi_cart_shift(comm2d, 1, 1, nbr_left, nbr_right, rc)
...

! left boundaries: send to left, receive from right
call mpi_sendrecv(buf(1,1), 1, coltype, nbr_left, &
    tag_left, buf(1,n+1), 1, coltype, nbr_right, &
    tag_left, comm2d, mpi_status_ignore, rc)

! right boundaries: send to right, receive from left
...
! top boundaries: send to above, receive from below
call mpi_sendrecv(buf(1,1), 1, rowtype, nbr_up, &
    tag_up, buf(n+1,1), 1, rowtype, nbr_down, &
    tag_up, comm2d, mpi_status_ignore, rc)

! bottom boundaries: send to below, receive from above
...
```

# Summary

- Process topologies provide a convenient referencing scheme for grid-like
  decompositions
- Usage pattern
    - Define a process grid with `MPI_Cart_create`
    - Use the obtained new communicator as the comm argument in communication
      routines
        - For getting the ranks of the neighboring processes, use
          `MPI_Cart_shift` or wrangle with `MPI_Cart_coords` and
          `MPI_Cart_rank`
