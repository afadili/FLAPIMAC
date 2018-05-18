#ifndef ENTITE__H
#define ENTITE__H

/* Amina FADILI - Laurine Sajdak */
/* Projet FLAPIMAC */
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

typedef struct boundingBox{
	float pMinx, pMaxx, pMiny, pMaxy;
}bBox;


typedef struct entite
{
  int life; // nombre de vies
  int type; // (code de joueur : 1 pour player / 2 pour ennemi / 3 pour obstacle / 4 pour missiles )
  float x,y; // position de l'entité
  float vitesseX, vitesseY; // vitesse de l'entité par rapport à l'axe des x et celui des y
  //bBox box; // la boundingBox pour gérer les collisions de l'entité
  struct entite *nextEntite; // liste chainée d'entitée pour la gestion du Jeu
}Entite, *listEntite, *Player, *Obstacle, *Ennemi, *Missiles;

// fonctions de gestion de l'entité
 Entite* allocEntite(int life, int type, float x, float y, float vitesseX, float vitesseY/*, bBox box*/);


// Fonction qui ajoute une entité de type obstacle à la liste d'obstacles
void addObstacleToList(Entite* entite, Obstacle *liste);

// Fonction qui ajoute une entité de type ennemi à la liste d'ennemies
void addEnnemiToList(Entite* entite, Ennemi *liste);

// Fonction qui ajoute une entité de type missiles à la liste de Missiles
void addMissilesToList(Entite* entite, Missiles *liste);

// Fonction qui supprime une entité de type obstacle de la liste d'obstacles
void removeObstacleFromList(Entite* entite, Obstacle *liste);

// Fonction qui supprime une entité de type ennemi de la liste d'ennemies
void removeEnnemiFromList(Entite* entite, Ennemi *liste);

// Fonction qui supprime une entité de type missiles de la liste de Missiles
void removeMissilesFromList(Entite* entite, Missiles *liste);

// Fonction qui libère la mémoire de la liste d'obstacles
void freeObstacleList(Obstacle *liste);

// Fonction qui libère la mémoire de la liste d'ennemis
void freeEnnemiList(Ennemi *liste);

// Fonction qui libère la mémoire de la liste de Missiles
void freeMissilesList(Missiles *liste);

// fonction de gestion des collisions

#endif
