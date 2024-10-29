#include "operations_image.h"

/* Calcule l'image "inverse" (négative) de l'image im1, et place le
   résultat dans l'image im2 */

void inverse_video(Image *im1, Image *im2) {
  Pixel p, p_inverse;
  int l = largeur(im1);
  int h = hauteur(im1);
  int max = maxval(im1);
  /* Indices de parcours de boucles */
  int i, j;

  /* Initialisation de l'image résultat, de mêmes largeur, hauteur
     et valeur max que l'image donnée en paramètre */
  init_image(l, h, max, im2);

  /* Parcours de chaque pixel de chaque ligne */
  for (i = 0; i < l; i++) {
    for (j = 0; j < h; j++) {
      /* A COMPLÉTER
         sélection du pixel (i,j) dans l'image Im :
         p <-- lepixel(im1,i,j)
         calcul de son "inverse video" :
         p_inverse <-- max - pixel
         et affectation du résultat dans la nouvelle image im2 :
         affecter_pixel(im2,i,j,p_inverse);
      */
      affecter_pixel(im2, i, j, lepixel(im1, i, j));
    }
  }
}
