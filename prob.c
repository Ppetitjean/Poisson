#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int prob(int nx, int *n, int **ia, int **ja, double **a, double **b)
/*
   But
   ===
   Génère le système linéaire n x n 
                          
                             Au = b                                   

   qui correspond à la disrétisation sur une grille cartesienne regulière 
   nx x nx de l'équation de Poisson à deux dimensions
              
              d    d           d    d
          ax -- ( -- u ) + ay -- ( -- u ) + c u = f   sur [0,1] x [0,1]
             dx   dx          dy   dy


  avec f(x,y) = sin(x^2+y^2), et les conditions aux limites de Dirichlet
         
         u = 0   sur (x,0) , (x,1), (0,y) et (1,y) , avec 0 <= x,y <= 1 . 
  
  La numérotation des inconnues est lexicographique, la direction x étént 
  parcourue avant celle de y. La matrice A est retournée dans le format 
  CRS qui est défini par les trois tableaux : 'ia', 'ja' et 'a'.

  Arguments
  =========
  nx (input)  - nombre de points par direction dans la grille 
  n  (output) - pointeur vers le nombre d'inconus dans le système
  ia (output) - pointeur vers le tableau 'ia' de la matrice A
  ja (output) - pointeur vers le tableau 'ja' de la matrice A
  a  (output) - pointeur vers le tableau 'a' de la matrice A
  b  (output) - pointeur vers le tableau 'b'

*/
{
    int  nnz, ix, iy, ind;
    double xx, yy;

    nx -= 2; /* noeuds sur la frontière Dirichlet ne sont pas pris en compte */
    *n  = nx * nx; /* nombre d'inconnues */
    nnz = 5 * nx * nx - 4 * nx; /* nombre d'éléments non nuls */

    /* allocation des tableaux */
    *ia  = malloc((*n + 1) * sizeof(int));
    *ja  = malloc(nnz * sizeof(int));
    *a   = malloc(nnz * sizeof(double));
    *b   = malloc(*n * sizeof(double));

    /* allocation réussite? */
    if (*ia == NULL || *ja == NULL || *a == NULL || *b == NULL ) {
        printf("\n ERREUR : pas assez de mémoire pour générer le système\n\n");
        return 1;
    }

    /* partie principale : replissage de la matrice */
    nnz = 0;

    for (iy = 0; iy < nx; iy++) {
        for (ix = 0; ix < nx; ix++) {
            /* numéro de l'éauqtion */
            ind = ix + nx * iy;

            /* marquer le début de la ligne suivante dans le tableau 'ia' */
            (*ia)[ind] = nnz;

            /* calculer le membre de droite */
            xx = (ix+1.0)/(nx+1.0); xx = xx*xx;
            yy = (iy+1.0)/(nx+1.0); xx = yy*yy;
            (*b)[ind] = sin(xx+yy);

            /* replissage de la ligne : voisin inférieur */
            if (iy > 0)  {
                (*a)[nnz] = -1.0;
                (*ja)[nnz] = ind - nx;
                nnz++;
            }

            /* replissage de la ligne : voisin à gauche */
            if (ix > 0)  {
                (*a)[nnz] = -1.0;
                (*ja)[nnz] = ind - 1;
                nnz++;
            }

            /* replissage de la ligne : élém. diagonal */
            (*a)[nnz] = 4.0;
            (*ja)[nnz] = ind;
            nnz++;

            /* replissage de la ligne : voisin à droite */
            if (ix < nx - 1) {
                (*a)[nnz] = -1.0;
                (*ja)[nnz] = ind + 1;
                nnz++;
            }

            /* replissage de la ligne : voisin supérieur */
            if (iy < nx - 1) {
                (*a)[nnz] = -1.0;
                (*ja)[nnz] = ind + nx;
                nnz++;
            }
        }
    }

    /* dernier élément du tableau 'ia' */
    (*ia)[ind + 1] = nnz;
    printf("%i""\n",ind);

    /* retour de fonction habituel */
    return nnz;
}
