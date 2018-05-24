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

// Les fonctions qui dessinent chaque entité du jeu avec sa texture correspondante
  void drawPlayer(Hero player);
  void drawObstacle(Obstacle obstacle);
  void drawEnnemi(Ennemi ennemi);
  void drawProj(Projectiles proj);
  void drawLine(Line line);
  void drawBonus(Bonus bonus);
  void drawYouWin();
  void drawYouLose();

  // Fonction qui retourne l'ID d'un fichier d'après son nom
  int getImgId(char* filename);

  // Fonction qui charge toutes les textures d'un dossier donné et retourne un tableau de ces textures
  int loadTexture(char* directory, GLuint textureID[]);

  // Fonction qui vérifie si une surface SDL est bien chargée
  int loaded(SDL_Surface* image);

  // Fonction qui dessine une texture sur un carré
  void drawTexturedSquare(GLuint textureID) ;

  // Fonction qui dessine le menu du jeu
  void texturedMenu();

#endif
