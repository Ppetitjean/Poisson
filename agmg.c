#include <stdio.h>
#include <stdlib.h>


void ACtoAF(int n,int nnz, int *ja,int *ia){
  int i,j;
  for (i = 1;i<nnz;i++){
    ja[i] = ja[i]+1;
  }
  for (j=0;j<n+1;j++){
    ia[j]=ia[j]+1;
  }
}

void agmgc(int n,int nnz, double *a,int *ja,int *ia ,double *b,double *x){
  int iprint,i,nrest,iterr,ijob;
  double itoll;
  ACtoAF(n,nnz,ja,ia);
  iprint = 6;
  iterr = 300;
  itoll = 1.0e-6;
  ijob = 0;
  nrest = 1;
  dagmg_(&n, a, ja, ia, b, x, &ijob, &iprint, &nrest, &iterr,&itoll);
}