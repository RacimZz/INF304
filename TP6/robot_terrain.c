#include "robot.h"
#include "terrain.h"
#include <stdio.h>

// Codes ANSI pour les couleurs
#define RESET   "\033[0m"  // Réinitialiser la couleur
#define ROUGE   "\033[31m" // Rouge
#define VERT    "\033[32m" // Vert
#define JAUNE   "\033[33m" // Jaune
#define BLEU    "\033[34m" // Bleu

#define TAILLE_TERRAIN 10

/* Affiche une orientation sur la sortie standard */
void afficher_orientation(Orientation o) {
    switch (o) {
    case Nord:
        printf(VERT "Nord\n" RESET);
        break;
    case Est:
        printf(VERT "Est\n" RESET);
        break;
    case Sud:
        printf(VERT "Sud\n" RESET);
        break;
    case Ouest:
        printf(VERT "Ouest\n" RESET);
        break;
    }
}

void afficher_infos_robot(Robot *r) {
    int x, y;
    int x1, y1;

    // Récupérer la position du robot
    position(r, &x, &y);
    // Récupérer la case devant le robot
    position_devant(r, &x1, &y1);
    // Afficher la position
    printf(JAUNE "Position : (%d, %d) - Orientation : " RESET, x, y);
    afficher_orientation(orient(r));
    printf("\n");
}

void afficher_terrain_et_robot(Terrain *t, Robot *r) {
    int i, j;
    char c;

    for (j = 0; j < hauteur(t); j++) {
        for (i = 0; i < largeur(t); i++) {
            if ((i == abscisse(r)) && (j == ordonnee(r))) {
                // Afficher le robot selon son orientation
                switch (orient(r)) {
                case Nord:
                    c = '^';
                    break;
                case Est:
                    c = '>';
                    break;
                case Sud:
                    c = 'v';
                    break;
                case Ouest:
                    c = '<';
                    break;
                }
                printf(BLEU "%c" RESET, c); // Robot en bleu
            } else {
                // Afficher la case
                switch (t->tab[j][i]) {
                case LIBRE:
                    c = '.';
                    printf("%c", c);  // Libre (sans couleur)
                    break;
                case ROCHER:
                    c = '#';
                    printf(ROUGE "%c" RESET, c); // Rocher en rouge
                    break;
                case EAU:
                    c = '~';
                    printf(BLEU "%c" RESET, c); // Eau en bleu
                    break;
                default:
                  break;
                }
            }
        }
        printf("\n");
    }
}

/* Renvoie vrai si le robot r, de sa position et orientation courante,
   peut avancer dans le terrain t */
int robot_peut_avancer(Terrain *t, Robot *r) {
    int posX, posY;
    position_devant(r, &posX, &posY);
    return est_case_libre(t, posX, posY);
}



int main(int argc, char **argv) {
    Terrain t;
    FILE *f;
    erreur_terrain e;
    int x, y;
    Robot r;
    char c;

    // Lecture du terrain : nom du fichier en ligne de commande
    if (argc < 2) {
        printf(ROUGE "Usage: %s <fichier terrain>\n" RESET, argv[0]);
        return 1;
    }

    // Lecture du terrain
    f = fopen(argv[1], "r");
    e = lire_terrain(f, &t, &x, &y);
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


    // Initialisation du robot
    init_robot(&r, x, y, Est);

    afficher_infos_robot(&r);
    afficher_terrain_et_robot(&t, &r);

    printf(JAUNE "Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in) : " RESET);
    scanf(" %c", &c);
    while (c != 'f') {
        switch (c) {
            case 'G':
            case 'g':
                tourner_a_gauche(&r);
                break;
            case 'D':
            case 'd':
                tourner_a_droite(&r);
                break;
            case 'A':
            case 'a':
                if (robot_peut_avancer(&t, &r)) {
                    printf(VERT "Le robot avance...\n" RESET);  // Afficher le message de déplacement en vert
                    t.tab[r.x][r.y] = LIBRE;
                    avancer(&r);
                } else {
                    printf(ROUGE " !! Le robot ne peut pas avancer !!\n" RESET);
                }
        }

        afficher_infos_robot(&r);
        afficher_terrain_et_robot(&t, &r);

        printf(JAUNE "Entrer une action ([a]vancer, [g]auche, [d]roite, [f]in) : " RESET);
        scanf(" %c", &c);
    }
    if (c != 'f')
        printf(ROUGE " Vous avez mis fin a la session\n" RESET);

    return 0;
}
