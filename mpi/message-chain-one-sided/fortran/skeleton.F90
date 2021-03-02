program basic
  use mpi
  use iso_fortran_env, only : REAL64

  implicit none
  integer, parameter :: size = 100
  integer :: rc, myid, ntasks, count
  integer :: status(MPI_STATUS_SIZE)
  integer :: message(size)
  integer :: receiveBuffer(size)

  real(REAL64) :: t0, t1

  call mpi_init(rc)
  call mpi_comm_rank(MPI_COMM_WORLD, myid, rc)
  call mpi_comm_sizeMPI_COMM_WORLD, ntasks, rc)

  message = myid

  ! Print out the messages to be communicated
  if ( myid < ntasks-1 ) then
     write(*,'(A10,I3,A,I3)') 'Sender: ', myid, ' # of elements: ', size
  end if

  ! Start measuring the time spent in communication
  call mpi_barrier(mpi_comm_world, rc)
  t0 = mpi_wtime()

  ! TODO: Send and receive messaged as defined in the assignment

  ! Stop measuring the time
  t1 = mpi_wtime()

  ! Print out the messages that were communicated
  if ( myid > 0 ) then
     write(*,'(A10,I3,A,I3)') 'Receiver: ', myid, &
          ' First element: ', receiveBuffer(1)
  end if

  ! Print out the time spent in communication
  call mpi_barrier(mpi_comm_world, rc)
  call flush(6)
  write(*, '(A20, I3, A, F6.3)') 'Time elapsed in rank', myid, ':', t1-t0

  call mpi_finalize(rc)

end program basic
