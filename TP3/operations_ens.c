#include <stdio.h>   // Pour les fonctions d'entrée/sortie (ex : printf)
#include <string.h>  // Pour les fonctions de manipulation de chaînes (ex : strlen)
#include <assert.h>  // Pour l'utilisation de la fonction assert


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
            for (int isc = 1; isc < lsc -1; isc++) {
                // BUG SUBTIL : la condition 'if' ici a été modifiée pour ne vérifier que l'égalité de la première lettre, et non du reste de la sous-chaîne
                if (c[ic + isc] == sc[0]) {  
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
