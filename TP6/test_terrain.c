#include "terrain.h"
#include <stdio.h>

// Codes ANSI pour les couleurs
#define RESET   "\033[0m"  // Réinitialiser la couleur
#define ROUGE   "\033[31m" // Rouge
#define VERT    "\033[32m" // Vert
#define JAUNE   "\033[33m" // Jaune
#define BLEU    "\033[34m" // Bleu

int main(int argc, char **argv) {
  FILE *f;
  Terrain t;
  int x, y;

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  f = fopen(argv[1], "r");
  erreur_terrain e = lire_terrain(f, &t, &x, &y);
  fclose(f);
  switch (e) 
    {
      case OK:
          printf(VERT "Lecture du terrain réussie.\n" RESET);
          break;
      case ERREUR_FICHIER:
          printf(ROUGE "Erreur : Impossible de lire le fichier.\n" RESET);
          return 2;
      case ERREUR_LARGEUR:
          printf(ROUGE "Erreur : Largeur du terrain invalide.\n" RESET);
          return 2;
      case ERREUR_HAUTEUR:
          printf(ROUGE "Erreur : Hauteur du terrain invalide.\n" RESET);
          return 2;
      case ERREUR_ROBOT_INEXISTANT:
          printf(ROUGE "Erreur : Position initiale du robot non définie.\n" RESET);
          return 2;
      case ERREUR_CARACTERE:
          printf(ROUGE "Erreur : Caractere non definie.\n" RESET);
          return 2;
      default:
          printf(ROUGE "Erreur inconnue lors de la lecture du terrain.\n" RESET);
          return 2;
    }
  afficher_terrain(&t);
  printf("Position initiale du robot : (%d, %d)\n", x, y);
}
