#include "player.h"

/* Fichier de gestion du joueur (déplacements et actions) */


// déplacement vers le bas
void moveDown(listEntite* hero){
	if((*hero)->y<= MIN_HEIGHT+1)// si le mouvement fait sortir le joueur en bas de la fenêtre
	{
		(*hero)->y=MIN_HEIGHT+1; // le joueur reste à sa position verticale minimum
	}
	else {
		(*hero)->y-=(*hero)->speedMove_y; //sinon on bouge vers le bas le joueur de sa vitesse
	}
}

// déplacement vers le haut
void moveUp(listEntite* hero){
	if((*hero)->y>= MAX_HEIGHT-1) // si le mouvement du joueur le fait sortir par le haut de la fenêtre
	{
		(*hero)->y=MAX_HEIGHT-1; // le joueur reste à sa position verticale maximum
	}
	else {
		(*hero)->y+=(*hero)->speedMove_y; //sinon on bouge vers le haut le joueur de sa vitesse
	}
}

void moveLeft(listEntite* hero){
	if((*hero)->x<= 0+1)
	{
		(*hero)->x=0+1; 
	}
	else {
		(*hero)->x-=(*hero)->speedMove_x; 
	}
}

// déplacement vers le haut
void moveRight(listEntite* hero){
	if((*hero)->x>= WINDOW_WIDTH) 
	{
		(*hero)->x=WINDOW_WIDTH-1; 
	}
	else {
		(*hero)->x+=(*hero)->speedMove_x; 
}
}


// Déplacement des projectiles
void moveProjectile(Projectiles projectile)
{
  while (projectile != NULL)
  {
    projectile->x+=1;
    projectile = projectile->nextEntite;
  }

}

// Déplacement des Bonus ( à rajouter plus tard)
/*void moveBonus(listEntite* Bonus){
	listEntite tmpBonus = Bonus;
	while(tmpBonus){ // tant qu'on a un bonus
		if(tmpBonus->y<=MIN_HEIGHT || tmpBonus>=MIN_HEIGHT-1) // on veut vérifier que notre bonus se déplace bien au sein de la fenêtre
		{
			tmpBonus->speedMove_y=-tmpBonus->speedMove_y; // on donne une valeur négative pour que le mouvement se fasse dans l'autre sens
		}
		tmpBonus->y+=tmpBonus->speedMove_y; // on fait bouger notre bonus
		tmpBonus=tmpBonus->next; // on passe au bonus suivant
	}
}*/

// changement des proriétés du joueur selon les bonus récupérés
void updateBonus(listEntite* hero);

// vérifie que la player ne sort pas de la fenetre, sinon le remet à sa place
//void positionPlayer(listEntite* hero);

// vitesse du player à gérer
