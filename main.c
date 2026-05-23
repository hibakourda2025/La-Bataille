#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "carte.h"
#include "liste.h"
#include "file.h"
#include "pile.h"
#include "jeu.h"

int main()
{
    char nom1[50];
    char nom2[50];

    /* affichage du titre */
    printf("========================================\n");
    printf("|       JEU DE LA BATAILLE v1.0        |\n");
    printf("========================================\n\n");

    /* saisie des noms */
    printf("Entrez le nom du Joueur 1 : ");
    scanf("%s", nom1);
    printf("Entrez le nom du Joueur 2 : ");
    scanf("%s", nom2);

    /* creation des joueurs */
    Joueur *j1 = creer_joueur(nom1);
    Joueur *j2 = creer_joueur(nom2);

    /* creation du paquet */
    carte *paquet = creerPaquet();

    /* melange du paquet */
    paquet = melanger_paquet(paquet);

    /* distribution des cartes */
    distribuer(paquet, j1, j2);

    printf("\n>>> Cartes distribuees !\n");
    printf(">>> %s : %d cartes\n", j1->nom, taille_file(j1->main));
    printf(">>> %s : %d cartes\n\n", j2->nom, taille_file(j2->main));

    /* lancement du jeu */
    boucle_jeu(j1, j2);

    /* liberation memoire */
    liberer_joueur(j1);
    liberer_joueur(j2);

    return 0;
}
