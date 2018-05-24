#ifndef PLAYER__H
#define PLAYER__H

#include "entite.h"
#include "display.h"
#include "player.h"
#include "game.h"

//empêcher le joueur de quitter le terrain, en bas 0 et en haut 24, hauteur en pixels de chaque map ppm
#define MAX_HEIGHT 24
#define MIN_HEIGHT 0

/* Fichier de gestion du joueur (déplacements et actions) */

// Déplacement du Joueur vers le haut
void moveUp(listEntite* hero);

// Déplacement du joueur vers le bas
void moveDown(listEntite* hero);

/* Déplacement du joueur à gauche et à droite
 à noter que ces fonctions n'ont au final pas été utilisées, en effet il est précisé dans le sujet que le joueur se déplace de manière horizontale automatiquement
void moveLeft(listEntite* hero);

void moveRight(listEntite* hero);*/

// déplacement vertical des ennemis, prends aussi en compte les collisions avec les obstacles pour automatiser le mouvement de haut en bas ou de bas en haut
void moveEnnemi(listEntite* ennemi, listEntite* projectile);
void moveEnnemiUpDown(Entite* ennemi);

// Déplacement des projectiles
void moveProjectile(Projectiles projectile);



#endif
