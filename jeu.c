#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "jeu.h"

Joueur* creer_joueur(char *nom)
{
    Joueur *j = malloc(sizeof(Joueur));
    strcpy(j->nom, nom);
    j->main = creer_file();
    return j;
}


void distribuer(carte *paquet, Joueur *j1, Joueur *j2)
{
    carte *actuelle = paquet;
    carte *suivante;
    int compteur = 0;

    while (actuelle != NULL)
    {
        suivante = actuelle->suivant;
        actuelle->suivant = NULL;

        if (compteur % 2 == 0)
            enfiler(j1->main, actuelle);
        else
            enfiler(j2->main, actuelle);

        compteur++;
        actuelle = suivante;
    }
}


void afficher_tableau_bord(Joueur *j1, Joueur *j2, int tour)
{
    printf("\n=======================================\n");
    printf("|       JEU DE LA BATAILLE v1.0        |\n");
    printf("========================================\n");
    printf("  --- MANCHE %d ---\n", tour);
    printf("  Score -> %s: %d cartes | %s: %d cartes\n",j1->nom, taille_file(j1->main),j2->nom, taille_file(j2->main));
    printf("=========================================\n\n");
}


void jouer_manche(Joueur *j1, Joueur *j2, int tour , int *batailles)
{

    getchar();
    afficher_tableau_bord(j1, j2, tour);

    carte *c1 = defiler(j1->main);
    carte *c2 = defiler(j2->main);

    printf("%s joue : [%d de %s]\n",j1->nom, c1->valeur, c1->couleur);
    printf("%s joue : [%d de %s]\n",j2->nom, c2->valeur, c2->couleur);

    if (c1->valeur > c2->valeur)
    {
        printf(">>> %s remporte la manche ! (+2 cartes)\n", j1->nom);
        enfiler(j1->main, c1);
        enfiler(j1->main, c2);

    }
    else if (c2->valeur > c1->valeur)
    {
        printf(">>> %s remporte la manche ! (+2 cartes)\n", j2->nom);
        enfiler(j2->main, c2);
        enfiler(j2->main, c1);

    }
    else
    {
        printf(">>> BATAILLE !\n");
        printf("\a");
        enfiler(j1->main, c1);
        enfiler(j2->main, c2);
        gerer_bataille(j1, j2, batailles);
    }
}


void gerer_bataille(Joueur *j1, Joueur *j2, int *batailles)
{
    (*batailles)++;
    Pile *p = creer_pile();

    /* verification joueur 1 */
    if (taille_file(j1->main) < 2)
    {
        printf(">>> %s n'a pas assez de cartes pour la bataille !\n",j1->nom);
        printf(">>> %s remporte la bataille par forfait !\n", j2->nom);
        vider_dans_file(p, j2->main);
        return;
    }

    /* verification joueur 2 */
    if (taille_file(j2->main) < 2)
    {
        printf(">>> %s n'a pas assez de cartes pour la bataille !\n",j2->nom);
        printf(">>> %s remporte la bataille par forfait !\n", j1->nom);
        vider_dans_file(p, j1->main);
        return;
    }

    /* cartes egales dans la pile */
    carte *c1 = defiler(j1->main);
    carte *c2 = defiler(j2->main);
    empiler(p, c1);
    empiler(p, c2);

    /* cartes cachees */
    carte *cachee1 = defiler(j1->main);
    carte *cachee2 = defiler(j2->main);
    empiler(p, cachee1);
    empiler(p, cachee2);
    printf(">>> Cartes cachees posees...\n");

    /* cartes visibles */
    carte *visible1 = defiler(j1->main);
    carte *visible2 = defiler(j2->main);
    empiler(p, visible1);
    empiler(p, visible2);

    printf("%s decouvre : [%d de %s]\n",j1->nom, visible1->valeur, visible1->couleur);
    printf("%s decouvre : [%d de %s]\n",j2->nom, visible2->valeur, visible2->couleur);

    if (visible1->valeur > visible2->valeur)
    {
        printf(">>> %s remporte la bataille ! (+%d cartes)\n",j1->nom, taille_pile(p));
        vider_dans_file(p, j1->main);

    }
    else if (visible2->valeur > visible1->valeur)
    {
        printf(">>> %s remporte la bataille ! (+%d cartes)\n",j2->nom, taille_pile(p));
        vider_dans_file(p, j2->main);

    }
    else
    {
        printf(">>> ENCORE UNE BATAILLE !\n");
        printf("\a");
        vider_dans_file(p, j1->main);
        gerer_bataille(j1, j2,batailles);
    }
}


int fin_de_partie(Joueur *j1, Joueur *j2, int tour)
{
    /* joueur 1 n'a plus de cartes */
    if (file_vide(j1->main))
    {
        printf("\n>>> %s n'a plus de cartes !\n", j1->nom);
        printf(" %s remporte la partie !\n", j2->nom);
        return 1;
    }

    /* joueur 2 n'a plus de cartes */
    if (file_vide(j2->main))
    {
        printf("\n>>> %s n'a plus de cartes !\n", j2->nom);
        printf(" %s remporte la partie !\n", j1->nom);
        return 1;
    }

    /* 200 manches atteintes */
    if (tour >= 200)
    {
        printf("\n>>> 200 manches atteintes !\n");
        if (taille_file(j1->main) > taille_file(j2->main))
            printf(" %s remporte la partie avec %d cartes !\n",j1->nom, taille_file(j1->main));
        else
            printf(" %s remporte la partie avec %d cartes !\n",j2->nom, taille_file(j2->main));
        return 1;
    }

    /* la partie continue */
    return 0;
}


void sauvegarder_stats(Joueur *j1, Joueur *j2,char *gagnant, int manches,int batailles)
{
    /* ouvrir le fichier en mode ajout */
    FILE *fichier = fopen("stats.txt", "a");

    if (fichier == NULL)
    {
        printf("Erreur : impossible d'ouvrir stats.txt !\n");
        return;
    }

    /* recuperer la date et l'heure */
    time_t maintenant = time(NULL);
    struct tm *t = localtime(&maintenant);

    /* ecrire les statistiques */
    fprintf(fichier, "\n═══════════════════════════════════════\n");
    fprintf(fichier, "       STATISTIQUES DE LA PARTIE\n");
    fprintf(fichier, "═══════════════════════════════════════\n");
    fprintf(fichier, "Date et heure     : %02d/%02d/%04d - %02d:%02d\n",
            t->tm_mday, t->tm_mon + 1, t->tm_year + 1900,
            t->tm_hour, t->tm_min);
    fprintf(fichier, "Joueur 1          : %s\n", j1->nom);
    fprintf(fichier, "Joueur 2          : %s\n", j2->nom);
    fprintf(fichier, "Vainqueur         : %s\n", gagnant);
    fprintf(fichier, "Nombre de manches : %d\n", manches);
    fprintf(fichier, "Nombre de batailles : %d\n", batailles);
    fprintf(fichier, "Cartes finales %s : %d\n",
            j1->nom, taille_file(j1->main));
    fprintf(fichier, "Cartes finales %s : %d\n",
            j2->nom, taille_file(j2->main));
    fprintf(fichier, "═══════════════════════════════════════\n");

    fclose(fichier);

    printf("\n>>> Statistiques sauvegardees dans stats.txt \n");
}


void boucle_jeu(Joueur *j1, Joueur *j2)
{

    int tour = 0;
    int batailles = 0;
    char reponse;
    char *gagnant;

    printf("\n>>> La partie commence entre %s et %s !\n",j1->nom, j2->nom);
    printf("\a");

    while (!fin_de_partie(j1, j2, tour))
    {
        tour++;

        /* jouer une manche */
        jouer_manche(j1, j2, tour, &batailles);

        /* pause tous les 50 tours */
        if (tour % 50 == 0 && tour < 200)
        {
            printf("\n======================================\n");
            printf("     PAUSE - %d manches jouees\n", tour);
            printf("=====================================\n");
            printf("  Score -> %s: %d cartes | %s: %d cartes\n",j1->nom, taille_file(j1->main),j2->nom, taille_file(j2->main));

            /* on demande au joueur qui perd */
            Joueur *perdant;
            Joueur *gagnant_pause;

            if (taille_file(j1->main) < taille_file(j2->main))
            {
                perdant = j1;
                gagnant_pause = j2;
            }
            else
            {
                perdant = j2;
                gagnant_pause = j1;
            }

            printf("\n  %s, voulez-vous continuer la partie ? (O/N) : ",perdant->nom);
            scanf(" %c", &reponse);

            if (reponse == 'N' || reponse == 'n')
            {
                printf("\n>>> %s abandonne la partie !\n", perdant->nom);
                printf(" %s remporte la partie !\n", gagnant_pause->nom);
                printf("\a\a");
                sauvegarder_stats(j1, j2, gagnant_pause->nom,tour, batailles);
                return;
            }
            printf(">>> La partie continue !\n");
        }
    }

    /* determiner le gagnant final */
    if (file_vide(j1->main))
    {
        gagnant = j2->nom;
    }
    else if (file_vide(j2->main))
    {
        gagnant = j1->nom;
    }
    else
    {
        if (taille_file(j1->main)> taille_file(j2->main))
            gagnant =  j1->nom;
        else
            gagnant = j2->nom;
    }

    /* affichage fin de partie */
    printf("\n=======================================\n");
    printf("||          FIN DE LA PARTIE           || \n");
    printf("========================================\n");
    printf("  Nombre de manches  : %d\n", tour);
    printf("  Nombre de batailles: %d\n", batailles);
    printf("  Vainqueur       : %s\n", gagnant);
    printf("=========================================\n");
    printf("\a\a\a");

    /* sauvegarder les stats */
    sauvegarder_stats(j1, j2, gagnant, tour, batailles);
}


void liberer_joueur(Joueur *j)
{
    liberer_file(j->main);
    free(j);
}

