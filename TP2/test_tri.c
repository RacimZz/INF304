#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "es_tableau.h"  // Pour lire et écrire les tableaux
#include "tri.h"         // Pour utiliser la fonction de tri_insertion

// Fonction pour vérifier si un tableau est trié en ordre croissant
int est_trie(tableau_entiers *t) {
    for (int i = 0; i < t->taille - 1; i++) {
        if (t->tab[i] > t->tab[i + 1]) {
            return 0;  // Si un élément est plus grand que le suivant, le tableau n'est pas trié
        }
    }
    return 1;  // Le tableau est trié
}

// Fonction de test qui trie les tableaux à partir de fichiers et vérifie s'ils sont bien triés
void test_tri_insertion(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <fichiers d'entrée...>\n", argv[0]);  // Message d'erreur si aucun fichier n'est passé en argument
        return;
    }

    tableau_entiers t;  // Variable pour stocker le tableau à trier
    char nom_fichier_out[256];  // Buffer pour le nom de fichier de sortie

    // Boucle sur chaque fichier passé en argument
    for (int i = 1; i < argc; i++) {
        printf("Test du fichier : %s\n", argv[i]);

        // Lecture du tableau à partir du fichier d'entrée
        lire_tableau(argv[i], &t);

        // Tri du tableau avec tri_insertion
        tri_insertion(&t);

        // Création du nom de fichier de sortie avec le suffixe ".out"
        strcpy(nom_fichier_out, argv[i]);
        strcat(nom_fichier_out, ".out");

        // Écriture du tableau trié dans le fichier de sortie
        ecrire_tableau(nom_fichier_out, &t);

        // Vérification si le tableau est trié correctement
        if (est_trie(&t) == 1)
            printf("Tableau correctement trié écrit dans : %s\n\n", nom_fichier_out);
        else
            printf("Erreur lors du tri par insertion");
    }
}

// Fonction qui génère un tableau aléatoire et l'écrit dans un fichier
void generer_tableau_alea_fichier(const char *nom_fichier, int taille, int max_val) {
    FILE *f = fopen(nom_fichier, "w");  // Ouvre le fichier en mode écriture
    if (f == NULL) {
        perror("Erreur à l'ouverture du fichier");  // Affiche un message d'erreur si le fichier ne peut pas être ouvert
        exit(EXIT_FAILURE);  // Quitte le programme
    }

    // Écrire la taille du tableau dans le fichier
    fprintf(f, "%d\n", taille);

    // Générer un tableau aléatoire et écrire chaque valeur dans le fichier
    for (int i = 0; i < taille; i++) {
        int valeur_alea = rand() % max_val;  // Génère une valeur aléatoire entre 0 et max_val - 1
        fprintf(f, "%d ", valeur_alea);  // Écrit la valeur dans le fichier
    }
    fprintf(f, "\n");  // Ajoute un saut de ligne après les éléments du tableau

    fclose(f);  // Ferme le fichier
    printf("Tableau aléatoire écrit dans le fichier : %s\n", nom_fichier);
}

// Fonction de test pour générer des tableaux aléatoires et les trier ensuite
void test_tri_insertion_alea(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: %s <fichiers d'entrée...>\n", argv[0]);  // Message d'erreur si aucun fichier n'est passé en argument
        return;
    }

    // Initialisation de la graine pour la génération aléatoire
    srand(time(NULL));

    int taille_max = 100;  // Taille maximale par défaut des tableaux
    int max_val = 1000;    // Valeur maximale des éléments du tableau

    // Boucle sur chaque fichier passé en argument
    for (int i = 1; i < argc; i++) {
        // Générer un tableau aléatoire pour chaque fichier
        int taille_alea = rand() % taille_max + 1;  // Taille aléatoire entre 1 et taille_max
        generer_tableau_alea_fichier(argv[i], taille_alea, max_val);  // Écrire le tableau aléatoire dans le fichier
    }

    // Appeler la fonction de test pour trier les tableaux aléatoires générés
    test_tri_insertion(argc, argv);
}
