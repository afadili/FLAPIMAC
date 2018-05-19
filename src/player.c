#include "player.h"

/* Fichier de gestion du joueur (déplacements et actions) */

// Déplacement du Joueur vers le haut
void moveUp(listEntite* player);

// Déplacement du joueur vers le bas
void moveDown(listEntite* player);

// Déplacement des projectiles
void moveProjectile(listProjectiles* projectile);

// Déplacement des Bonus ( à rajouter plus tard)
void moveBonus(listEntite* Bonus);

// changement des proriétés du joueur selon les bonus récupérés
void updateBonus(listEntite* player);

// vérifie que la player ne sort pas de la fenetre, sinon le remet à sa place
void positionPlayer(listEntite* player);

// vitesse du player à gérer 
