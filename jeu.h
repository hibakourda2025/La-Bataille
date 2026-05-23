#ifndef jeu_h
#define jeu_h
#include <string.h>
#include "carte.h"
#include "file.h"
#include "pile.h"
#include "liste.h"

typedef struct joueur
{
    char nom[50];   /* nom du joueur */
    File *main;     /* file de cartes du joueur dans la main */
} Joueur;


/* Prototypes */

Joueur* creer_joueur(char *nom);

void distribuer(carte *paquet, Joueur *j1, Joueur *j2);

void jouer_manche(Joueur *j1, Joueur *j2, int tour, int *batailles);

void gerer_bataille(Joueur *j1, Joueur *j2, int *batailles);

int fin_de_partie(Joueur *j1, Joueur *j2, int tour);

void afficher_tableau_bord(Joueur *j1, Joueur *j2, int tour);

void sauvegarder_stats(Joueur *j1, Joueur *j2,char *gagnant, int manches , int batailles);

void boucle_jeu(Joueur *j1, Joueur *j2);

void liberer_joueur(Joueur *j);


#endif // jeu.h
