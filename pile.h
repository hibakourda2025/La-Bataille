#ifndef pile_h
#define pile_h

#include "carte.h"
#include "file.h"

typedef struct pile
{
    carte *sommet;
    int taille;
} Pile;

Pile* creer_pile();

void empiler(Pile *p, carte *c);

carte* depiler(Pile *p);

int pile_vide(Pile *p);

int taille_pile(Pile *p);

void vider_dans_file(Pile *p, File *f);

void liberer_pile(Pile *p);



#endif // pile_h
