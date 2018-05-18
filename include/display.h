#ifndef DISPLAY__H
#define DISPLAY__H
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "game.h"
#include "entite.h"
#include "display.h"
#include "player.h"
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800


/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

 // fonction qui dessine un carré à une position donnée

 void drawSquare(int full, float x, float y);

/* Fonction qui sert à redimensionner la fenêtre */
void resizeViewport();

/* Fonctions qui dessinent les entites d'une liste */
void drawEntite(listEntite entite);

/* Fonction qui dessine le backgroud du jeu */
void drawBG();

#endif
