#ifndef ENTITE__H
#define ENTITE__H

/* Amina FADILI - Laurine Sajdak */
/* Projet FLAPIMAC */
#include <stdio.h>
#include <stdlib.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define MAX_SPEEDMOVE 2


typedef struct boundingBox{
	float pMinx, pMaxx, pMiny, pMaxy;
}bBox;


typedef struct entite
{
  int life; // nombre de vies
  int bonus;
  char type; // (H pour hero, E pour ennemi, O pour obstacle, P pour projectile, L pour line)
  float x,y; // position de l'entité
  float speedMove_x, speedMove_y; // vitesse de l'entité par rapport à l'axe des x et celui des y
  //bBox box; // la boundingBox pour gérer les collisions de l'entité
  struct entite *nextEntite; // liste chainée d'entitée pour la gestion du Jeu
}Entite, *listEntite, *Hero, *Obstacle, *Ennemi, *Projectiles, *Line, *Bonus;


// fonctions de gestion de l'entité
 Entite* allocEntite(int life, int bonus, char type, float x, float y, float speedMove_x, float speedMove_y/*, bBox box*/);


// Fonction qui ajoute une entité de type obstacle à la liste d'obstacles
void addObstacleToList(Entite* entite, Obstacle *liste);

// Fonction qui ajoute une entité de type ennemi à la liste d'ennemies
void addEnnemiToList(Entite* entite, Ennemi *liste);


// Fonction qui ajoute une entité de type projectile à la liste de projectiles
void addProjectilesToList(Entite* entite, Projectiles *liste);

// Fonction qui ajoute une entité player à la liste
void addPlayerTolist(Entite* entite, Hero* liste);

// Fonction qui ajoute une entité bonus à la liste de bonus
void addBonusTolist(Entite* entite, Bonus* bonus);

// Fonction qui ajoute une entité finalLine à la ligne de fin de jeu
void addLineTolist(Entite* entite, Line* liste);

// Fonction qui supprime une entité de type obstacle de la liste d'obstacles
void removeObstacleFromList(Entite* entite, Obstacle *liste);

// Fonction qui supprime une entité de type ennemi de la liste d'ennemis
void removeEnnemiFromList(Entite* entite, Ennemi *liste);

// Fonction qui supprime une entité de type projectile de la liste de Projectiles
void removeProjectilesFromList(Entite* entite, Projectiles *liste);

void removeLineFromList(Entite* entite, Line *liste);

void removeBonusFromList(Entite* entite, Bonus *liste);

// Fonction qui libère la mémoire de la liste d'obstacles
void freeObstacleList(Obstacle *liste);

// Fonction qui libère la mémoire de la liste d'ennemis
void freeEnnemiList(Ennemi *liste);

// Fonction qui libère la mémoire de la liste de Projectiles
void freeProjectilesList(Projectiles *liste);

// Fonction qui libère la mémoire de la liste de ligne d'arrivée
void freeLineList(Line *liste);

void freeBonusList(Bonus *liste);

// fonction de gestion des collisions
int intersection(Entite a, Entite b);

int checkCollision(listEntite e1, listEntite* e2);

int collision(Entite a, Entite b) ;


void moveEnnemiUpDown(Entite* ennemi);



#endif
