    #include "type_pile.h"
    #include <stdio.h>


    void creer_pile(PileEntiers *p)
    {
        p->n=0;
    }

    int est_vide(PileEntiers *p)
    {
        return (p->n == 0);
    }

    int sommet(PileEntiers *p)
    {
        if (est_vide(p)) {
            printf("Erreur : pile vide\n");
            return -1;
        }
        return p->tab[p->n-1];
    }

    int taille(PileEntiers *p)
    {
        return p->n;
    }

    void print(PileEntiers *p)
    {
        int i;
        printf("Contenu de la pile : ");
        for (i=0; i<p->n; i++) {
            printf("%d | ", p->tab[i]);
        }
        printf("\n");
    }

    void vider(PileEntiers *p)
    {
        while (!est_vide(p)) {
            depiler(p); 
        }
    }


    void empiler(PileEntiers *p, int x)
    {
        if (p->n == 100) {
            printf("Erreur : pile pleine\n");
            return;
        }
        p->tab[p->n] = x;
        p->n++;
    }
    int depiler(PileEntiers *p)
    {
        if (est_vide(p)) {
            printf("Erreur : pile vide\n");
            return -1;
        }
        int x = p->tab[p->n-1];
        p->n--;
        return x;
    }
