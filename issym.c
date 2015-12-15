#include <stdlib.h>
#include <stdio.h>


void trans(int n,int ipos, double *a,int *ja,int *ia, double *b, int *ib, int *jb) {

    // compute pointers from lengths
    int i,k,j;
    int next = 0;
    //compute lengths of rows of transp(A)
    for(i = 0; i< n;i++){
         for (k=ia[i];k < ia[i+1];k++){
            j = ja[k]+1;
            ib[j] = ib[j]+1;
         } 
      }
    printf("hello2\n");
      ib[0] = ipos;
      for (i=0;i<n;i++){
         ib[i+1] = ib[i] + ib[i+1];
         }
      for (i=0;i<n;i++){
         for (k=ia[i];k<ia[i+1];k++){
            j = ja[k] ;
            next = ib[j];
	    b[next] = a[k];
	    jb[next] = i;
            ib[j] = next+1;           
	 }

     }
// reshift ib and leave 
      for (i=(n-1);i>=0;i--){
         ib[i+1] = ib[i];
      }
      ib[0] = ipos;
}


int issym(int nx,int n,double *a,int *ja,int *ia){
  int i,ipos;
  double *atrans = malloc(sizeof(double) * (nx));
  int *iatrans = malloc(sizeof(int) * (n+1));
  int *jatrans = malloc(sizeof(int) * (nx));
  ipos = 0;
  trans(n,ipos,a,ja,ia,atrans,iatrans,jatrans);
  printf("hello1\n");
  for (i =0;i<nx;i++){
    if (a[i] != atrans[i] || ja[i] != jatrans[i]){
      return 1;
    }
  }
  printf("hello1\n");
  for (i =0;i<n;i++){
    if (ia[i] != iatrans[i]){
      return 1;
    }
  }
  free(atrans);free(iatrans);free(jatrans);
  return 0;
}
