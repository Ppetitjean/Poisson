#include <stdlib.h>
#include <stdio.h>


void trans(int n,int ipos, double *a,int *ja,int *ia, double *b, int *ib, int *jb) {
/*calcul la transposée d'une matrice en format csr*/
    int i,k,j;
    int next = 0;
    //calcul la longeur des colone des la transposée de A
    for(i = 0; i< n;i++){
         for (k=ia[i];k < ia[i+1];k++){
            j = ja[k]+1;
            ib[j] = ib[j]+1;
         } 
      }
    /* calcul des pointeurs à patir de leur longueur*/
    ib[0] = ipos;
    for (i=0;i<n;i++){
         ib[i+1] = ib[i] + ib[i+1];
         }
    /*copie des éléments dans la matrice transposée*/     
    for (i=0;i<n;i++){
       for (k=ia[i];k<ia[i+1];k++){
	    j = ja[k] ;
            next = ib[j];
	    b[next] = a[k];
	    jb[next] = i;
            ib[j] = next+1;
       }
    }
    /*remet les ib dans le bonne ordre*/
      for (i=(n-1);i>=0;i--){
         ib[i+1] = ib[i];
      }
      ib[0] = ipos;
}


int issym(int nx,int n,double *a,int *ja,int *ia){
  /*vérifie si la matrice A est bien symétrique revie 0 si elle l'est 1 dans le cas contraire*/
  int i,ipos;
  double *atrans = malloc(sizeof(double) * (nx));
  int *iatrans = malloc(sizeof(int) * (n+1));
  int *jatrans = malloc(sizeof(int) * (nx));
  ipos = 0; 
  trans(n,ipos,a,ja,ia,atrans,iatrans,jatrans);
  for (i =0;i<nx;i++){
    if (a[i] != atrans[i] || ja[i] != jatrans[i]){
      return 1;
    }
  }
  for (i =0;i<n;i++){
    if (ia[i] != iatrans[i]){
      return 1;
    }
  }
  free(atrans);free(iatrans);free(jatrans);
  return 0;
}
