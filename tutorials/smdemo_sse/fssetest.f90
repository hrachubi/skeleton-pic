!-----------------------------------------------------------------------
      program ssetest
! SSE vector add test program
! written by Viktor K. Decyk, UCLA
! nx = size of array, nblock = block size on SSE
      implicit none
      integer :: nx = 1048576, nblock = 4
      integer :: j, irc
      real :: time = 0.0
      real :: eps, epsmax
      double precision :: dtime
      real, dimension(:), pointer :: a, b, c, d
      integer, dimension(4) :: itime
      integer, dimension(2) :: g_a = 0.0, g_b = 0.0, g_c = 0.0
!
! initialize Host data
      allocate(a(nx),b(nx),c(nx),d(nx))
      do j = 1, nx
         b(j) = j
         c(j) = 2*j
      enddo
      a = 0.0; d = -1.0
! set up SSE
      irc = 0
      call setgbsize(nblock)
! allocate aligned data on SSE, return address to Fortran
      call g_fallocate(g_a,nx,irc)
      call g_fallocate(g_b,nx,irc)
      call g_fallocate(g_c,nx,irc)
      if (irc /= 0) then
         write (*,*) 'SSE allocate error!'
         stop
      endif
!
! First execute on Host in Fortran: a = b + c
      call dtimer(dtime,itime,-1)
      call fadd(a,b,c,nx)
      call dtimer(dtime,itime,1)
      write (*,*) 'Fortran add time=', real(dtime)
! Copy data to SSE
      call dtimer(dtime,itime,-1)
      call copyin_gmemptr(b,g_b,nx)
      call copyin_gmemptr(c,g_c,nx)
      call dtimer(dtime,itime,1)
      time = time + real(dtime)
      write (*,*) 'Copyin time=', real(dtime)
! Execute on SSE: g_a = g_b + g_c
      call dtimer(dtime,itime,-1)
      call ssadd(g_a,g_b,g_c,nx)
      call dtimer(dtime,itime,1)
      time = time + real(dtime)
      write (*,*) 'SSE add time=', real(dtime)
! Copy data from SSE: d = g_a
      call dtimer(dtime,itime,-1)
      call copyout_gmemptr(d,g_a,nx)
      call dtimer(dtime,itime,1)
      time = time + real(dtime)
      write (*,*) 'Copyout time=', real(dtime)
      write (*,*) 'Total SSE time=',time
!
! Check for correctness: compare a and d
      epsmax = 0.0
      do j = 1, nx
         eps = abs(a(j)-d(j))
         if (eps > epsmax) epsmax = eps
      enddo
      write (*,*) 'maximum difference = ', epsmax
!
! deallocate memory on SSE
      call g_deallocate(g_a)
      call g_deallocate(g_b)
      call g_deallocate(g_c)
! deallocate Host memory
      deallocate(a,b,c,d)
!
      end program
!
      subroutine fadd(a,b,c,nx)
      integer :: nx
      real, dimension(nx) :: a, b, c
      integer :: j
      do j = 1, nx
         a(j) = b(j) + c(j)
      enddo
      end subroutine
      
