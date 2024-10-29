#include <stdio.h>
#include <stdlib.h>
#include "type_pile.h"
#include "commandes_calculette.h"

int main(int argc, char **argv)
{
    PileEntiers *pile = malloc(sizeof(PileEntiers));  // Allouer dynamiquement la pile
    if (pile == NULL) {
        printf("Erreur : allocation mémoire pour la pile\n");
        return 1;
    }

    int x, y;

    // Vérification du nombre d'arguments
    if (argc != 2)
    {
        printf("Erreur : nombre d’arguments différent de 1\n");
        free(pile);
        return 1;
    }

    // Ouverture du fichier de commandes
    FILE *f = ouvrir_commandes(argv[1]);
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier de commandes\n");
        free(pile);
        return 1;
    }

    commande cmd;
    creer_pile(pile);  // Initialiser la pile

    // Boucle principale pour traiter les commandes
    while (!fin_commandes(f))
    {       
        print(pile);  // Afficher l'état de la pile

        cmd = commande_suivante(f);
        print_commandes(cmd);  // Afficher la commande lue

        switch (cmd.cmd)
        {
        case DEPILER_SOMMET:
            x = depiler(pile);
            break;

        case EMPILER_VALEUR:
            // La valeur à empiler est déjà dans `cmd.arg` après traitement
            empiler(pile, cmd.arg);
            break;

        case VIDER_PILE:
            vider(pile);
            break;

        case EFFECTUER_ADDITION:
            x = depiler(pile);
            y = depiler(pile);
            empiler(pile, x + y);
            break;

        case EFFECTUER_MULTIPLICATION:
            x = depiler(pile);
            y = depiler(pile);
            empiler(pile, x * y);
            break;

        case EFFECTUER_DIVISION:
            x = depiler(pile);
            y = depiler(pile);
            if (y != 0) {
                empiler(pile, y / x);
            } else {
                printf("Erreur : division par zéro\n");
            }
            break;

        case EFFECTUER_SOUSTRACTION:
            x = depiler(pile);
            y = depiler(pile);
            empiler(pile, y - x);
            break;

        case COMMANDE_INCORRECTE:
            printf("ERREUR : commande incorrecte\n");
            break;

        default:
            printf("ERREUR : commande inconnue\n");
            break;
        }
    }

    // Afficher l'état final de la pile et le résultat
    print(pile);
    x = depiler(pile);
    printf("Résultat : %d\n", x);

    // Fermer le fichier et libérer la mémoire
    fermer_commandes(f);
    free(pile);  // Libérer la mémoire allouée pour la pile

    return 0;
}
