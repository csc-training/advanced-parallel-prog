! Utility routines for heat equation solver
!   NOTE: This file does not need to be edited!
module utilities
    use heat

contains

  ! Swap the data fields of two variables of type field
  ! Arguments:
  !   curr, prev (type(field)): the two variables that are swapped
  subroutine swap_fields(curr, prev)

    implicit none

    type(field), intent(inout) :: curr, prev
    real(dp), allocatable, dimension(:,:) :: tmp
    integer :: tmp_win

    call move_alloc(curr%data, tmp)
    call move_alloc(prev%data, curr%data)
    call move_alloc(tmp, prev%data)

    ! TODO swap RMA windows
    tmp_win = curr%rma_window
    curr%rma_window = prev%rma_window
    prev%rma_window = tmp_win
  end subroutine swap_fields

  ! Copy the data from one field to another
  ! Arguments:
  !   from_field (type(field)): variable to copy from
  !   to_field (type(field)): variable to copy to
  subroutine copy_fields(from_field, to_field)
    use mpi

    implicit none

    type(field), intent(in) :: from_field
    type(field), intent(out) :: to_field

    integer :: double_size, ierr
    integer(kind=MPI_ADDRESS_KIND) :: win_size

    ! Consistency checks
    if (.not.allocated(from_field%data)) then
       write (*,*) "Can not copy from a field without allocated data"
       stop
    end if
    if (.not.allocated(to_field%data)) then
       ! Target is not initialize, allocate memory
       allocate(to_field%data(lbound(from_field%data, 1):ubound(from_field%data, 1), &
            & lbound(from_field%data, 2):ubound(from_field%data, 2)))

       ! TODO: Create RMA window for to_field. In principle, only borders would be needed
       ! but it is simpler to expose the whole array
       ! Utilize struct member rma_window defined in heat_mod.F90
       call mpi_type_size(MPI_DOUBLE_PRECISION, double_size, ierr)
       win_size = (from_field%nx + 2)*(from_field%ny + 2) * double_size
       call mpi_win_create(to_field%data, win_size,  &
            &              double_size, MPI_INFO_NULL, &
            &              MPI_COMM_WORLD, to_field%rma_window, ierr)

    else if (any(shape(from_field%data) /= shape(to_field%data))) then
       write (*,*) "Wrong field data sizes in copy routine"
       print *, shape(from_field%data), shape(to_field%data)
       stop
    end if

    to_field%data = from_field%data

    to_field%nx = from_field%nx
    to_field%ny = from_field%ny
    to_field%dx = from_field%dx
    to_field%dy = from_field%dy

  end subroutine copy_fields

end module utilities
