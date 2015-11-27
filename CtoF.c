#include <stdio.h>
#include <stdlib.h>

void ACtoAF(int n,int nnz, double *a,int *ja,int *ia){
  int i,j;
  for (i = 1;i<nnz;i++){
    ja[i] = ja[i]+1;
  }
  for (j=0;j<n+1;j++){
    ia[j]=ia[j]+1;
  }
}

void csrbnd (int n,double *a,int *ja,int *ia,double **abd,int kd){

//  first determine ml and mu.
  int i,k,j,x;
  printf("hello2 \n");
  for (i=0;i<n;i++){
    for(k=ia[i];k<ia[i+1]-1;k++){
      j = ja[k];
      x = kd+i-j;
      printf("%i ""\n",j);
      abd[x][j] = a[k];
    }
  }
}


void CtoF(int n,int nnz, double *a,int *ja,int *ia,double *b)/*double *b,double *sol,int issym)*/
{
  int job,nabd,lowd,mu,ml,ierr,i,k,INFO;
  double **abd,*sol;
  abd = (double**) malloc(nabd*sizeof(double*));
  for (i = 0; i < n; i++){
    abd[i] = (double*) malloc(n*sizeof(double));
  }
  printf("hello \n");
  nabd = (ia[1]-ia[0])/2+1;
  
  printf("%i \n",nabd);
  csrbnd(n,a,ja,ia,abd,nabd);
  /*converting a c form CSR to a Fortran CRS*/
  ACtoAF(n,nnz,a,ja,ia);
  /*caculate nabd*/
  printf("%i \n",nabd);
  
  printf("coucou""\n");
  job = 1;
//   if (issim == 1){
//     nabd = nabd/2 +1;
//     csrbnd (n,a,ja,ia,job,&abd,nabd,&lowd,&ml,&mu,&ierr);
//     dpbsv ('U', n,nabd, 1, abd, nabd, b, n, &INFO);
//   }
//   else{
//     int IPIV;
//     csrbnd (n,a,ja,ia,job,&abd,nabd,&lowd,&ml,&mu,&ierr);
//     dgbsv (n, ml, mu, 1, abd, nabd, &IPIV, b, n, &INFO);
//   }
  
}