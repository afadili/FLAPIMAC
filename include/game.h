#ifndef GAME__H
#define GAME__H

#include "entite.h"

/* structure game comprenant le joueur, les obstacles, les ennemis, les missiles */

typedef struct game
{
  listEntite player, listObsctacle, listEnnemi, listMissiles;
}Game;
//typedef struct Entite *listEntite;
/* fonctions de gestion du game */

// fonction qui initialise les listes du game
void initializeGame(Game *game);

// fonction qui libère le Game
void freeGame(Game *game);

// fonction qui ajoute une entité au Game
void addEntiteToGame(Game *game, Entite entite);

#endif
