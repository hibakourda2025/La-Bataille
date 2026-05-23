#ifndef carte_h
#define carte_h

typedef struct Carte
{
    int valeur; // 2 a 14 (As = 14)
    char couleur[10]; // coeur, carreau, trefle, pique
    struct Carte* suivant; // Pointeur vers la carte suivante
}carte;

#endif // carte_h
