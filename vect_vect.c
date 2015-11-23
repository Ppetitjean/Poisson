void vect_vect(int n, double *a, double *b,double *y){
  int i;
  double t;
  for (i=0;i<n;i++){
    t=a[i]-b[i];
    y[i]=t;
  }
}