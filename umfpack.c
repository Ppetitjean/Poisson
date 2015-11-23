#include <stdio.h>
/* #include <stdlib.h>*/
#include "umfpack.h"

int solve_umfpack(int n, int *ja, int *ia, double *a, 
                  double *b, double *x)
/*
   But
   ===
   Résout le système linéaire 
                          
                             Ax = b                                   

   en utilisant les fonctions de UMFPACK. La matrice A est 
   supposée être dans le format CRS défini par les trois 
   tableaux : 'ia', 'ja' et 'a'.

   Attention! pour chaque ligne stoquée dans les tableaux 'ja'
              et 'a' entre ia[i] et ia[i+1]-1, i=0,...,n-1
              les indices de colonnes dans 'ja' doivent être 
              ordonnés de manière croissante.

   Arguments
   =========
   n  (output) - le nombre d'inconus dans le système
   ia (output) - le tableau 'ia' de la matrice A
   ja (output) - le tableau 'ja' de la matrice A
   a  (output) - le tableau 'a' de la matrice A
   b  (output) - le tableau contenant le vecteur B
   x  (output) - le tableau contenant le vecteur X
*/
{
    /* initialization */
    int status;
    double Info [UMFPACK_INFO], Control [UMFPACK_CONTROL];
    void *Symbolic, *Numeric ;

    /* factorization symbolique */
    status = umfpack_di_symbolic (n, n, ja, ia, a, &Symbolic, Control, Info) ;
    if (status < 0)
    {
	umfpack_di_report_info (Control, Info) ;
	umfpack_di_report_status (Control, status) ;
        printf("\n ERREUR : umfpack_di_symbolic a échoué\n\n");
        return 0;
    }

    /* factorization symbolique - affichage */

    printf ("\nFactorization symbolique de A: ") ;
    (void) umfpack_di_report_symbolic (Symbolic, Control) ;

    /* factorization numérique */

    status = umfpack_di_numeric (ja, ia, a, Symbolic, &Numeric, Control, Info);
    if (status < 0)
    {
	umfpack_di_report_info (Control, Info) ;
	umfpack_di_report_status (Control, status) ;
	error ("umfpack_di_numeric failed") ;
    }

    /* factorization numérique - affichage */
    printf ("\nFactorization numérique de A: ") ;
    (void) umfpack_di_report_numeric (Numeric, Control) ;

   /* solution */
   status = umfpack_di_solve (UMFPACK_A, ja, ia, a, x, b, Numeric, Control, Info) ;
    umfpack_di_report_info (Control, Info) ;
    umfpack_di_report_status (Control, status) ;
    if (status < 0)
    {
	error ("umfpack_di_solve failed") ;
    }
}
