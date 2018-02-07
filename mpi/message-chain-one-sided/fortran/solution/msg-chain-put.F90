program basic
  use mpi
  use iso_fortran_env, only : REAL64

  implicit none
  integer, parameter :: size = 100
  integer :: rc, myid, ntasks, count
  integer :: status(MPI_STATUS_SIZE)
  integer :: message(size)
  integer :: receiveBuffer(size)

  integer :: integer_size
  integer(kind=MPI_ADDRESS_KIND) :: win_size  
  integer(kind=MPI_ADDRESS_KIND) :: disp = 0
  integer :: rma_window  ! RMA window for one-sided communication

  real(REAL64) :: t0, t1 

  call mpi_init(rc)
  call mpi_comm_rank(MPI_COMM_WORLD, myid, rc)
  call mpi_comm_size(MPI_COMM_WORLD, ntasks, rc)

  message = myid


  call mpi_type_size(MPI_INTEGER, integer_size, rc)
  win_size = size * integer_size
  call mpi_win_create(receiveBuffer, win_size, integer_size, &
       &              MPI_INFO_NULL, MPI_COMM_WORLD, rma_window, rc)

  ! Start measuring the time spent in communication
  call mpi_barrier(mpi_comm_world, rc)
  t0 = mpi_wtime()

  ! TODO: Send and receive as defined in the assignment

  call mpi_win_fence(0, rma_window, rc)

  if ( myid < ntasks-1 ) then
     call mpi_put(message, size, MPI_INTEGER, myid + 1, disp, &
          &       size, MPI_INTEGER, rma_window, rc)

     write(*,'(A10,I3,A20,I8,A,I3,A,I3)') 'Sender: ', myid, &
          ' Sent elements: ',size, &
          '. Tag: ', myid+1, '. Receiver: ', myid+1
  end if

  call mpi_win_fence(0, rma_window, rc)

  if ( myid > 0 ) then
     write(*,'(A10,I3,A,I3)') 'Receiver: ', myid, &
          ' First element: ', receiveBuffer(1)
  end if

  ! Finalize measuring the time and print it out
  t1 = mpi_wtime()
  call mpi_barrier(mpi_comm_world, rc)
  call flush(6)

  write(*, '(A20, I3, A, F6.3)') 'Time elapsed in rank', myid, ':', t1-t0

  call mpi_finalize(rc)

end program basic
