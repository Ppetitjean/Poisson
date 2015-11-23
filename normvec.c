#include <math.h>

double normvec2(int nx ,double *x){
  int i ;
  double norm,t;
  t = 0;
  for (i=0;i<n;i++){
    t = t + x[i]*x[i];
  }
  norm = sqrt(t);
  return norm;
}