#include "terrain.h"
#include <stdio.h>
#include <string.h>

erreur_terrain lire_terrain(FILE *f, Terrain *t, int *x, int *y) {
    int l, h;   // Dimensions du terrain
    int rx = -1, ry = -1; // Coordonnées initiales du robot
    char c;
    int i;  // Coordonnées pour parcourir le terrain
    int cmpL = 0, cmpH = 0;  // Compteurs pour la largeur et la hauteur lues
    
    // Lecture des dimensions du terrain
    if (fscanf(f, "%d\n%d", &l, &h) != 2) {
        return ERREUR_FICHIER;
    }

    // Vérification des dimensions
    if (l < 0 || l > DIM_MAX) {
        return ERREUR_LARGEUR;  // Largeur invalide
    }

    if (h < 0 || h > DIM_MAX) {
        return ERREUR_HAUTEUR;  // Hauteur invalide
    }

    t->largeur = l;
    t->hauteur = h;

      // Lecture du terrain
  while (fscanf(f, " %c", &c) == 1) {
      i = 0; 
      cmpL = 0; 
      while (cmpL < l && c != '\n') {
          switch (c) {
              case '.':
                  t->tab[cmpH][i] = LIBRE;
                  break;
              case '~':
                  t->tab[cmpH][i] = EAU;
                  break;
              case '#':
                  t->tab[cmpH][i] = ROCHER;
                  break;
              case 'C':
                  t->tab[cmpH][i] = ROBOT;
                  rx = cmpH;
                  ry = i;
                  break;
              default:
                  return ERREUR_CARACTERE;
                  break;
          }
          i++;
          cmpL++;
          if (cmpL < l && fscanf(f, " %c", &c) != 1) {
              return ERREUR_LARGEUR;  
          }
      }
      if (cmpL != l) {
          return ERREUR_LARGEUR;  // Incorrect width
      }
      cmpH++;
  }

  // Initialisation de la position du robot
  *x = rx;
  *y = ry;

  if (cmpH != h) {
      return ERREUR_HAUTEUR;
  }

  if (rx == -1 || ry == -1) {
      return ERREUR_ROBOT_INEXISTANT;
  }

  return OK;
}

int largeur(Terrain *t) {
    return t->largeur;
}

int hauteur(Terrain *t) {
    return t->hauteur;
}

int est_case_libre(Terrain *t, int x, int y) {
    return (x >= 0 && x < hauteur(t) && y >= 0 && y < largeur(t) && t->tab[x][y] == LIBRE);
}

void afficher_terrain(Terrain *t) {
    int i, j;
    // Parcours des lignes
    for (j = 0; j < hauteur(t); j++) {
        // Parcours des colonnes
        for (i = 0; i < largeur(t); i++) {
            // Associer chaque case à un caractère pour l'affichage
            switch (t->tab[j][i]) {  
                case LIBRE:
                    printf(".");  // Case libre
                    break;
                case EAU:
                    printf("~");  // Case avec de l'eau
                    break;
                case ROCHER:
                    printf("#");  // Case avec un rocher
                    break;
                case ROBOT:
                    printf("C");  // Position du robot
                    break;
                default:
                    printf("?");  // Cas inattendu
            }
        }
        printf("\n");  // Nouvelle ligne après chaque ligne du terrain
    }
}


void ecrire_terrain(FILE *f, Terrain *t, int x, int y) {
    int i, j;
    fprintf(f, "%d\n%d\n", largeur(t), hauteur(t));
    for (j = 0; j < hauteur(t); j++) {
        for (i = 0; i < largeur(t); i++) {
            if (i == x && j == y) {
                fprintf(f, "C");
            } else {
                switch (t->tab[i][j]) {
                    case LIBRE:
                        fprintf(f, ".");
                        break;
                    case EAU:
                        fprintf(f, "~");
                        break;
                    case ROCHER:
                        fprintf(f, "#");
                        break;
                    case ROBOT:
                        fprintf(f, "C");
                        break;
                    default:
                        fprintf(f, "?");
                        break;  
                }
            }
        }
        fprintf(f, "\n");
    }
}