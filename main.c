#include <stdio.h>
#include <stdlib.h>
#include "main.h"

void plot(int sizemat, int n,double *x){
  int j,i,c,k;
  double **u,nx,h;
  nx = sizemat;
  h = 1/(nx-1);
  char * commandsForGnuplot[] = {"nx = 100","set title \"graph solution\"","set size square","set pm3d map","set palette rgbformulae 22,13,-31","set ytics (\"0\"0,\"1/2\"nx/2,\"1\"nx)","set xtics (\"0\"0,\"1/2\"nx/2,\"1\"nx)", "splot 'file.txt' matrix with pm3d"};
  char * commandsForGnuplot2[] = {"nx = 100","set title \"graph solution\"","set ytics (\"0\"0,\"1/2\"nx/2,\"1\"nx)","set xtics (\"0\"0,\"1/2\"nx/2,\"1\"nx)","set pm3d","set palette rgbformulae 22,13,-31", "splot 'file.txt' matrix with pm3d"};
  
  /*definting of u*/
  u = (double**) malloc(sizemat*sizeof(double*));
  for (i = 0; i < sizemat; i++){
    u[i] = (double*) malloc(sizemat*sizeof(double));
  }
  for (i = 0; i<sizemat;i++){
    for (c = 0;c<sizemat;c++){
      u[i][c] = 0.0;
    }
  }
  j =0;

  /*change les valeurs hors des frontières*/
  for (i=sizemat-1;i>1;i--){
    for (k=1;k<sizemat-1;k++){
      u[i][k] = x[j];
      j = j+1;
    }
  }
  /*chargement des donnes dans un fichier*/
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
    /*Ouvre une interface qu'on peut utilisé pour éxécuter des commandes comme si c'était 
     * l'utilisateur qui tapait ces commandes dans gnuplot.
     * La commande "-persistent" permet de garder le graphique affiché une fois 
     * que le programme C terminer
     */
  FILE * gnuplotPipe = popen ("gnuplot -persistent", "w");
   for (i=0; i < 8; i++)
    {
    fprintf(gnuplotPipe, "%s \n", commandsForGnuplot[i]); //envoie les commandes a gnuplot une par une.
    }
  FILE * gnuplotPipe2 = popen ("gnuplot -persistent", "w");
    for (i=0; i < 7; i++)
    {
    fprintf(gnuplotPipe2, "%s \n", commandsForGnuplot2[i]); //envoie les commandes a gnuplot une par une.
    }
  free(u);
}

int main(int argc, char *argv[]){
  /* déclarer les variables */
  int nx =100;
  int i,n,nzz,sym, *ia, *ja; 
  double *a, *b, *x, *y, normx, normf,normb_y,*b_y,*x1,d,*bprim,*b_yprim;
  double residu; 
  double t1, t2,t3,t4;

  /* générér le problème */
  prob(nx, &n, &ia, &ja, &a, &b);
  printf("\nSystème: ");
  printf("nx = %5d   n = %8d  nnz = %9d\n", nx, n, ia[n] );
  /*test si la mtrice est symétrique*/
  nzz = ia[n];
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

  /*résoudre et mesurer le temps de solution*/ 
  t1 = mytimer();
  if( solve_umfpack(n, ia, ja, a, b, x) )
      return 1;
  t2 = mytimer();
  printf("\nTemps de solution (CPU): %5.1f sec\n",t2-t1);
  y = malloc(sizeof(double)*n);
  
  x1 = malloc(sizeof(double)*n);
  b_y = malloc(sizeof(double)*n);
  b_yprim = malloc(sizeof(double)*n);
  bprim = malloc(sizeof(double)*n);
  /*calcul du résidu*/
  double z,v,ye;
  amux(n,x,y,a,ja,ia);
  vect_vect(n,b,y,b_y);
  z = normvec2(n,b_y);
  v = normvec2(n,b);
  d = normvec2(n,x);
  residu = z/v;
  printf("%e residu \n",residu);
  copy(n,b,bprim);
  plot(nx,n,x);
  /*resolution en utilisant DPBSV*/
  CtoF(n,nzz,a,ja,ia,bprim);
    /*calcul du résidu pour DPBSV*/
  amux(n,bprim,y,a,ja,ia);
  vect_vect(n,b,y,b_y);
  z = normvec2(n,b_y);
  v = normvec2(n,b);
  residu = z/v;
  printf("%e residu2 \n",residu);
  /*resolution en utilisant DAGMG*/
  agmgc(n,nzz,a,ja,ia ,b,x1);
  /* libérér la mémoire */
  free(ia); free(ja); free(a); free(b); free(x); free(y); free(b_y);free(x1);
return 0;
}

