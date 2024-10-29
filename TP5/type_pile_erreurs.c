#include <stdio.h>
#include "type_pile_erreurs.h"


/* Constructeurs */

/* Créer une pile vide
   Précondition : p != NULL
   Résultat : p est une pile vide
   Retourne :
     - OK si la fonction s'est déroulée correctement
     - POINTEUR_NUL si p == NULL
 */
erreur_pile creer_pile(PileEntiers *p){
    if(p==NULL)
        return POINTEUR_NUL;
    p->n = 0;
    return OK;
}

/* Opérations d'accès */

/* Retourne vrai ssi p est vide */
int est_vide(PileEntiers *p){
    if(p==NULL)
        return POINTEUR_NUL;
    p->n=0;
    return 1;
}

/* Renvoie l'entier en haut de la pile
   Précondition : p non vide
   Résultat : res contient l'entier en haut de la pile
   Retourne :
     - OK si la précondition est valide
     - PILE_VIDE si p est vide. Dans ce cas, la valeur de res n'est
       pas définie
 */
erreur_pile sommet(PileEntiers *p, int *res){
    if(p==NULL)
        return POINTEUR_NUL;
    if(p->n==0)
        return PILE_VIDE;
    *res= p->tab[p->n-1];
    return OK;
}

/* Renvoie le nombre d'éléments dans la pile */
int taille(PileEntiers *p){
    /*if(p==NULL)
        return POINTEUR_NUL;*/
    return p->n;
}

/* Afficher les éléments de la pile */
void print(PileEntiers *p){
    int i;
    printf("Contenu de la pile : ");
    for (i=0; i<p->n; i++) {
        printf("%d | ", p->tab[i]);
    }
    printf("\n");
}

/* Opérations de modification */

/* Vider la pile p
   Précondition : p != NULL
   Résultat : p est une pile vide
   Retourne :
     - OK si la fonction s'est déroulée correctement
     - POINTEUR_NUL si p == NULL
*/
erreur_pile vider(PileEntiers *p){
    if(p==NULL)
        return POINTEUR_NUL;
    if(p->n==0)
        return PILE_VIDE;
    int i;
    erreur_pile ARRIS;
    
    while(est_vide(p)!=1)
    {
        ARRIS = depiler(p,&i);
        if (ARRIS == POINTEUR_NUL || ARRIS == PILE_VIDE)
            return ARRIS;
    }
    return OK;
}

/* Empiler un entier x
   Précondition : p != NULL et taille(p) < TAILLE_MAX
   Résultat : l'entier x est placé en haut de la pile
   Retourne :
     - OK si la fonction s'est déroulée correctement
     - POINTEUR_NUL si p == NULL
     - PILE_PLEINE si la structure est pleine, et l'entier ne peut
       être empilé. Dans ce cas la pile p n'est pas modifiée
*/
erreur_pile empiler(PileEntiers *p, int x){
    if(p==NULL)
        return POINTEUR_NUL;
    if(p->n==TAILLE_MAX)
        return PILE_PLEINE;
    p->tab[p->n++]=x;
    return OK;
}

/* Supprimer et renvoyer l'entier en haut de la pile
   Précondition : p != NULL et p non vide
   Résultat :
     - l'entier en haut de la pile est enlevé de la pile
     - l'entier resultat contient l'entier dépilé
   Retourne :
     - OK si la précondition est valide
     - POINTEUR_NUL si p == NULL
     - PILE_VIDE si p est vide. Dans ce cas, la pile n'est pas
       modifiée
*/
erreur_pile depiler(PileEntiers *p, int *resultat){
    if(p==NULL)
        return POINTEUR_NUL;
    if(p->n==0)
        return PILE_VIDE;
    *resultat=p->tab[p->n-1];
    p->n--;
    return OK;
}