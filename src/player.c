#include "player.h"

/* Fichier de gestion du player (déplacements et actions) */


// déplacement vers le bas
void moveDown(listEntite* hero){
	if((*hero)->y<= MIN_HEIGHT)// si le mouvement fait sortir le joueur en bas de la fenêtre 
	{
		(*hero)->y=MIN_HEIGHT; // le joueur reste à sa position verticale minimum, ici 0 comme défini dans player.h
	}
	else {
		(*hero)->y-=(*hero)->speedMove_y; //sinon on bouge vers le bas le joueur de sa "vitesse", c'est à dire l'ampleur de son mouvement
	}
}

// déplacement vers le haut
void moveUp(listEntite* hero){
	if((*hero)->y>= MAX_HEIGHT-1) // si le mouvement du joueur le fait sortir par le haut de la fenêtre, ici 24-1 car une image fait 24 pixels de haut, et le joueur est un carré de 1x1 dont la position est déterminée par sa valeur du bas
	{
		(*hero)->y=MAX_HEIGHT-1; // le joueur reste à sa position verticale maximum
	}
	else {
		(*hero)->y+=(*hero)->speedMove_y; //sinon on bouge vers le haut le joueur de l'ampleur de son mouvement
	}
}

/* comme expliqué dans le rapport ainsi que dans player.h, à l'origine le joueur pouvait bouger son personnage dans tous les sens mais la consigne était que le défilement horizontal soit automatisé

void moveLeft(listEntite* hero){
	if((*hero)->x<= 0+1)
	{
		(*hero)->x=0+1; 
	}
	else {
		(*hero)->x-=(*hero)->speedMove_x; 
	}
}

void moveRight(listEntite* hero){
	if((*hero)->x>= WINDOW_WIDTH) 
	{
		(*hero)->x=WINDOW_WIDTH-1; 
	}
	else {
		(*hero)->x+=(*hero)->speedMove_x; 
}
}
*/


// Déplacement des projectiles
void moveProjectile(Projectiles projectile)
{
  while (projectile != NULL) // on vérifie que la liste est bien remplie
  {
  	if(projectile->type == 'P') 
    {
    	projectile->x+=0.2;
	}
	else  // condition pour distinguer les projectiles ennemis de ceux du joueur, si c'est un ennemi il faut qu'ils partent dans l'autre sens
	{
		projectile->x-=0.2;
	}
	projectile = projectile->nextEntite; 
  }

}


/*le déplacement des ennemis est automatisé
par défaut, speedMove_y est positive donc l'ennemi va vers le haut
cependant, s'il rencontre un obstacle, la valeur devient négative, ce qui fait que l'ennemi se déplace maintenant vers le bas
*/
void moveEnnemi(listEntite* ennemi, listEntite* projectile){
	listEntite tmp = *ennemi;
  	while (tmp != NULL)
  {
   	 if((tmp->y<=0) || tmp->y>=MAX_HEIGHT-1)
  	{
    	tmp->speedMove_y = -tmp->speedMove_y;   
  	}
    tmp->y += tmp->speedMove_y;
    tmp = tmp->nextEntite;
  }
}



