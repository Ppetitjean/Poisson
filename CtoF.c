#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printMat(int nbligne,int nbcol,double **x){
  int j,i;
  for (j = 0; j < nbligne; j++){
    for (i = 0; i < nbcol; i++){
      printf("%f ",x[j][i]);
    }
    printf("\n");
  }
}
void saveMat(int nbligne,int nbcol,double **x){
  int j,i;
/*loading data in the file*/
  FILE *f = fopen("mat.txt", "w+");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }
  for (j = 0; j < nbligne; j++){
    for (i = 0; i < nbcol; i++){
      fprintf(f,"%f ",x[j][i]);
        }
      fprintf(f,"\n");
  }
  fclose(f);
}

void saveMatLinear(int L, int C, double* x) {
    int i,j;
    FILE* f = fopen("mat.txt", "w+");
    if(f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    for (j = 0; j < C; j++){
        for (i = 0; i < L; i++){
          fprintf(f, "%f ", x[j * C+ i ]);
        }
        fprintf(f,"\n");
    }
    fclose(f);
}

void csrbnd (int n,double *a,int *ja,int *ia,double *abd,int kd){

//  first determine ml and mu.
  int i,k,j,x,l,z;
  z = 0;
  for (i=0;i<n;i++){
    for(k=ia[i];k<ia[i+1];k++){
      j = ja[k];
      x = j-i;
      if (j>=i){ 
	abd[(x+i)*(kd+1) + (kd-x)] = a[k];
      }
    }
  }
}

void CtoF(int n,int nnz, double *a,int *ja,int *ia,double *x){
  int nabd,lowd,mu,ml,ierr,i,k,INFO,m1,m2,j,labd,lnabd,lbdb,nrhs;
  double *abd,*sol,t3,t4,diff;
  char uplo;
  printf("salut \n");
  fflush(stdout); 
  /*find nabd : the number of uper bandes*/
  m1 = ia[0];
  m2 = ia[1];
  nabd = ja[m2-1]-ja[m1];
  abd = calloc(((nabd+1)*n),sizeof(double));
  fflush(stdout); 
  csrbnd(n,a,ja,ia,abd,nabd);
  lnabd = nabd + 1; labd =1;uplo = 'U';lbdb = n;nrhs=1;
  clock_t now = clock();
  dpbsv_(&uplo,&n,&nabd,&nrhs,abd,&lnabd,x,&lbdb,&INFO);
  clock_t later = clock();
  diff = (((float)later - (float) now)/CLOCKS_PER_SEC);
  printf("\nTemps de solution (CPU): %5.1f sec\n",diff);
  printf("%i Info \n",INFO);
}
