#include <stdio.h>
#include <stdlib.h>

#include "file.h"

File* creer_file()
{
    File *f = malloc(sizeof(File));
    f->tete   = NULL;
    f->queuee  = NULL;
    f->taille = 0;
    return f;
}


void enfiler(File *f, carte *c)
{
    c->suivant = NULL;
    if (file_vide(f))
    {
        f->tete = c;
        f->queuee = c;
    }
    else
    {
        f->queuee->suivant = c;
        f->queuee = c;
    }
    f->taille++;
}


carte* defiler(File *f)
{
    if (file_vide(f))
    {
        return NULL;
    }
    carte *carte_jouee = f->tete;
    f->tete = f->tete->suivant;
    if (f->tete == NULL)
    {
        f->queuee = NULL;
    }
    carte_jouee->suivant = NULL;
    f->taille--;
    return carte_jouee;
}


int file_vide(File *f)
{
    return (f->taille == 0);
}


int taille_file(File *f)
{
    return f->taille;
}


void afficher_file(File *f)
{
    if (file_vide(f))
        return;
    carte *tmp = f->tete;
    while (tmp != NULL)
    {
        printf("[%d de %s] -> ", tmp->valeur, tmp->couleur);
        tmp = tmp->suivant;
    }
    printf("NULL\n");
}


void liberer_file(File *f)
{
    carte *tmp;
    while (!file_vide(f))
    {
        tmp = defiler(f);   // on retire chaque carte
        free(tmp);          // on libère sa mémoire
    }
    free(f);
}

