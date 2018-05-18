#ifndef GAME__H
#define GAME__H

#include "entite.h"
#include "display.h"
#include "player.h"

/* structure game comprenant le joueur, les obstacles, les ennemis, les missiles */

typedef struct game
{
  listEntite player, listObstacle, listEnnemi, listProjectiles;
}Game;

/* fonctions de gestion du game */

// fonction qui initialise les listes du game
void initializeGame(Game *game);

// fonction qui libère le Game
void freeGame(Game *game);

// fonction qui ajoute une entité au Game
void addEntiteToGame(Game *game, Entite entite);

// fonction qui supprime une entite du game
void removeEntiteFromGame(Game *game, Entite *entite);

// fonction de chargement du level avec la PPM
int ReadPPM(char * filename, Obstacle* Obstacle, Ennemi* Ennemi, Projectiles* Projectiles);

#endif
