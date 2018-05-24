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


/* typiquement, chaque entité possède :
-un nombre de points de vie 
-un compteur de bonus : 3 points par bonus récupéré qui vont permettre de détruire des obstacles
-un type 
-une position x et y
-speedMove_x et speedMove_y qui détermine l'ampleur du déplacement de chaque entité

on plusieurs type d'entités :
-listEntité qui permet la création des listes chainées
-hero : c'est notre joueur, Bob l'éponge Imac
-obstacle : va permettre de créer les murs
-ennemi : ici des méduses
-projectiles : disponibles  à l'infini, on va pouvoir les lancer sur les obstacles ou les ennemis. attention, on ne peut détruire un mur que si on possède des points bonus
-line : c'est la ligne d'arrivée, ici des ananas
-bonus : ici des pâtés de crabe
*/
typedef struct entite
{
  int life; 
  int bonus;
  char type; // (H pour hero, E pour ennemi, O pour obstacle, P pour projectile, L pour line)
  float x,y; // position de l'entité
  float speedMove_x, speedMove_y; 
  struct entite *nextEntite; // liste chainée d'entitée pour la gestion du Jeu
}Entite, *listEntite, *Hero, *Obstacle, *Ennemi, *Projectiles, *Line, *Bonus;


// on alloue la mémoire de chaque entité
 Entite* allocEntite(int life, int bonus, char type, float x, float y, float speedMove_x, float speedMove_y);


/**************************FONCTIONS D'AJOUT**********************************/
// Fonction qui ajoute une entité de type obstacle à la liste d'obstacles
void addObstacleToList(Entite* entite, Obstacle *liste);

// Fonction qui ajoute une entité de type ennemi à la liste d'ennemis
void addEnnemiToList(Entite* entite, Ennemi *liste);

// Fonction qui ajoute une entité de type projectile à la liste de projectiles
void addProjectilesToList(Entite* entite, Projectiles *liste);

// Fonction qui ajoute une entité hero à la liste : ici on n'a qu"un joueur donc la liste n'a qu'une entité
void addPlayerTolist(Entite* entite, Hero* liste);

// Fonction qui ajoute une entité bonus à la liste de bonus
void addBonusTolist(Entite* entite, Bonus* bonus);

// Fonction qui ajoute une entité finalLine à la ligne de fin de jeu
void addLineTolist(Entite* entite, Line* liste);



/**************************FONCTIONS DE SUPPRESSION**********************************/
// Fonction qui supprime une entité de type obstacle de la liste d'obstacles
void removeObstacleFromList(Entite* entite, Obstacle *liste);

// Fonction qui supprime une entité de type ennemi de la liste d'ennemis
void removeEnnemiFromList(Entite* entite, Ennemi *liste);

// Fonction qui supprime une entité de type projectile de la liste de Projectiles
void removeProjectilesFromList(Entite* entite, Projectiles *liste);

// Fonction qui supprime une entité finalLine à la ligne de fin de jeu
void removeLineFromList(Entite* entite, Line *liste);

// Fonction qui supprime une entité bonus à la liste de bonus
void removeBonusFromList(Entite* entite, Bonus *liste);


/**************************FONCTIONS DE LIBERATION**********************************/
// Fonction qui libère la mémoire de la liste d'obstacles
void freeObstacleList(Obstacle *liste);

// Fonction qui libère la mémoire de la liste d'ennemis
void freeEnnemiList(Ennemi *liste);

// Fonction qui libère la mémoire de la liste de Projectiles
void freeProjectilesList(Projectiles *liste);

// Fonction qui libère la mémoire de la liste de ligne d'arrivée
void freeLineList(Line *liste);

// Fonction qui libère la mémoire de la liste de bonus
void freeBonusList(Bonus *liste);

/**************************FONCTIONS DE COLLISION**********************************/

//on vérifie si deux entités entrent en collision
int collision(Entite a, Entite b) ;

//on effectue des actions en fonction du type d'éléments entrant en collision
int checkCollision(listEntite e1, listEntite* e2);






#endif
