#ifndef PLAYER__H
#define PLAYER__H

#include "entite.h"
#include "display.h"
#include "player.h"
#include "game.h"

//empêcher le joueur de quitter le terrain, valeurs à modifier en fonction de la taille de la fenêtre
#define MAX_HEIGHT 24
#define MIN_HEIGHT 0

/* Fichier de gestion du joueur (déplacements et actions) */

// Déplacement du Joueur vers le haut
void moveUp(listEntite* hero);

// Déplacement du joueur vers le bas
void moveDown(listEntite* hero);

// Déplacement du joueur à gauche et à droite
void moveLeft(listEntite* hero);

void moveRight(listEntite* hero);

void moveEnnemiUp(Ennemi ennemi);

void moveEnnemiDown(Ennemi ennemi);

// Déplacement des projectiles
void moveProjectile(Projectiles projectile);

// Déplacement des Bonus ( à rajouter plus tard)
void moveBonus(listEntite* Bonus);

// changement des proriétés du joueur selon les bonus récupérés
void updateBonus(listEntite* hero);

// vérifie que la player ne sort pas de la fenetre, sinon le remet à sa place
void positionPlayer(listEntite* hero);

// vitesse du player à gérer

#endif
