  int prob(int nx, int *n, int **ia, int **ja, double **a, double **b);
  double mytimer(void);
  int solve_umfpack(int n, int *ja, int *ia, double *a, double *b, double *x);
  int issym(int nx,int n,double *a,int *ja,int *ia);
  double amux (int n,double *x,double *y, double *a,int *ja,int *ia);
  double normvec2(int nx ,double *x);
  void vect_vect(int n, double *a, double *b,double *result);
  void CtoF(int n,int nnz, double *a,int *ja,int *ia,double *b);
//   void plot(int sizemat, double *a, int *ja,int *ia);