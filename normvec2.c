#include <math.h>

double normvec2(int nx ,double *x){
  /*calcul la norme euclidienne d'un vecteur x de taille nx*/
  int i ;
  double norm,t;
  t = 0;
  for (i=0;i<nx;i++){
    t = t + x[i]*x[i];
  }
  norm = sqrt(t);
  return norm;
}