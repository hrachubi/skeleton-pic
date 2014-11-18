#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "ssemain.h"

void cadd(float a[], float b[], float c[], int nx) {
   int j;
   for (j = 0; j < nx; j++) {
      a[j] = b[j] + c[j];
   }
   return;
}

void dtimer(double *time, struct timeval *itime, int icntrl);

int main(int argc, char *argv[])
{
/* SSE vector add test program */
/* written by Viktor K. Decyk, UCLA */
/* nx = size of array, nblock = block size on SSE */
   int nx = 1048576, nblock = 4;
   int j, irc;
   float time = 0.0;
   float eps, epsmax;
   double dtime;
   float *a = NULL, *b = NULL, *c = NULL, *d = NULL; 
   struct timeval itime;
   float *g_a = NULL, *g_b = NULL, *g_c = NULL; 

/* initialize Host data */
   a = (float *) malloc(nx*sizeof(float));
   b = (float *) malloc(nx*sizeof(float));
   c = (float *) malloc(nx*sizeof(float));
   d = (float *) malloc(nx*sizeof(float));
/* initialize vectors */
   for (j = 0; j < nx; j++) {
      a[j] = 0.0; b[j] = j + 1; c[j] = 2*j + 2; d[j] = -1.0;
   }
/* set up SSE */
   irc = 0;
   setgbsize(nblock);
/* allocate aligned data on SSE, return address to C */
   g_fallocate(&g_a,nx,&irc);
   g_fallocate(&g_b,nx,&irc);
   g_fallocate(&g_c,nx,&irc);
   if (irc != 0) {
      printf("SSE allocate error!\n");
      exit(1);
   }

/* First execute on Host in C: a = b + c */
   dtimer(&dtime,&itime,-1);
   cadd(a,b,c,nx);
   dtimer(&dtime,&itime,1);
   printf("C add time=%e\n",(float)dtime);
/* Copy data to SSE */
   dtimer(&dtime,&itime,-1);
   copyin_gmemptr(b,g_b,nx);
   copyin_gmemptr(c,g_c,nx);
   dtimer(&dtime,&itime,1);
   time += (float)dtime;
   printf("Copyin time=%e\n",(float)dtime);
/* Execute on SSE: g_a = g_b + g_c */
   dtimer(&dtime,&itime,-1);
   ssadd(g_a,g_b,g_c,nx);
   dtimer(&dtime,&itime,1);
   time += (float)dtime;
   printf("SSE add time=%e\n",(float)dtime);
/* Copy data from SSE: d = g_a */
   dtimer(&dtime,&itime,-1);
   copyout_gmemptr(d,g_a,nx);
   dtimer(&dtime,&itime,1);
   time += (float)dtime;
   printf("Copyout time=%e\n",(float)dtime);
   printf("Total SSE time=%e\n",time);

/* Check for correctness: compare a and d */
   epsmax = 0.0;
   for (j = 0; j < nx; j++) {
      eps = a[j] - d[j];
      if (eps < 0.0)
         eps = -eps;
      if (eps > epsmax)
         epsmax = eps;
   }
   printf("maximum difference = %e\n",epsmax);

/* deallocate memory on SSE */
   g_deallocate(&g_a);
   g_deallocate(&g_b);
   g_deallocate(&g_c);
/* deallocate Host memory */
   free(a);
   free(b);
   free(c);
   free(d);

   return 0;
}

