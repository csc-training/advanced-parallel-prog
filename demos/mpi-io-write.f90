program mpiio
  use mpi
  use, intrinsic :: iso_fortran_env, only : error_unit, output_unit
  implicit none

  integer, parameter :: datasize = 64
  integer :: rc, my_id, ntasks, localsize, i
  integer, dimension(:), allocatable :: localvector
  integer :: fh, dsize
  integer(kind=MPI_OFFSET_KIND) :: offset

  call mpi_init(rc)
  call mpi_comm_size(mpi_comm_world, ntasks, rc)
  call mpi_comm_rank(mpi_comm_world, my_id, rc)

  localsize = datasize / ntasks
  allocate(localvector(localsize))

  localvector = [(i + my_id * localsize, i=1,localsize)]

  call mpi_type_size(MPI_INTEGER, dsize, rc)
  offset = my_id * localsize * dsize

  call mpi_file_open(MPI_COMM_WORLD, 'output.dat', &
       & MPI_MODE_CREATE+MPI_MODE_WRONLY, MPI_INFO_NULL, fh, rc)
  call mpi_file_write_at_all(fh, offset, localvector, localsize, &
       & MPI_INTEGER, MPI_STATUS_IGNORE, rc)
  call mpi_file_close(fh, rc)

  deallocate(localvector)
  call mpi_finalize(rc)

end program mpiio
