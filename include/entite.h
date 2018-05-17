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
  //int type; // (code de joueur : 1 pour player / 2 pour ennemi / 3 pour obstacle / 4 pour missiles )
  float x,y; // position de l'entité
  bBox box; // la boundingBox pour gérer les collisions de l'entité
  entite *nextEntite; // liste chainée d'entitée pour la gestion du Jeu
}Entite, *listEntite, *Player, *Obstacle, *Ennemi, *Missiles;

// fonctions de gestion de l'entité
 Entite* allocEntite(int life, int type, float x, float y , bBox box);


void removeEntite(Entite entite)
{


}
*

#endif
