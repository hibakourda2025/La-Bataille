# 🃏 La Bataille — Jeu de Cartes en C

> Implémentation complète du jeu de cartes **La Bataille** en langage C,  
> avec gestion dynamique de la mémoire via listes chaînées, file (queue) et pile (stack).

## 🎯 Objectif du projet

- Manipuler les **pointeurs** en C avec rigueur
- Implémenter des **structures de données dynamiques** : liste chaînée, file, pile
- Décomposer un problème complexe en **fonctions indépendantes**
- Gérer la **mémoire dynamique** (`malloc` / `free`) sans fuites
- Écrire du code **propre, commenté et modulaire**

---

## 🃏 Règles du Jeu

1. Un jeu de **52 cartes** est mélangé aléatoirement puis distribué : **26 cartes par joueur**
2. À chaque manche, chaque joueur retourne la **première carte** de sa pile
3. Le joueur avec la carte de **plus haute valeur** remporte les deux cartes
4. En cas d'**égalité (Bataille)** :
   - Chaque joueur pose **1 carte cachée** et **1 carte visible**
   - La plus haute carte visible remporte **toutes** les cartes posées
   - Si nouvelle égalité → nouvelle bataille récursive
5. Le joueur qui **possède toutes les cartes** gagne
6. Un joueur qui n'a **plus de cartes** perd immédiatement
7. Limite de **200 manches** — le joueur avec le plus de cartes gagne

---

## 🏗️ Structure du Projet
```bash
bataille/
│
├── main.c
├── carte.h
├── liste.c
├── liste.h
├── file.c
├── file.h
├── pile.c
├── pile.h
├── jeu.c
├── jeu.h
└── stats.txt
```
---

## 🧱 Architecture Technique

### Structure de base — `Carte`

```c
typedef struct Carte {
    int valeur;          // 2 à 14 (As = 14)
    char couleur[10];    // coeur, carreau, trefle, pique
    struct Carte *suivant;
} carte;
```

Chaque carte est un **nœud** qui peut être chaîné dans une liste, une file ou une pile.

---

### 📦 Liste Chaînée — `liste.c / liste.h`

Utilisée pour représenter le **paquet initial de 52 cartes** avant distribution.

| Fonction | Description |
|---|---|
| `creer_carte(valeur, couleur)` | Alloue et retourne une nouvelle carte |
| `ajout_carte(tete, valeur, couleur)` | Insère une carte en queue de liste |
| `creerPaquet()` | Génère les 52 cartes en ordre |
| `melanger_paquet(tete)` | Mélange aléatoirement avec l'algorithme **Fisher-Yates** |
| `affiche_liste(tete)` | Affiche toutes les cartes de la liste |
| `liberer_liste(tete)` | Libère toute la mémoire de la liste |

**Algorithme de mélange :** Fisher-Yates — copie les pointeurs dans un tableau temporaire, effectue les échanges aléatoires, puis reconstruit la liste chaînée dans le nouvel ordre.

---

### 📂 File (Queue) FIFO — `file.c / file.h`

Utilisée pour modéliser la **main de chaque joueur**.  
Le joueur joue toujours la première carte (tête), et les cartes gagnées s'ajoutent en queue.

```c
typedef struct file {
    carte *tete;
    carte *queuee;
    int taille;
} File;
```

| Fonction | Description |
|---|---|
| `creer_file()` | Crée une file vide |
| `enfiler(f, c)` | Ajoute une carte en queue |
| `defiler(f)` | Retire et retourne la carte en tête |
| `file_vide(f)` | Retourne 1 si vide, 0 sinon |
| `taille_file(f)` | Retourne le nombre de cartes |
| `afficher_file(f)` | Affiche toutes les cartes du joueur |
| `liberer_file(f)` | Libère toute la mémoire (cartes + structure) |

---

### 🗃️ Pile (Stack) LIFO — `pile.c / pile.h`

Utilisée pour stocker temporairement les **cartes pendant une bataille** (égalité).

```c
typedef struct pile {
    carte *sommet;
    int taille;
} Pile;
```

| Fonction | Description |
|---|---|
| `creer_pile()` | Crée une pile vide |
| `empiler(p, c)` | Pose une carte au sommet |
| `depiler(p)` | Retire la carte du sommet |
| `pile_vide(p)` | Retourne 1 si vide, 0 sinon |
| `taille_pile(p)` | Retourne le nombre de cartes |
| `vider_dans_file(p, f)` | Transfère toutes les cartes vers la file du gagnant |
| `liberer_pile(p)` | Libère la mémoire de la pile |

---

### 🎮 Logique du Jeu — `jeu.c / jeu.h`

```c
typedef struct joueur {
    char nom[50];
    File *main;
} Joueur;
```

| Fonction | Description |
|---|---|
| `creer_joueur(nom)` | Initialise un joueur avec son nom et une file vide |
| `distribuer(paquet, j1, j2)` | Distribue 26 cartes à chaque joueur |
| `jouer_manche(j1, j2, tour, batailles)` | Joue un tour complet |
| `gerer_bataille(j1, j2, batailles)` | Gère la manche spéciale d'égalité (récursif) |
| `fin_de_partie(j1, j2, tour)` | Détecte la fin de partie |
| `afficher_tableau_bord(j1, j2, tour)` | Affiche le score à chaque manche |
| `boucle_jeu(j1, j2)` | Boucle principale du jeu |
| `sauvegarder_stats(...)` | Sauvegarde les statistiques dans `stats.txt` |
| `liberer_joueur(j)` | Libère la mémoire du joueur |

---

## 🖥️ Exemple d'affichage
```txt
╔══════════════════════════════════════╗
║       JEU DE LA BATAILLE v1.0        ║
╚══════════════════════════════════════╝

--- MANCHE 12 ---

Farah joue : [13 de pique]
Hiba joue : [13 de coeur]

>>> BATAILLE !

Farah découvre : [5 de trefle]
Hiba découvre : [9 de carreau]

>>> Hiba remporte la bataille !
```
---

## 📊 Fonctionnalités Bonus

- **Pause interactive** tous les 50 tours — le joueur qui perd peut abandonner
- **Sauvegarde des statistiques** dans `stats.txt` (date, joueurs, vainqueur, manches, batailles)
- **Gestion des batailles récursives** (double, triple, égalité)
- **Forfait automatique** si un joueur n'a pas assez de cartes pour une bataille

---

## 👤 Auteur

**Hiba Kourda**  
Etudiente en Business Intelligence — IHEC Carthage  
