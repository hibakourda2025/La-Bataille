#include <stdio.h>  // print
#include <stdlib.h> // malloc et free
#include <string.h> // strcpy
#include <time.h>  // pour mélanger la carte aléatoirement

#include "liste.h"

carte* creer_carte(int valeur, char couleur[])   // cree une nouvelle carte
{
    carte* nouvelle;  // declaration
    nouvelle = malloc(sizeof(carte));  // allocation memoire
    nouvelle -> valeur = valeur;
    strcpy(nouvelle->couleur,couleur);
    nouvelle -> suivant = NULL;
    return nouvelle;
}


carte* ajout_carte(carte* tete, int valeur, char couleur[])   // ajouter une carte a fin de la liste (ajout fin)
{
    carte* nouvelle = creer_carte(valeur,couleur);
    if (tete==NULL)
        tete= nouvelle;
    else
    {
        carte* parcours=tete;
        while(parcours->suivant!=NULL)
        {
            parcours=parcours->suivant;
        }
        parcours->suivant=nouvelle;
    }
    return(tete);

}


carte* creerPaquet()
{
    carte* paquet = NULL;
    char couleurs[4][10] = {"coeur", "carreau", "trefle", "pique"};
    for (int i=0;i<4;i++)
    {
        for (int j=2;j<=14;j++)
        {
            paquet = ajout_carte(paquet,j,couleurs[i]);
        }
    }
    return paquet;
}


carte* melanger_paquet(carte *tete)
{
    // Si la liste est vide, rien à faire, on retourne NULL
    if (tete == NULL) return NULL;

    // Compter le nombre de cartes
    int n = 0;
    carte* tmp = tete;
    while (tmp != NULL)
    {
        n++;
        tmp = tmp->suivant;
    }

    /* Copier les adresses dans un tableau temporaire (on met les ADRESSES (pointeurs) de chaque
    carte dans un tableau, on mélange le tableau, puis on reconstruit la liste dans le nouvel ordre)*/

    carte **tableau = malloc(n * sizeof(carte*));
    tmp = tete;
    for (int i = 0; i < n; i++) {
        tableau[i] = tmp;       // on sauvegarde l'adresse de la carte i
        tmp = tmp->suivant;     // on passe à la carte suivante
    }

    /* Algorithme de Fisher-Yates: on parcourt le tableau de la fin vers le début.
    À chaque position i, on choisit un indice j aléatoire entre 0 et i, puis on échange tableau[i] et tableau[j]*/

    srand(time(NULL));
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);  //j est entre 0 et i inclus
        carte *temp = tableau[i];  //Échange de tableau[i] et tableau[j]
        tableau[i]  = tableau[j];
        tableau[j]  = temp;
    }

    //Reconstruire la liste chaînée dans le nouvel ordre

    for (int i = 0; i < n - 1; i++)
    {
        tableau[i]->suivant = tableau[i + 1];
    }
    tableau[n - 1]->suivant = NULL;  // la dernière carte ne pointe vers rien
    carte *nouvelle_tete = tableau[0]; //La nouvelle tête de liste est tableau[0]
    free(tableau); // Libérer le tableau temporaire

    return nouvelle_tete;
}


void affiche_liste(carte* tete)  // afficher toutes les carte (pour verifier la liste)
{
    carte* parcours = tete;
    while (parcours!=NULL)
    {
        printf("%d de %s\n",parcours->valeur, parcours->couleur);
        parcours=parcours->suivant;
    }
}


void liberer_liste(carte* tete)
{
    carte* parcours;
    while (tete!=NULL)
    {
        parcours=tete;
        tete=tete->suivant;
        free(parcours);
    }
}

