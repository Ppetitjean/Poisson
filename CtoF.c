#include <stdio.h>
#include <stdlib.h>

void printMat(int nbligne,int nbcol,double **x){
  int j,i;
  for (j = 0; j < nbligne; j++){
    for (i = 0; i < nbcol; i++){
      printf("%f"" ",x[j][i]);
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
      fprintf(f,"%f"" ",x[j][i]);
        }
      fprintf(f,"\n");
  }
  fclose(f);
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
  int i,k,j,x,l,z;
  z = 0;
  for (i=0;i<n;i++){

    
    for(k=ia[i];k<ia[i+1];k++){
      j = ja[k];
      x = i-j;
      if (i>=j){
      
      /*printf("%i z ""\n",z);printf("%i x ""\n",x);printf("%i j ""\n",j);*/
      fflush(stdout); 
      abd[x][j] = a[k];
      z++;}
    }
  }
  saveMat(kd+1,n,abd);
}


void CtoF(int n,int nnz, double *a,int *ja,int *ia,double *x)/*double *b,double *sol,int issym)*/
{
  int job,nabd,lowd,mu,ml,ierr,i,k,INFO,m1,m2,j;
  double **abd,*sol,t1,t2;
  m1 = ia[0];
  m2 = ia[1];
  nabd = ja[m2-1]-ja[m1];
  printf("%i ja[m2-1] ""\n",ja[m2-1] );
  printf("%i ja[m1] ""\n",ja[m1] );
  printf("%i nabd ""\n",nabd );
  printf("%i n ""\n",n );
  abd = (double**) malloc((nabd+1)*sizeof(double*));
  for (i = 0; i <= nabd; i++){
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
  extern dpbsv_('L',n,nabd,1,abd,nabd+1,x,&INFO);
  t2 = mytimer();
  printf("\nTemps de solution (CPU): %5.1f sec\n",t2-t1);
}