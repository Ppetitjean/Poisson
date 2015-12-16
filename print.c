
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


void printMat(int nbligne,int nbcol,double **x){
  int j,i,c,k;
  double **u;
  for (j = 0; j < nbligne; j++){
    for (i = 0; i < nbcol; i++){
      printf("%f"" ",x[j][i]);
        }
      printf("\n");
  }
}