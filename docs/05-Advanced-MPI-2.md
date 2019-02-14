---
title:  Advanced User-defined datatypes
author: CSC Training
date:   2019-02
lang:   en
---


# MPI datatypes

MPI datatypes are used for communication purposes

  - Datatype tells MPI where to take the data when sending or where to
    put data when receiving

Elementary datatypes (MPI_INT, MPI_REAL, ...)

  - Different types in Fortran and C, correspond to languages basic
    types
  - Enable communication using contiguous memory sequence of identical
    elements (e.g. vector or matrix)


# User-defined datatypes

Use elementary datatypes as building blocks

Enable communication of

  - Non-contiguous data with a single MPI call, e.g. rows or columns of
    a matrix
  - Heterogeneous data (structs in C, types in Fortran)
  - Larger messages, count is int in C

Provide higher level of programming

  - Code is more compact and maintainable

Needed for getting the most out of MPI I/O


# User-defined datatypes

  - User-defined datatypes can be used both in point-to-point
    communication and collective communication
  - The datatype instructs where to take the data when sending or where
    to put data when receiving
  - Non-contiguous data in sending process can be received as contiguous
    or vice versa


# Using user-defined datatypes

A new datatype is created from existing ones with a datatype constructor

  - Several routines for different special cases

A new datatype must be committed before using it
MPI_Type_commit(newtype) newtype the new datatype to commit

A type should be freed after it is no longer needed


MPI_Type_free(newtype)

newtype the datatype for decommision


# Example: sending rows of a matrix in Fortran

FIXME: missing figure


```fortran
integer, parameter :: n=3, m=3
real, dimension(n,m) :: a
integer :: rowtype

! create a derived type
call mpi_type_vector(m, 1, n, mpi_real, rowtype, ierr)
call mpi_type_commit(rowtype, ierr)

! send a row
call mpi_send(a, 1, rowtype, dest, tag, comm, ierr)

! free the type after it is not needed
call mpi_type_free(rowtype, ierr)
```

# Datatype constructor examples

MPI_Type_contiguous
  : contiguous datatypes

MPI_Type_vector
  : regularly spaced datatype

MPI_Type_indexed
  : variably spaced datatype

MPI_Type_create_subarray
  : subarray within a multi-dimensional array

MPI_Type_create_hvector
  : like vector, but uses bytes for spacings

MPI_Type_create_hindexed
  : like index, but uses bytes for spacings

MPI_Type_create_struct
  : fully general datatype

Covered in the introductory course


# Understanding datatypes: typemap

A datatype is defined by a typemap

  - pairs of basic types and displacements (in bytes)
  - E.g. MPI_INT={(int,0)}

FIXME: missing figure?


# Datatype constructors: MPI_TYPE_CREATE_STRUCT

The most general type constructor, creates a new type from heterogeneous
blocks

  - E.g. Fortran types and C structures
  - Input is the typemap

FIXME: missing code?

```fortran
count=3, blocklens=(/2,2,1/), disps=(/0,3,9/)

types

newtype
```

# Datatype constructors: MPI_TYPE_CREATE_STRUCT

MPI_Type_create_struct(count, blocklens, displs, types, newtype)

count number of blocks
blocklens lengths of blocks (array)
displs displacements of blocks in bytes (array)
types types of blocks (array)

FIXME: missing code?

```fortran
count=3, blocklens=(/2,2,1/), disps= (/0,3,9/)

types

newtype
```


# Example: sending a C struct

```c
/* Structure for particles */

struct ParticleStruct {
    int charge;         /* particle charge */
    double coord[3];    /* particle coords */
    double velocity[3]; /* particle velocity vector components */
};

struct ParticleStruct particle[1000];
MPI_Datatype Particletype;

MPI_Datatype type[3]={MPI_INT, MPI_DOUBLE, MPI_DOUBLE};
int blocklen[3]={1,3,3};
MPI_Aint disp[3]={0, sizeof(double), 4*sizeof(double)};

...

MPI_Type_create_struct(3, blocklen, disp, type, &Particletype);
MPI_Type_commit(&Particletype);

MPI_Send(particle, 1000, Particletype, dest, tag, MPI_COMM_WORLD);

MPI_Type_free(&Particletype);
```

# Determining displacements

The previous example defines and assumes a certain alignment for the
data within the structure

The displacements can (and should!) be determined by using the function
MPI_Get_address(pointer, address)

  - The address of the variable is returned, which can then be used for
    determining relative displacements


# Determining displacements

```c
/* Structure for particles */
struct ParticleStruct {
    int charge;         /* particle charge */
    double coords[3];   /* particle coords */
    double velocity[3]; /* particle velocity vector components */
};

struct ParticleStruct particle[1000];
...

MPI_Aint disp[3];
MPI_Get_address(&particle[0].charge, &disp[0]);
MPI_Get_address(&particle[0].coords, &disp[1]);
MPI_Get_address(&particle[0].velocity, &disp[2]);

/* Make displacements relative */
disp[2] -= disp[0];
disp[1] -= disp[0];
disp[0] = 0;

...
```

Note the address type - MPI_Aint in C, integer(mpi_address_kind) in
Fortran


# Gaps between datatypes

Sending of an array of the ParticleStruct structures may have a
portability issue: it assumes that array elements are packed in memory

  - Implicit assumption: the extent of the datatype was the same as the
    size of the C struct
  - This is not necessarily the case

If there are gaps in memory between the successive structures, sending
does not work correctly


# type extent

FIXME: missing??


# Sending multiple elements: Extent

Sending multiple user-defined types at once may not behave as expected

The *lower bound* describes where the datatype starts

  - LB: min(dispj)

The *extent* describes the stride at which contiguous elements are read
or written when sending multiple elements

  - Extent = max(dispj + sizej) – LB + padding


# Multiple MPI_TYPE_VECTOR

FIXME: missing figures

MPI_Type_vector(count = 3, blocklen = 2, stride = 3, oldtype, newtype)

MPI_Send(buffer, count = 1, newtype, dest, tag, comm)

MPI_Send(buffer, count = 2, newtype, dest, tag, comm)


# Setting extent and lower bound

  - Read current extent and lower bound
  - Set new extent and lower bound


# Multiple MPI_TYPE_VECTOR

FIXME: missing figures

```
MPI_Type_vector(count = 3, blocklen = 2, stride = 3, oldtype, newtype)

MPI_Create_resized(newtype, lb = 0, extent = 9*sizeof(oldtype), n2type)

MPI_Send(buffer, count = 1, n2type, dest, tag, comm)

MPI_Send(buffer, count = 2, newtype, dest, tag, comm)
```


# Example: sending an array of structs portably

```c
struct ParticleStruct particle[1000];
MPI_Datatype particletype, oldtype;
MPI_Aint lb, extent;

...

/* Check that the extent is correct
MPI_Type_get_extent(particletype, &lb, &extent);
if ( extent != sizeof(particle[0] ) {
    oldtype = particletype;
    MPI_Type_create_resized(oldtype, 0, sizeof(particle[0]), &particletype);
    MPI_Type_commit(&particletype);
    MPI_Type_free(&oldtype);
}

...
```


# Other ways of communicating non-uniform data

```c
struct ParticleStruct particle[1000];
int psize;

psize = sizeof(particle[0]);

MPI_Send(particle, 1000*psize, MPI_BYTE, ...);
```

Non-contiguous data by manual packing

  - Copy data into or out from temporary buffer
  - Use MPI_Pack and MPI_Unpack functions
  - Performance will likely be an issue

Structures and types as continuous stream of bytes: Communicate
everything using MPI_BYTE

  - Portability can be an issue - be careful


# Summary

User-defined types enable communication of non-contiguous or
heterogeneous data with single MPI communication operations

  - Improves code readability & portability
  - Allows optimizations by the MPI runtime

This time we focused on the most general type specification:
MPI_Type_create_struct

Introduced the concepts of extent and typemap
