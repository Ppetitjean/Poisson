
#include "coucou.h"
#include <stdlib.h>
#include <stdio.h>

#include <stdlib.h>
#include <stdio.h>

void plot(int sizemat, int n,double *a,int *ja, int *ia){
  double u[sizemat][sizemat];
  int c,i,k,j;
  printf("%i""\n",n);
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
  for (i = 0; i<sizemat;i++){
    for (c = 0;c<sizemat;c++){
      printf("%f""  ",u[i][c]);
    }
    printf("\n");
  }
  printf("ok2""\n");
  FILE *f = fopen("file.txt", "w+");
  if (f == NULL)
  {
      printf("Error opening file!\n");
      exit(1);
  }
  for (j = 0; j < sizemat; j++){
    for (i = 0; i < sizemat; i++){
      fprintf(f,"%f"" ",u[i][j]);
      printf("%f""\n",u[i][j]);
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

// void trans(int n,int ipos, double *a,int *ja,int *ia, double *b, int *ib, int *jb) {
// 
//     // compute pointers from lengths
//     int i,k,j;
//     int next = 0;
//     //compute lengths of rows of transp(A)
//     for(i = 0; i<= n;i++){
//          for (k=ia[i];k < ia[i+1];k++){
//             j = ja[k]+1;
//             ib[j] = ib[j]+1;
//          } 
//       }
// 	//now do the actual copying
//       ib[0] = ipos;
//       for (i=0;i<n;i++){
//          ib[i+1] = ib[i] + ib[i+1];
//          }
//       for (i=0;i<n;i++){
//          for (k=ia[i];k<ia[i+1];k++){
//             j = ja[k] ;
//             next = ib[j];
// 	    b[next] = a[k];
// 	    jb[next] = i;
//             ib[j] = next+1;
// 	    printf("%i",next);
// 	 }
// 
//      }
// // reshift ib and leave 
//       for (i=n;i>=0;i--){
//          ib[i+1] = ib[i];
//       }
//       ib[0] = ipos;
// }

/*
int issym(int nx,int n,double *a,int *ja,int *ia){
  int i,ipos;
  double *b = malloc(sizeof(double) * (nx-1));
  int *ib = malloc(sizeof(int) * (n+1));
  int sizeib = 0;
  int *jb = malloc(sizeof(int) * (nx-1));
  int sizejb = 0;
  ipos = 0;
  trans(n,ipos,a,ja,ia,b,ib,jb);
  for (i =0;i<nx;i++){
    if (a[i] != b[i] || ja[i] != jb[i]){
      return 1;
    }
  }
  for (i =0;i<n+1;i++){
    if (ia[i] != ib[i]){
      return 1;
    }
  } 
  return 0;
}
*/

void main() {
    int n,nx,ipos,i,res;
    n = 3;
    ipos = 0;
    nx = 6;
    int *ia = malloc(sizeof(int) * n+1);
    int *ja = malloc(sizeof(int)*(nx));
    double *a = malloc(sizeof(double) * (nx));
    double *b = malloc(sizeof(double) * (nx));
    int sizeb = 0;
    int *ib = malloc(sizeof(int) * (n+1));
    int sizeib = 0;
    int *jb = malloc(sizeof(int) * (nx));
    int sizejb = 0;
    /*a[0]= 1.0;
    a[1]=1.0;
    a[2]=2.0;
    a[3]=3.0;
    a[4]=2.0;
    ja[0]=0.0;
    ja[1]=1.0;
    ja[2]=0.0;
    ja[3]=1.0;
    ja[4]=2.0;
    ia[0]= 0.0;
    ia[1]=1.0;
    ia[2]=2.0;
    ia[3]=5.0;*/
    
    /*int taille_ia = 4;
    int ia[4] = {0,2,5,6};
    double a[6] = {4,1,1,2,1,1};
    int ja[6] = {0,1,0,1,2,1};
    a[0]=4.0;
    a[1]=1.0;
    a[2]=1.0;
    a[3]=2;
    a[4]=1;
    a[5]=1;
    ja[0]=0;
    ja[1]=1;
    ja[2]=0;
    ja[3]=1;
    ja[4]=2;
    ja[5]=1;
    ia[0]= 0;
    ia[1]=2;
    ia[2]=5;
    ia[3]=6;
     int iA[4] = {0,2,5,6};
    int A[6] = {4,1,1,2,7,1};
    int jA[6] = {0,1,0,1,2,1};
    */
    a[0]=4.0;
    a[1]=1.0;
    a[2]=1.0;
    a[3]=2.0;
    a[4]=1.0;
    a[5]=1.0;
    ja[0]=0;
    ja[1]=1;
    ja[2]=0;
    ja[3]=1;
    ja[4]=2;
    ja[5]=1;
    ia[0]= 0;
    ia[1]=2;
    ia[2]=5;
    ia[3]=6;
//     res = issym(6,n,a,ja,ia);
//     if (res == 0){
//       printf("est symetrique");
//     }
//     else {
//       printf("n'est pas symetrique");
//     }
//     trans(n,ipos,a,ja,ia,b,ib,jb);
//     for (i=0;i<n+1;i++){
//     	printf("%i""\n",ib[i]);
//     	}
//     for (i=0;i<nx;i++){
//     	printf("%i""\n",jb[i]);
//     	}
    printf("first""\n");
    plot(n,nx,a,ja,ia);
    /*
    for (i=0;i<nx;i++){
      printf("a");printf("%f""\n",a[i]);printf("b");printf("%f""\n",b[i]);
    }
*/

}
