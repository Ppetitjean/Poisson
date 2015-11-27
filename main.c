#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void plot(int sizemat, int n,double *x){
  int j,i,c,k;
  double **u,nx,h;
  nx = sizemat;
  h = 1/(nx-1);
  printf("%f ""\n",h);
  char * commandsForGnuplot[] = {"set title \"graph solution\"","set size square","set pm3d map","set palette rgbformulae 22,13,-31", "splot 'file.txt' matrix with pm3d"};
  char * commandsForGnuplot2[] = {"set title \"graph solution\"","set pm3d","set palette rgbformulae 22,13,-31", "splot 'file.txt' matrix with pm3d"};
  
  /*definting of u*/
  u = (double**) malloc(sizemat*sizeof(double*));
  for (i = 0; i < sizemat; i++){
    u[i] = (double*) malloc(sizemat*sizeof(double));
  }printf("%i""\n",n);
  for (i = 0; i<sizemat;i++){
    for (c = 0;c<sizemat;c++){
      u[i][c] = 0.0;
    }
  }
  j =n-1;
  printf("ok1""\n");
  /*changing value not on the frontier*/
  for (i=1;i<sizemat-1;i++){
    for (k=1;k<sizemat-1;k++){
      u[i][k] = (h*h)*x[j];
      j = j-1;
    }
  }
  printf("ok2""\n");
  /*loading data in the file*/
  FILE *f = fopen("file.txt", "w+");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }
  for (j = 0; j < sizemat; j++){
    for (i = 0; i < sizemat; i++){
      fprintf(f,"%f"" ",u[j][i]);
        }
      fprintf(f,"\n");
  }
  FILE * temp = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
  FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
   for (i=0; i < 5; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //Send commands to gnuplot one by one.
    }
  FILE * temp1 = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
  FILE * gnuplotPipe2 = popen ("gnuplot -persistent", "w");
    for (i=0; i < 4; i++)
    {
    fprintf(gnuplotPipe2, "%s \n", commandsForGnuplot2[i]); //Send commands to gnuplot one by one.
    }
    
  
}

int main(int argc, char *argv[])
{
  /* déclarer les variables */
  int nx =10;
  int i,n,nzz,sym, *ia, *ja; 
  double *a, *b, *x, *y, normx, normf,normb_y,*b_y;
  double residu; 
  double t1, t2;

  /* générér le problème */
  nzz = prob(nx, &n, &ia, &ja, &a, &b);
  printf("\nSystème: ");
  printf("nx = %5d   n = %8d  nnz = %9d\n", nx, n, ia[n] );
  /*test si la mtrice est symétrique*/
  sym = issym(nzz,n,a,ja,ia);
  if (sym == 0){
    printf("la martice a est symétrique""\n");
  }
  else{  
    printf("la matrice a n'est pas symétrique""\n");
  }
  /* allouer la mémoire pour le vecteur de solution */
  x = malloc(n * sizeof(double));
  if ( x == NULL ) {
  	printf("\n ERREUR : pas assez de mémoire pour le vecteur des solutions\n\n");
        return 1;
  }

  /* résoudre et mesurer le temps de solution */
  t1 = mytimer();
  if( solve_umfpack(n, ia, ja, a, b, x) )
     return 1;
  t2 = mytimer();
  printf("\nTemps de solution (CPU): %5.1f sec\n",t2-t1);
  y = malloc(sizeof(double)*n);
  b_y = malloc(sizeof(double)*n);
  printf("%i""\n",n);
  for (i=0;i<2;i++){printf("%i""\n",i);}
  amux(n,x,y,a,ja,ia);
  vect_vect(n,b,y,b_y);
  double z,v,ye;
  z = normvec2(n,b_y);
  v = normvec2(n,b);
  residu = z/v;
  printf("%e""\n",residu);
//   plot(nx,n,x);
  CtoF(n,nzz,a,ja,ia,b);
  /* libérér la mémoire */
  free(ia); free(ja); free(a); free(b); free(x); free(y); free(b_y);
return 0;
}

