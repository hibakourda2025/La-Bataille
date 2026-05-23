#ifndef liste_h
#define liste_h

#include "carte.h"

carte* creer_carte(int , char[]);   // cree une nouvelle carte

carte* ajout_carte(carte* , int , char[]);   // ajouter une carte a la liste en queue

carte* creerPaquet(); // creer un paquet de 52 cartes en ordre

carte* melanger_paquet(carte *tete); // mélange aléatoirement une liste chaînée de cartes en utilisant l'algorithme de Fisher-Yates

void affiche_liste(carte*);  // afficher toutes les cartes (pour verifier la liste)

void liberer_liste(carte*);  // liberation de la liste utiliser à la fin

#endif // liste.h
