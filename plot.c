#include <stdlib.h>
#include <stdio.h>

void plot(int sizemat,double *a,int *ja, int *ia){
  printf("debut");
  double u[sizemat][sizemat];
  int c,i,k,j;
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
  FILE *f = fopen("file.txt", "w+");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }
  for (j = 0; j < sizemat; j++){
    for (i = 0; i < sizemat; i++){
      fprintf(f,"%f"" ",u[i][j]);
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
