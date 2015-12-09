#include <stdio.h>
#include <stdlib.h>

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
  int i,k,j,x,l,z,nelf,neld,ndemi;
  for (i=0;i<n;i++){
    printf("%i i ""\n",i);
    l = ia[i+1]-ia[i];
    printf("%i l ""\n",l);
    z = 0;
    ndemi= n/2;
    neld = 0;
    nelf = 0;
    if(l == 5){
      neld = 2;
    }
    if ((l == 4) && (i < (ndemi))){
      neld = 1;
    }
    if ((l == 4) && (i > (ndemi))){
      neld = 1;
      nelf = 2;
    }
    if ((l == 3) && (i < (ndemi))){
      neld = 1;
    }
    if ((l == 3) && (i > (ndemi))){
      neld = 1;
      nelf = 2;
    }
    
    for(k=ia[i]+neld;k<ia[i+1]-nelf;k++){
      j = ja[k];
      x = i-j+kd-;
      
      printf("%i x ""\n",x);printf("%i j ""\n",j);printf("%i k ""\n",k);printf("%i i ""\n",i);
      fflush(stdout); 
      abd[x][j] = a[k];
      z++;
    }
  }
  printMat(kd,n,abd);
}


void CtoF(int n,int nnz, double *a,int *ja,int *ia,double *x)/*double *b,double *sol,int issym)*/
{
  int job,nabd,lowd,mu,ml,ierr,i,k,INFO,m1,m2,j;
  double **abd,*sol,t1,t2;
  m1 = ia[0];
  m2 = ia[1];
  nabd = ja[m2-1]-ja[m1];
  printf("%i nabd ""\n",nabd );
  printf("%i n ""\n",n );
  abd = (double**) malloc((nabd+1)*sizeof(double*));
  for (i = 0; i < n; i++){
    abd[i] = (double*) malloc(n*sizeof(double));
  }
  for (i = 0;i<nabd+1;i++){
    for (j = 0;j<n;j++){
      abd[i][j]= 0.0;
    }
  }
  printf("hello \n");
  
  
  printf("%i ""coucou"" \n",nabd);
  csrbnd(n,a,ja,ia,abd,nabd);
  /*caculate nabd*/
  printf("coucou""\n");
  job = 1;
  t1 = mytimer();
  printf("coucou""\n");
  dpbsv_('U',n,nabd,1,abd,n,x,1);
  t2 = mytimer();
  printf("\nTemps de solution (CPU): %5.1f sec\n",t2-t1);
}