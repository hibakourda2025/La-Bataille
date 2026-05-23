#include <stdio.h>
#include <stdlib.h>
#include "pile.h"

Pile* creer_pile()
{
    Pile *p = malloc(sizeof(Pile));
    p->sommet = NULL;
    p->taille = 0;
    return p;
}

void empiler(Pile *p, carte *c)
{
    c->suivant = p->sommet;
    p->sommet  = c;
    p->taille++;
}

carte* depiler(Pile *p)
{
    if (pile_vide(p))
        return NULL;

    carte *c   = p->sommet;
    p->sommet  = p->sommet->suivant;
    c->suivant = NULL;
    p->taille--;
    return c;
}

int pile_vide(Pile *p)
{
    return (p->taille == 0);
}

int taille_pile(Pile *p)
{
    return p->taille;
}

void vider_dans_file(Pile *p, File *f)
{
    while (!pile_vide(p))
    {
        carte *c = depiler(p);
        enfiler(f, c);
    }
    free(p);
}

void liberer_pile(Pile *p)
{
    carte *tmp;
    while (!pile_vide(p))
    {
        tmp = depiler(p);
        free(tmp);
    }
    free(p);
}
