#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void plot(int sizemat, int n,double *a,int *ja, int *ia){
  int j,i,c,k;
  double **u;
  u = (double**) malloc(sizemat*sizeof(double*));
  for (i = 0; i < sizemat; i++){
    u[i] = (double*) malloc(sizemat*sizeof(double));
  }printf("%i""\n",n);
  for (i = 0; i<sizemat;i++){
    for (c = 0;c<sizemat;c++){
      u[i][c] = 0.0;
    }
  }
  printf("ok1""\n");
  for (i=0;i<sizemat;i++){
    for (k=ia[i];k<ia[i+1];k++){
      j = ja[k];
      u[i][j] = a[k];
    }
  }
  for (i = 0; i<sizemat;i++){
    for (c = 0;c<sizemat;c++){
      printf("%f""  ",u[i][c]);
    }
    printf("\n");
  }
  printf("ok2""\n");
  FILE *f = fopen("file.txt", "w+");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }
  for (j = 0; j < sizemat; j++){
    for (i = 0; i < sizemat; i++){
      fprintf(f,"%f"" ",u[i][j]);
      printf("%f""\n",u[i][j]);
        }
      fprintf(f,"\n");
  }
  FILE * temp = fopen("data.temp", "w");
    /*Opens an interface that one can use to send commands as if they were typing into the
     *     gnuplot command line.  "The -persistent" keeps the plot open even after your
     *     C program terminates.
     */
  FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
  fprintf(gnuplotPipe, "%s \n", "splot 'file.txt' matrix nonuniform with lines t ''");
  

  
}

int main(int argc, char *argv[])
{
  /* déclarer les variables */
  int nx = 1000;
  int i,n,nzz,sym, *ia, *ja; 
  double *a, *b, *x, *y, normx, normf,normb_y,*b_y;
  long double residu; 
  double t1, t2;

  /* générér le problème */
  nzz = prob(nx, &n, &ia, &ja, &a, &b);
  printf("\nSystème: ");
  printf("nx = %5d   n = %8d  nnz = %9d\n", nx, n, ia[n] );
  /*test si la mtrice est symétrique*/
  sym = issym(nzz,n,a,ja,ia);
  if (sym == 0){
    printf("la matice a est symétrique""\n");
  }
  else{  
    printf("la matice a n'est pas symétrique""\n");
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
  printf("%2.20Lf""\n",residu);
  
  plot(n,nzz,a,ja,ia);
  /* libérér la mémoire */
  free(ia); free(ja); free(a); free(b); free(x); free(y); free(b_y);
return 0;
}

