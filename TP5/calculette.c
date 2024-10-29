#include <stdio.h>
#include <stdlib.h>
#include "type_pile_erreurs.h"
#include "commandes_calculette.h"

// Séquences ANSI pour les couleurs
#define COLOR_RED "\033[1;31m"
#define COLOR_RESET "\033[0m"

int main(int argc, char **argv)
{
    PileEntiers *pile = malloc(sizeof(PileEntiers));  // Allouer dynamiquement la pile
    if (pile == NULL) {
        printf(COLOR_RED "Erreur : allocation mémoire pour la pile\n" COLOR_RESET);
        return 1;
    }

    int x, res, y;

    // Vérification du nombre d'arguments
    if (argc != 2)
    {
        printf(COLOR_RED "Erreur : nombre d’arguments différent de 1\n" COLOR_RESET);
        free(pile);
        return 1;
    }

    // Ouverture du fichier de commandes
    FILE *f = ouvrir_commandes(argv[1]);
    if (f == NULL) {
        printf(COLOR_RED "Erreur : impossible d'ouvrir le fichier de commandes\n" COLOR_RESET);
        free(pile);
        return 1;
    }

    // Vérification si le fichier est vide
    int premier_caractere = fgetc(f);
    if (premier_caractere == EOF) {
        printf(COLOR_RED "Erreur : le fichier est vide\n" COLOR_RESET);
        fclose(f);
        free(pile);
        return 1;
    } else {
        // Remettre le caractère lu dans le flux pour ne pas le perdre
        ungetc(premier_caractere, f);
    }

    erreur_pile ERROR, ERROR_temp;
    commande cmd;
    ERROR = creer_pile(pile);  // Initialiser la pile
    if (ERROR == POINTEUR_NUL) {
        printf(COLOR_RED "Erreur : pointeur NULL lors de la création de la pile\n" COLOR_RESET);
        free(pile);
        return 1;
    }

    // Boucle principale pour traiter les commandes
    while (!fin_commandes(f))
    {
        print(pile);  // Afficher l'état de la pile

        cmd = commande_suivante(f);
        print_commandes(cmd);  // Afficher la commande lue

        switch (cmd.cmd)
        {
        case DEPILER_SOMMET:
            ERROR = depiler(pile, &x);
            if (ERROR == PILE_VIDE) {
                printf(COLOR_RED "Erreur : la pile est vide, impossible de dépiler\n" COLOR_RESET);
                break;
            }
            break;

        case EMPILER_VALEUR:
            ERROR = empiler(pile, cmd.arg);
            if (ERROR == POINTEUR_NUL) {
                printf(COLOR_RED "Erreur : échec de l'empilement\n" COLOR_RESET);
                break;
            }
            break;

        case VIDER_PILE:
            ERROR = vider(pile);
            if (ERROR == PILE_VIDE) {
                printf(COLOR_RED "Erreur : la pile est déjà vide\n" COLOR_RESET);
            }
            break;

        case EFFECTUER_ADDITION:
            ERROR = depiler(pile, &x);
            ERROR_temp = depiler(pile, &y);
            if (ERROR == PILE_VIDE || ERROR_temp == PILE_VIDE) {
                printf(COLOR_RED "Erreur : impossible d'effectuer l'addition, la pile est vide\n" COLOR_RESET);
                break;
            }
            res = x + y;
            ERROR = empiler(pile, res);
            break;

        case EFFECTUER_MULTIPLICATION:
            ERROR = depiler(pile, &x);
            ERROR_temp = depiler(pile, &y);
            if (ERROR == PILE_VIDE || ERROR_temp == PILE_VIDE) {
                printf(COLOR_RED "Erreur : impossible d'effectuer la multiplication, la pile est vide\n" COLOR_RESET);
                break;
            }
            res = x * y;
            ERROR = empiler(pile, res);
            break;

        case EFFECTUER_DIVISION:
            ERROR = depiler(pile, &x);
            ERROR_temp = depiler(pile, &y);
            if (ERROR == PILE_VIDE || ERROR_temp == PILE_VIDE) {
                printf(COLOR_RED "Erreur : impossible d'effectuer la division, la pile est vide\n" COLOR_RESET);
                break;
            }
            if (x != 0) {
                res = y / x;
                ERROR = empiler(pile, res);
            } else {
                printf(COLOR_RED "Erreur : division par zéro\n" COLOR_RESET);
                fclose(f);
                free(pile);
                return 1;
            }
            break;

        case EFFECTUER_SOUSTRACTION:
            ERROR = depiler(pile, &x);
            ERROR_temp = depiler(pile, &y);
            if (ERROR == PILE_VIDE || ERROR_temp == PILE_VIDE) {
                printf(COLOR_RED "Erreur : impossible d'effectuer la soustraction, la pile est vide\n" COLOR_RESET);
                break;
            }
            res = y - x;
            ERROR = empiler(pile, res);
            break;

        default:
            printf(COLOR_RED "ERREUR : commande inconnue\n" COLOR_RESET);
            break;
        }

        // Vérifier les erreurs
        if (ERROR != OK) {
            printf(COLOR_RED "Une erreur est survenue lors de l'exécution\n" COLOR_RESET);
        }
    }

    // Afficher l'état final de la pile et le résultat
    if (ERROR == OK) {
        ERROR = depiler(pile, &x);
        if (ERROR == OK) {
            print(pile);
            printf("Résultat : %d\n", x);
        }
    } else {
        printf(COLOR_RED "Erreur : impossible d'obtenir le résultat final\n" COLOR_RESET);
    }

    // Fermer le fichier et libérer la mémoire
    fermer_commandes(f);
    free(pile);

    return 0;
}
