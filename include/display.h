#ifndef DISPLAY__H
#define DISPLAY__H
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <time.h>
#include <math.h>
#include "game.h"
#include "entite.h"
#include "display.h"
#include "player.h"
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800
#define NBTEXTURES 11
extern GLuint textures[NBTEXTURES];



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

  //void drawSquareTexture(int full, char* filename);

  void drawPlayer(Hero player);
  void drawObstacle(Obstacle obstacle);
  void drawEnnemi(Ennemi ennemi);
  void drawProj(Projectiles proj);
  void drawLine(Line line);
  void drawBonus(Bonus bonus);
  void drawYouWin();
  void drawYouLose();

//  void loadTexture(int full, char* filename);

  int getImgId(char* filename);
  int loadTexture(char* directory, GLuint textureID[]);
  int loaded(SDL_Surface* image);
  void drawTexturedSquare(GLuint textureID) ;
  void texturedMenu();

 //void loadPictures(GLuint textureID, SDL_Surface* image);

 //void texturedMenu(GLuint textureID, SDL_Surface* image);


#endif
