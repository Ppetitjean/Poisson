void vect_vect(int n, double *a, double *b,double *y){
  /*fait la soustraction entre les vecteur a et b de sorte à avoir y=a-b */
  int i;
  double t;
  for (i=0;i<n;i++){
    t=a[i]-b[i];
    y[i]=t;
  }
}