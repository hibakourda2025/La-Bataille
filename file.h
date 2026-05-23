#ifndef file_h
#define file_h

#include "carte.h"

typedef struct file
{
    carte *tete;
    carte *queuee;
    int taille;
} File;

File* creer_file();  // créer une file vide

void enfiler(File *f, carte *c);  // ajouter une carte à la fin

carte* defiler(File *f);  // retirer la carte en tête

int file_vide(File *f);  // vérifie si la file est vide ( 1 si vide, 0 sinon)

int taille_file(File *f);  //  retourne le nombre de cartes

void afficher_file(File *f);  // affiche toutes les cartes du joueur (de la tête vers la queue)

void liberer_file(File *f);  // libère toute la mémoire de la file (libère chaque carte + la structure File elle-même)


#endif // file.h
