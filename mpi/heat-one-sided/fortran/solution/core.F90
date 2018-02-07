! Main solver routines for heat equation solver
module core
    use heat

contains

  ! Exchange the boundary data between MPI tasks
  subroutine exchange(field0, parallel)
    use mpi

    implicit none

    type(field), intent(inout) :: field0
    type(parallel_data), intent(in) :: parallel

    integer(kind=MPI_ADDRESS_KIND) :: disp
    integer :: ierr

    call mpi_win_fence(0, field0%rma_window, ierr)
    ! Put to left
    disp = (field0%nx + 2) * (field0%ny + 1)
    call mpi_put(field0%data(:, 1), field0%nx + 2, MPI_DOUBLE_PRECISION, &
                 parallel%nleft, disp,  &
                 field0%nx + 2, MPI_DOUBLE_PRECISION, field0%rma_window, ierr)

    ! Put to right
    disp = 0
    call mpi_put(field0%data(:, field0%ny), field0%nx + 2, &
                 MPI_DOUBLE_PRECISION, parallel%nright, disp, field0%nx + 2, &
                 MPI_DOUBLE_PRECISION, field0%rma_window, ierr)

    call mpi_win_fence(0, field0%rma_window, ierr)

  end subroutine exchange

  ! Compute one time step of temperature evolution
  ! Arguments:
  !   curr (type(field)): current temperature values
  !   prev (type(field)): values from previous time step
  !   a (real(dp)): update equation constant
  !   dt (real(dp)): time step value
  subroutine evolve(curr, prev, a, dt)

    implicit none

    type(field), intent(inout) :: curr, prev
    real(dp) :: a, dt
    integer :: i, j, nx, ny

    nx = curr%nx
    ny = curr%ny

    do j = 1, ny
       do i = 1, nx
          curr%data(i, j) = prev%data(i, j) + a * dt * &
               & ((prev%data(i-1, j) - 2.0 * prev%data(i, j) + &
               &   prev%data(i+1, j)) / curr%dx**2 + &
               &  (prev%data(i, j-1) - 2.0 * prev%data(i, j) + &
               &   prev%data(i, j+1)) / curr%dy**2)
       end do
    end do
  end subroutine evolve

end module core
