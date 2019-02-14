---
title:  MPI reference
author: CSC Training
date:   2019-02
lang:   en
---


# C interfaces for the "first five" MPI operations

```c
int MPI_Init(int *argc, char **argv)

int MPI_Comm_size(MPI_Comm comm, int *size)

int MPI_Comm_rank(MPI_Comm comm, int *rank)

int MPI_Barrier(MPI_Comm comm)

int MPI_Finalize()
```


# Fortran interfaces for the "first five" MPI operations

```fortran
mpi_init(ierror)

mpi_comm_size(comm, size, ierror)

mpi_comm_rank(comm, rank, ierror)

mpi_barrier(comm, ierror)

mpi_finalize(ierror)

integer :: comm, size, rank, ierror
```


# C interfaces for the basic point-to-point operations

```c
int MPI_Send(void *buffer, int count, MPI_Datatype datatype,int dest, int tag, MPI_Comm comm)

int MPI_Recv( void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Status *status)

int MPI_Sendrecv(void *sendbuf, int sendcount, MPI_Datatype sendtype, int dest, int sendtag, void *recvbuf, int recvcount, MPI_Datatype recvtype, int source, int recvtag, MPI_Comm comm, MPI_Status *status)

int MPI_Get_count(MPI_Status *status, MPI_Datatype datatype, int *count)
```


# Fortran interfaces for the basic point-to-point operations

```fortran
mpi_send(buffer, count, datatype, dest, tag, comm, ierror)

type :: buf(*)

integer :: count, datatype, dest, tag, comm, ierror

mpi_recv(buf, count, datatype, source, tag, comm, status, ierror)

type :: buf(*)

integer :: count, datatype, source, tag, comm, ierror

integer :: status(MPI_STATUS_SIZE)

mpi_sendrecv(sendbuf, sendcount, sendtype, dest, sendtag, recvbuf, recvcount, recvtype, source, recvtag, comm, status, ierror)

type :: sendbuf(*), recvbuf(*)

integer :: sendcount, sendtype, dest, sendtag, recvcount, recvtype, source, recvtag, comm, ierror

integer :: status(MPI_STATUS_SIZE)
```


# MPI datatypes

MPI type
  : C type

MPI_CHAR
  : signed char

MPI_SHORT
  : short int

MPI_INT
  : int

MPI_LONG
  : long int

MPI_UNSIGNED_SHORT
  : unsigned short int

MPI_UNSIGNED_INT
  : unsigned int

MPI_UNSIGNED_LONG
  : unsigned long int

MPI_FLOAT
  : float

MPI_DOUBLE
  : double

MPI_LONG_DOUBLE
  : long double

MPI_BYTE


# MPI datatypes

MPI type
  : Fortran type

MPI_CHARACTER
  : character

MPI_INTEGER
  : integer

MPI_REAL
  : real

MPI_REAL8
  : real\*8   (non­standard)

MPI_DOUBLE_PRECISION
  : double precision

MPI_COMPLEX
  : complex

MPI_DOUBLE_COMPLEX
  : double complex

MPI_LOGICAL
  : logical

MPI_BYTE


# C interfaces for collective operations

```c
int MPI_Bcast(void* buffer, int count, MPI_datatype datatype, int root, MPI_Comm comm)

int MPI_Scatter(void* sendbuf, int sendcount, MPI_datatype sendtype, void* recvbuf, int recvcount, MPI_datatype recvtype, int root, MPI_Comm comm)

int MPI_Scatterv(void* sendbuf, int *sendcounts, int *displs, MPI_datatype sendtype, void* recvbuf, int recvcount, MPI_datatype recvtype, int root, MPI_Comm comm)

int MPI_Gather(void* sendbuf, int sendcount, MPI_datatype sendtype, void* recvbuf, int recvcount, MPI_datatype recvtype, int root, MPI_Comm comm)

int MPI_Gatherv(void *sendbuf, int sendcnt, MPI_Datatype sendtype, void *recvbuf, int *recvcnts, int *displs, MPI_Datatype recvtype, int root, MPI_Comm comm)
```


# C interfaces for collective operations

```c
int MPI_Reduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, int root, MPI_Comm comm)

int MPI_Allreduce(void* sendbuf, void* recvbuf, int count, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)

int MPI_Allgather(void* sendbuf, int sendcount, MPI_datatype sendtype, void* recvbuf, int recvcount, MPI_datatype recvtype, MPI_Comm comm)

int MPI_Reduce_scatter(void* sendbuf, void* recvbuf, int* recvcounts, MPI_Datatype datatype, MPI_Op op, MPI_Comm comm)

int MPI_Alltoall(void* sendbuf, int sendcount, MPI_datatype sendtype, void* recvbuf, int recvcount, MPI_datatype recvtype, MPI_Comm comm)

int MPI_Alltoallv(void* sendbuf, int *sendcounts, int *sdispls, MPI_Datatype sendtype, void* recvbuf, int *recvcounts, int *rdispls, MPI_Datatype recvtype,MPI_Comm comm)
```


# Fortran interfaces for collective operations

```fortran
mpi_bcast(buffer, count, datatype, root, comm, ierror)

type :: buffer(*) integer :: count, datatype, root, comm, ierror

mpi_scatter(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, ierror)

type :: sendbuf(*), recvbuf(*)

integer :: sendcount, recvcount, sendtype, recvtype, root, comm, ierror

mpi_scatterv(sendbuf, sendcounts, displs, sendtype, recvbuf, recvcount, recvtype, root, comm, ierror) *type* :: sendbuf(*), recvbuf(*) integer :: sendcounts(*), displs(*), recvcount, sendtype, recvtype, root, comm, ierror
```


# Fortran interfaces for collective operations

```fortran
mpi_gather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, root, comm, ierror)

*type* :: sendbuf(*), recvbuf(*)

integer :: sendcount, recvcount, sendtype, recvtype, root, comm, ierror

mpi_gatherv(sendbuf, sendcount, sendtype, recvbuf, recvcounts, displs, recvtype, root, comm, ierror) *type* :: sendbuf(*), recvbuf(*) integer :: sendcount, recvcounts(*), displs(*), sendtype, recvtype, root, comm, ierror

mpi_reduce(sendbuf, recvbuf, count, datatype, op, root, comm, ierror)

*type* :: sendbuf(*), recvbuf(*)

integer :: count, datatype, op, root, comm, ierror
```


# Fortran interfaces for collective operations

```fortran
mpi_allreduce(sendbuf, recvbuf, count, datatype, op, comm, ierror) *type* :: sendbuf(*), recvbuf(*) integer :: count, datatype, op, comm, ierror

mpi_allgather(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, ierror) *type* :: sendbuf(*), recvbuf(*)

integer :: sendcount, recvcount, sendtype, recvtype, comm, ierror

mpi_reduce_scatter(sendbuf, recvbuf, recvcounts, datatype, op, comm, ierror) *type* :: sendbuf(*), recvbuf(*)

integer :: recvcounts(*), datatype, op, comm, ierror

mpi_alltoall(sendbuf, sendcount, sendtype, recvbuf, recvcount, recvtype, comm, ierror) *type* :: sendbuf(*), recvbuf(*) integer :: sendcount, recvcount, sendtype, recvtype, comm, ierror
```


# Fortran interfaces for collective operations

```fortran
mpi_alltoallv(sendbuf,sendcounts, sdispls, sendtype, recvbuf, recvcounts, rdispls, recvtype, comm, ierror) *type* :: sendbuf(*), recvbuf(*)

integer :: sendcounts(*), recvcounts(*), sdispls(*), rdispls(*), sendtype, recvtype, comm, ierror
```


# Reduce operation

  - Available reduction operations (argument op)

MPI_MAX
  : Max value

MPI_MIN
  : Min value

MPI_SUM
  : Sum

MPI_PROD
  : Product

MPI_MAXLOC
  : Max value + location

MPI_MINLOC
  : Min value + location

MPI_LAND
  : Logical AND

MPI_BAND
  : Bytewise AND

MPI_LOR
  : Logical OR

MPI_BOR
  : Bytewise OR

MPI_LXOR
  : Logical XOR

MPI_BXOR
  : Bytewise

XOR


# C interfaces for user-defined communicators

```c
int MPI_Comm_split (MPI_Comm comm, int color, int key, MPI_Comm newcomm)

int MPI_Comm_compare (MPI_Comm comm1, MPI_Comm comm2, int result)

int MPI_Comm_dup ( MPI_Comm comm, MPI_Comm newcomm )

int MPI_Comm_free ( MPI_Comm comm )
```


# Fortran interfaces for user-defined communicators

```fortran
mpi_comm_split (comm, color, key, newcomm, ierror)

integer :: comm, color, key, newcomm, ierror

mpi_comm_compare ( comm1, comm2, result, ierror) integer :: comm1, comm2, result, ierror

mpi_comm_dup ( comm, newcomm, ierror) integer :: comm, newcomm, ierror

mpi_comm_free ( comm, ierror) integer :: comm, ierror
```


# C interfaces for non-blocking operations

```c
int MPI_Isend( void *buf, int count, MPI_Datatype datatype, int dest, int tag, MPI_Comm comm, MPI_Request *request )

int MPI_Irecv( void *buf, int count, MPI_Datatype datatype, int source, int tag, MPI_Comm comm, MPI_Request *request )

int MPI_Wait(MPI_Request *request, MPI_Status *status)

int MPI_Waitall(int count, MPI_Request *array_of_requests, MPI_Status *array_of_statuses)
```


# Fortran interfaces for non-blocking operations

```fortran
mpi_isend(buf, count, datatype, dest, tag, comm, request,ierror)

*type* :: buf(*)

integer :: count, datatype, dest, tag, comm, request, ierror

mpi_irecv(buf, count, datatype, source, tag, comm, request,ierror)

*type* :: buf(*)

integer :: count, datatype, source, tag, comm, request, ierror

mpi_wait(request, status, ierror)

integer :: request, status(mpi_status_size), ierror

mpi_waitall(count, array_of_requests, array_of_statuses, ierror)

integer :: count, array_of_requests(:), array_of_statuses(mpi_status_size,:), ierror
```


# C interfaces for Cartesian process topologies

```
int MPI_Cart_create(MPI_Comm old_comm, int ndims, int *dims, int *periods, int reorder, MPI_Comm *comm_cart)

int MPI_Cart_coords(MPI_Comm comm, int rank, int maxdim, int *coords)

int MPI_Cart_rank(MPI_Comm comm, int *coords, int rank)

int MPI_Cart_shift( MPI_Comm comm, int direction, int displ, int *low, int *high )
```


# Fortran interfaces for Cartesian process topologies

```fortran
mpi_cart_create(old_comm, ndims, dims, periods, reorder, comm_cart, ierror) integer :: old_comm, ndims, dims(:), comm_cart, ierror

logical :: reorder, periods(:)

mpi_cart_coords(comm, rank, maxdim, coords, ierror) integer :: comm, rank, maxdim, coords(:), ierror

mpi_cart_rank(comm, coords, rank, ierror) integer :: comm, coords(:), rank, ierror

mpi_cart_shift(comm, direction, displ, low, high, ierror) integer :: comm, direction, displ, low, high, ierror
```


# C interfaces for datatype routines

```
int MPI_Type_commit(MPI_Datatype *type)

int MPI_Type_free(MPI_Datatype *type)

int MPI_Type_contiguous(int count, MPI_Datatype oldtype, MPI_Datatype *newtype)

int MPI_Type_vector(int count, int block, int stride, MPI_Datatype oldtype, MPI_Datatype *newtype)

int MPI_Type_indexed(int count, int blocks[], int displs[], MPI_Datatype oldtype, MPI_Datatype *newtype)

int MPI_Type_create_subarray(int ndims, int array_of_sizes[], int array_of_subsizes[], int array_of_starts[], int order, MPI_Datatype oldtype, MPI_Datatype *newtype )

int MPI_Type_create_struct(int count, const int array_of_blocklengths[], const MPI_Aint array_of_displacements[], const MPI_Datatype array_of_types[], MPI_Datatype *newtype)
```


# Fortran interfaces for datatype routines

```fortran
mpi_type_commit(type, ierror) integer :: type, ierror

mpi_type_free(type, ierror) integer :: type, ierror

mpi_type_contiguous(count, oldtype, newtype, ierror) integer :: count, oldtype, newtype, ierror

mpi_type_vector(count, block, stride, oldtype, newtype, ierror) integer :: count, block, stride, oldtype, newtype, ierror

mpi_type_indexed(count, blocks, displs, oldtype, newtype, ierror) integer :: count, oldtype, newtype, ierror integer, dimension(count) :: blocks, displs

mpi_type_create_subarray(ndims, sizes, subsizes, starts, order, oldtype, newtype, ierror) integer :: ndims, order, oldtype, newtype, ierror integer, dimension(ndims) :: sizes, subsizes, starts

mpi_type_create_struct(count, blocklengths, displacements, types, newtype, ierror) integer :: count, blocklengths(count), types(count), newtype, ierror integer(kind=mpi_address_kind) :: displacements(count)
```


# C interfaces for one-sided routines

```c
int MPI_Win_create(void *base, MPI_Aint size, int disp_unit, MPI_Info info, MPI_Comm comm, MPI_Win *win)

int MPI_Win_fence(int assert, MPI_Win win)

int MPI_Put(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win)

int MPI_Get(void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Win win)

int MPI_Accumulate(const void *origin_addr, int origin_count, MPI_Datatype origin_datatype, int target_rank, MPI_Aint target_disp, int target_count, MPI_Datatype target_datatype, MPI_Op op, MPI_Win win)
```


# Fortran interfaces for one-sided routines

```fortran
mpi_win_create(base, size, disp_unit, info, comm, win, ierror) <type> :: base(*) integer(kind=mpi_address_kind) :: size integer :: disp_unit, info, comm, win, ierror

mpi_win_fence(assert, win, ierror) integer :: assert, win, ierror

mpi_put(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, ierror) <type> :: origin_addr(*) integer(kind=mpi_address_kind) :: target_disp integer :: origin_count, origin_datatype, target_rank, target_count, target_datatype, win, ierror
```


# Fortran interfaces for one-sided routines

```fortran
mpi_get(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, win, ierror) <type> :: origin_addr(*) integer(kind=mpi_address_kind) :: target_disp integer :: origin_count, origin_datatype, target_rank, target_count, target_datatype, win, ierror

mpi_accumulate(origin_addr, origin_count, origin_datatype, target_rank, target_disp, target_count, target_datatype, op, win, ierror) <type> :: origin_addr(*) integer(kind=mpi_address_kind) :: target_disp integer :: origin_count, origin_datatype, target_rank, target_count, target_datatype, op, win, ierror
```


# C interfaces to MPI I/O routines

```c
int MPI_File_open(MPI_Comm comm, char *filename, int amode, MPI_Info info, MPI_File *fh)

int MPI_File_close(MPI_File *fh)

int MPI_File_seek(MPI_File fh, MPI_Offset offset, int whence)

int MPI_File_read(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)

int MPI_File_read_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)

int MPI_File_write(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)

int MPI_File_write_at(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
```


# C interfaces to MPI I/O routines

```c
int MPI_File_set_view(MPI_File fh, MPI_Offset disp, MPI_Datatype etype, MPI_Datatype filetype, char *datarep, MPI_Info info)

int MPI_File_read_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)

int MPI_File_read_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)

int MPI_File_write_all(MPI_File fh, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)

int MPI_File_write_at_all(MPI_File fh, MPI_Offset offset, void *buf, int count, MPI_Datatype datatype, MPI_Status *status)
```


# Fortran interfaces for MPI I/O routines

```fortran
mpi_file_open(comm, filename, amode, info, fh, ierror) integer :: comm, amode, info, fh, ierror character* :: filename

mpi_file_close(fh, ierror)

mpi_file_seek(fh, offset, whence, ierror)

integer :: fh, whence, ierror

integer(kind=MPI_OFFSET_KIND) :: offset

mpi_file_read(fh, buf, count, datatype, status, ierror)

mpi_file_write(fh, buf, count, datatype, status, ierror)

integer :: fh, count, datatype, status(mpi_status_size)

*type* :: buf(*)

mpi_file_read_at(fh, offset, buf, count, datatype, status, ierror)

mpi_file_write_at(fh, offset, buf, count, datatype, status, ierror) integer :: fh, offset, buf, count, datatype, status(mpi_status_size)
```


# Fortran interfaces for MPI I/O routines

```fortran
mpi_file_set_view(fh, disp, etype, filetype, datarep, info, ierror) integer :: fh, etype, filetype, info, ierror

integer(kind=MPI_OFFSET_KIND) :: disp character* :: datarep

mpi_file_read_all(fh, buf, count, datatype, status, ierror)

mpi_file_write_all(fh, buf, count, datatype, status, ierror)

integer :: fh, count, datatype, status(MPI_STATUS_SIZE), ierror

*type* :: buf(*)

mpi_file_read_at_all(fh, offset, buf, count, datatype, status, ierror)

mpi_file_write_at_all(fh, offset, buf, count, datatype, status, ierror)

integer :: fh, count, datatype, status(MPI_STATUS_SIZE), ierror

integer(kind=MPI_OFFSET_KIND) :: offset

*type* :: buf(*)
```
