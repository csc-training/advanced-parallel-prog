program hybridhello
  use omp_lib
  implicit none
  include 'mpif.h'
  integer :: provided, my_id, ntask, tid, rc

  ! TODO: Initialize MPI with thread support. Investigate different
  ! thread support levels

  if (provided == MPI_THREAD_MULTIPLE) then
     write(*,*) 'MPI library supports MPI_THREAD_MULTIPLE'
  else if (provided == MPI_THREAD_SERIALIZED) then
     write(*,*) 'MPI library supports MPI_THREAD_SERIALIZED'
  else if (provided == MPI_THREAD_FUNNELED) then
     write(*,*) 'MPI library supports MPI_THREAD_FUNNELED'
  else
     write(*,*) 'No multithreading support'
  end if

  ! TODO: Find out the number of MPI tasks, MPI rank, and thread id,
  ! and print out the results

  call MPI_Finalize(rc)

end program hybridhello
