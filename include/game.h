#ifndef GAME__H
#define GAME__H

#include "entite.h"
#include "display.h"
#include "player.h"

/* structure game comprenant le joueur, les obstacles, les ennemis, les missiles */

typedef struct game
{
  listEntite player, listObstacle, listEnnemi, listProjectiles, listLine, listBonus;
}Game;

/* fonctions de gestion du game */

// fonction qui dessine le game
void drawGame(Game game);

// fonction qui initialise les listes du game
void initializeGame(Game *game);

// fonction qui libère le Game
void freeGame(Game *game);

// Fonction qui ajoute la ligne d'arrivée à une liste
void addLineToList(Entite* entite, Line *liste);

// Fonction qui ajoute un bonus à une liste
void addBonusToList(Entite* entite, Bonus *liste);

// fonction de chargement du level avec la PPM
int ReadPPM(char * filename,Game *game);


#endif
