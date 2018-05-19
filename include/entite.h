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
  char type; // (H pour hero, E pour ennemi, O pour obstacle, P pour projectile)
  float x,y; // position de l'entité
  float vitesseX, vitesseY; // vitesse de l'entité par rapport à l'axe des x et celui des y
  //bBox box; // la boundingBox pour gérer les collisions de l'entité
  struct entite *nextEntite; // liste chainée d'entitée pour la gestion du Jeu
}Entite, *listEntite, *Hero, *Obstacle, *Ennemi, *Projectiles;

// fonctions de gestion de l'entité
 Entite* allocEntite(int life, char type, float x, float y, float vitesseX, float vitesseY/*, bBox box*/);


// Fonction qui ajoute une entité de type obstacle à la liste d'obstacles
void addObstacleToList(Entite* entite, Obstacle *liste);

// Fonction qui ajoute une entité de type ennemi à la liste d'ennemies
void addEnnemiToList(Entite* entite, Ennemi *liste);

// Fonction qui ajoute une entité de type missiles à la liste de Missiles
void addProjectilesToList(Entite* entite, Projectiles *liste);

// Fonction qui supprime une entité de type obstacle de la liste d'obstacles
void removeObstacleFromList(Entite* entite, Obstacle *liste);

// Fonction qui supprime une entité de type ennemi de la liste d'ennemies
void removeEnnemiFromList(Entite* entite, Ennemi *liste);

// Fonction qui supprime une entité de type missiles de la liste de Projectiles
void removeProjectilesFromList(Entite* entite, Projectiles *liste);

// Fonction qui libère la mémoire de la liste d'obstacles
void freeObstacleList(Obstacle *liste);

// Fonction qui libère la mémoire de la liste d'ennemis
void freeEnnemiList(Ennemi *liste);

// Fonction qui libère la mémoire de la liste de Projectiles
void freeProjectilesList(Projectiles *liste);

// fonction de gestion des collisions
int intersection(Entite a, Entite b);

int collision(listEntite a, listEntite* b);

#endif
