#ifndef DISPLAY__H
#define DISPLAY__H
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800


/* Nombre de bits par pixel de la fenêtre */
static const unsigned int BIT_PER_PIXEL = 32;

/* Nombre minimal de millisecondes separant le rendu de deux images */
static const Uint32 FRAMERATE_MILLISECONDS = 1000 / 60;

 // fonction qui dessine un carré

void drawSquare(int full);

/* Fonction qui sert à redimensionner la fenêtre */
void resizeViewport();

#endif
