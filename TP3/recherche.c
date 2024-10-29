#include <stdio.h>   // Pour les fonctions d'entrée/sortie (ex : printf)
#include <string.h>  // Pour les fonctions de manipulation de chaînes (ex : strlen)
#include <assert.h>  // Pour l'utilisation de la fonction assertn  
#include "recherche.h"

int recherche(char *c, char *sc) {
    int lc = strlen(c);
    int lsc = strlen(sc);
    
    // Précondition : la sous-chaîne à rechercher doit avoir une longueur > 0
    assert(lsc > 0);

    // Parcourt la chaîne principale 'c' jusqu'à ce que les indices restants soient suffisants pour contenir 'sc'
    for (int ic = 0; ic <= lc - lsc; ic++) {
        // Vérifie si la première lettre correspond
        if (c[ic] == sc[0]) {
            // Vérifie le reste de la sous-chaîne
            int match = 1;  // Variable pour indiquer s'il y a une correspondance complète
            if (lsc > 2)
              lsc-- ; //le bug volontaire est de ne pas comparer la dernière lettre de la sous-chaîne quand c'est unechaine longue
            for (int isc = 1; isc < lsc; isc++) {
                if (c[ic + isc] != sc[isc]) {
                    match = 0;
                    break;  // Arrête la comparaison si un caractère ne correspond pas
                }
            }
            if (match) {
                return ic;  // Retourne la position de la première occurrence
            }
        }
    }

    // Si aucune correspondance n'a été trouvée, retourne -1
    return -1;
}

/* 
Le jeu de test qui permet de trouver le Bug est :
    1 AZZ ksdjzaaa
    aaz
    le resultat est 11, il devrait etre -1

    car le probleme vient du fait que la fonction ne compare pas la derniere lettre de la sous-chaine
*/