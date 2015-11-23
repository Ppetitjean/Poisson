#include <stdlib.h>
#include <stdio.h>

void amux (int n,double *x,double *y, double *a,int *ja,int *ia){
  int i,k,j;
  double t;
      
  for (i = 0; i<n;i++){
  // compute the inner product of row i with vector x
      t = 0;
      for (k=ia[i];k<ia[i+1];k++){
 	j = ja[k];
	t =t+a[k]*x[j];
      }
  // store result in y[i]
         y[i] = t;
  }
}