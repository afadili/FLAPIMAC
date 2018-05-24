#include "entite.h"

/* Fichier de gestion du jeu dans la mémoire */

// fonctions de gestion de chaque entité
// fonctions qui alloue la mémoire d'une entité,
// on initialise les champs avec les valeurs passées en paramètre


Entite* allocEntite(int life, int bonus, char type, float x, float y, float speedMove_y, float speedMove_x)
 {
  Entite* entite;
  entite = malloc(sizeof(Entite));
    if (entite == NULL)
     {
      printf("Allocation error !\n");
     }
    entite->life = life;
    entite->bonus = bonus;
    entite->type = type;
    entite->x = x;
    entite->y = y;
    entite->speedMove_x = speedMove_x;
    entite->speedMove_y = speedMove_y;
    entite->nextEntite=NULL;
    return entite;
   }


 // Fonction qui ajoute une entité player à la liste
void addPlayerTolist(Entite* entite, Hero* liste)
{
  printf("entre dans la fonction add player to list\n");
  Hero tmp;// on crée une liste tmp pour ne pas perdre le début de la chaine
  tmp = *liste; // le début de la chaine est gardé dans tmp
  if (tmp == NULL) // si la chaine est vide on ajoute l'entité
  {
    tmp = entite;
  }
  else // sinon on ajoute l'entite au début de la chaine
  {
    entite->nextEntite = tmp;
    tmp = entite;
  }
*liste = tmp;
}

void addObstacleToList(Entite* entite, Obstacle *liste)
{

  Obstacle tmp;// on crée une liste tmp pour ne pas perdre le début de la chaine
	tmp = *liste; // le début de la chaine est gardé dans tmp
	if (tmp == NULL) // si la chaine est vide on ajoute l'entité
  {
  	tmp = entite;
  }
  else // sinon on ajoute l'entite au début de la chaine
    {
  	entite->nextEntite = tmp;
  	tmp = entite;
  	}
  *liste = tmp;
}

void addEnnemiToList(Entite* entite, Ennemi *liste)
{
  Ennemi tmp;// on crée une liste tmp pour ne pas perdre le début de la chaine
	tmp = *liste; // le début de la chaine est gardé dans tmp
	if (tmp == NULL) // si la chaine est vide on ajoute l'entité
  {
  	tmp = entite;
  }
  else // sinon on ajoute l'entite au début de la chaine
  {
  	entite->nextEntite = tmp;
  	tmp = entite;
  }
  *liste = tmp;
}


void addProjectilesToList(Entite* entite, Projectiles *liste)
{
 	Projectiles tmp;// on crée une liste tmp pour ne pas perdre le début de la chaine
	tmp = *liste; // le début de la chaine est gardé dans tmp
	if (tmp == NULL) // si la chaine est vide on ajoute l'entité
  {
  	tmp = entite;
  }
  else // sinon on ajoute l'entite au début de la chaine
  {
  	entite->nextEntite = tmp;
  	tmp = entite;
  }
  *liste = tmp;
}

/*dans la fonction de collision, si l'ennemi entre en collision avec un obstacle, on inverse sa valeur de déplacement pour changer sa direction*/
void moveEnnemiUpDown(Entite* ennemi){
  ennemi->speedMove_y = -ennemi->speedMove_y;
  ennemi->y += ennemi->speedMove_y;
}

/* gestion des collisions
on parcourt nos deux listes pour vérifier si deux éléments de chaque liste entrent en collision 
on parcourt d'abord la liste passée en premier paramètre, puis celle passée en second paramètre
*/
int checkCollision(listEntite e1, listEntite* e2) {
	listEntite tmp1 = e1;
	listEntite tmp2 = *e2;
	while (tmp2) {
		while (e1) {
			if (collision(*e1, *tmp2) == 1) {
        //on enlève de la vie à un ennemi s'il est touché par un projectile, si sa vie tombe à 0 on le retire de la liste
        if((e1->type == 'P') && ((*e2)->type == 'E'))
        {
          tmp2->life-=1;
          printf("VIE ENNEMI : %d\n", tmp2->life);
          if(tmp2->life <= 0)
          {
            removeEnnemiFromList(tmp2, &((*e2)));
            printf("he's dead :(\n");
          } 
        }

        // si le joueur percute une entité de type bonus, celle-ci est retirée de la liste
        if(((*e2)->type == 'B') && e1->type == 'H')
        {
          removeBonusFromList(tmp2, &((*e2)));
        }
        //si l'ennemi rencontre un obstacle, il change de trajectoire
        if(((*e2)->type == 'E') && e1->type == 'O')
        {
          moveEnnemiUpDown(&((*tmp2)));
        }
        //on supprime le projectile s'il touche un obstacle sans que le joueur ait de bonus
				if((e1->type == 'O') && ((*e2)->type == 'P'))
				{
					removeProjectilesFromList(tmp2, &((*e2)));
				}
        // si le joueur a un bonus, on enlève de la vie à l'obstacle qui est supprimé s'il n'a plus de vie
        if((e1->type == 'P') && ((*e2)->type == 'O'))
        {
          tmp2->life-=1;
          if(tmp2->life == 0)
          {
            removeObstacleFromList(tmp2, &((*e2)));
          } 
        }
        // s'il y a eu une action suite à une collision, on renvoie 1, voir main.c
				return 1;
			}
      //on passe à l'entité suivante si aucune collision détectée
			e1 = e1->nextEntite;
		}
		e1 = tmp1;
		tmp2 = tmp2->nextEntite;
	}
	return 0;
}

/* Renvoie 1 si les deux éléments entrent en collision, 0 sinon */
int collision(Entite e1, Entite e2) {
	if((abs(e1.x-e2.x)*2 < 2) && (abs(e1.y-e2.y)*2 < 2)) 
	// étant donné qu'on a des carrés de 1x1, on vérifie que les deux carrés passés en paramètre ne se chevauchent pas
	// si le résultat est inférieur à 2, cela signife que les deux carrés se partagent au moins une coordonnée, et donc qu'il y a collision
	{
		return 1;
	}
	else
    return 0;
}

/**************FONCTIONS DE SUPPRESSION*********************/
// fonctions classiques qui supprime une entité passée en premier paramètre d'une liste passée en deuxième paramètre
void removeObstacleFromList(Entite* entite, Obstacle* liste)
{
    if (liste != NULL) // si la liste n'est pas déjà vide
    {
      if (entite == *liste)// si l'entite est à la tête de la liste
      {
        Entite *tmp = *liste; // on garde la tête de la liste dans un tmp
        *liste = (*liste)->nextEntite; // on pointe vers l'élement suivant de la chaine
        free(tmp); // on libère la mémoire du premier élement qui est notre entité
      }
      else // si l'entite est au milieu de la liste
      {
        Entite *tmp = (*liste)->nextEntite; // on garde un tmp pour parcourir la chaine
        Entite *prev = *liste; // on garde un pointeur vers l'élement pécédant le tmp
        while (entite != tmp) // tant qu'on n'a pas trouvé notre entité
        {
          prev = tmp; // on passe à l'entité suivante en gardant le précédant du tmp
          tmp = tmp->nextEntite;
        }
        prev->nextEntite = tmp->nextEntite;
        free(tmp); // on libère la mémoire allouée à l'entité qu'on veut supprimer
      }
    }
}

void removeEnnemiFromList(Entite* entite, Ennemi *liste)
{
    if (liste != NULL) // si la liste n'est pas déjà vide
    {
      if (entite == *liste)// si l'entite est à la tête de la liste
      {
        Entite *tmp = *liste; // on garde la tête de la liste dans un tmp
        *liste = (*liste)->nextEntite; // on pointe vers l'élement suivant de la chaine
        free(tmp); // on libère la mémoire du premier élement qui est notre entité
      }
      else // si l'entite est au milieu de la liste
      {
        Entite *tmp = (*liste)->nextEntite; // on garde un tmp pour parcourir la chaine
        Entite *prev = *liste; // on garde un pointeur vers l'élement pécédant le tmp
        while (entite != tmp) // tant qu'on n'a pas trouvé notre entité
        {
          prev = tmp; // on passe à l'entité suivante en gardant le précédant du tmp
          tmp = tmp->nextEntite;
        }
        prev->nextEntite = tmp->nextEntite;
        free(tmp); // on libère la mémoire allouée à l'entité qu'on veut supprimer
      }
    }
}

void removeProjectilesFromList(Entite* entite, Projectiles *liste)
{
      if (liste != NULL) // si la liste n'est pas déjà vide
      {
        if (entite == *liste)// si l'entite est à la tête de la liste
        {
          Entite *tmp = *liste; // on garde la tête de la liste dans un tmp
          *liste = (*liste)->nextEntite; // on pointe vers l'élement suivant de la chaine
          free(tmp); // on libère la mémoire du premier élement qui est notre entité
        }
        else // si l'entite est au milieu de la liste
        {
          Entite *tmp = (*liste)->nextEntite; // on garde un tmp pour parcourir la chaine
          Entite *prev = *liste; // on garde un pointeur vers l'élement pécédant le tmp
          while (entite != tmp) // tant qu'on n'a pas trouvé notre entité
          {
            prev = tmp; // on passe à l'entité suivante en gardant le précédant du tmp
            tmp = tmp->nextEntite;
          }
          prev->nextEntite = tmp->nextEntite;
          free(tmp); // on libère la mémoire allouée à l'entité qu'on veut supprimer
        }
      }
}

void removeLineFromList(Entite* entite, Line *liste)
{
      if (liste != NULL) // si la liste n'est pas déjà vide
      {
        if (entite == *liste)// si l'entite est à la tête de la liste
        {
          Entite *tmp = *liste; // on garde la tête de la liste dans un tmp
          *liste = (*liste)->nextEntite; // on pointe vers l'élement suivant de la chaine
          free(tmp); // on libère la mémoire du premier élement qui est notre entité
        }
        else // si l'entite est au milieu de la liste
        {
          Entite *tmp = (*liste)->nextEntite; // on garde un tmp pour parcourir la chaine
          Entite *prev = *liste; // on garde un pointeur vers l'élement pécédant le tmp
          while (entite != tmp) // tant qu'on n'a pas trouvé notre entité
          {
            prev = tmp; // on passe à l'entité suivante en gardant le précédant du tmp
            tmp = tmp->nextEntite;
          }
          prev->nextEntite = tmp->nextEntite;
          free(tmp); // on libère la mémoire allouée à l'entité qu'on veut supprimer
        }

   
   }
}

void removeBonusFromList(Entite* entite, Bonus *liste)
{
      if (liste != NULL) // si la liste n'est pas déjà vide
      {
        if (entite == *liste)// si l'entite est à la tête de la liste
        {
          Entite *tmp = *liste; // on garde la tête de la liste dans un tmp
          *liste = (*liste)->nextEntite; // on pointe vers l'élement suivant de la chaine
          free(tmp); // on libère la mémoire du premier élement qui est notre entité
        }
        else // si l'entite est au milieu de la liste
        {
          Entite *tmp = (*liste)->nextEntite; // on garde un tmp pour parcourir la chaine
          Entite *prev = *liste; // on garde un pointeur vers l'élement pécédant le tmp
          while (entite != tmp) // tant qu'on n'a pas trouvé notre entité
          {
            prev = tmp; // on passe à l'entité suivante en gardant le précédant du tmp
            tmp = tmp->nextEntite;
          }
          prev->nextEntite = tmp->nextEntite;
          free(tmp); // on libère la mémoire allouée à l'entité qu'on veut supprimer
        }
      }
}


/******************FONCTIONS DE LIBERATION************************/
// on libère la mémoire de nos listes

void freeObstacleList(Obstacle *liste)
{
		while (*liste) // tant que la liste n'est pas vide
    {
			Obstacle next = (*liste)->nextEntite; // on garde l'élement suivant de la chaine dans un tmp
			free(*liste); // on libère le premier élement
			*liste = next; // on passe à l'élement suivant
		}
}

void freeEnnemiList(Ennemi *liste)
{
		while (*liste) // tant que la liste n'est pas vide
    {
			Ennemi next = (*liste)->nextEntite; // on garde l'élement suivant de la chaine dans un tmp
			free(*liste); // on libère le premier élement
			*liste = next; // on passe à l'élement suivant
		}
}

void freeProjectilesList(Projectiles *liste)
{
		while (*liste) // tant que la liste n'est pas vide
    {
			Projectiles next = (*liste)->nextEntite; // on garde l'élement suivant de la chaine dans un tmp
			free(*liste); // on libère le premier élement
			*liste = next; // on passe à l'élement suivant
		}
}

void freeLineList(Line *liste)
{
		while (*liste) // tant que la liste n'est pas vide
    {
			Line next = (*liste)->nextEntite; // on garde l'élement suivant de la chaine dans un tmp
			free(*liste); // on libère le premier élement
			*liste = next; // on passe à l'élement suivant
		}
}


void freeBonusList(Line *liste)
{
    while (*liste) // tant que la liste n'est pas vide
    {
      Line next = (*liste)->nextEntite; // on garde l'élement suivant de la chaine dans un tmp
      free(*liste); // on libère le premier élement
      *liste = next; // on passe à l'élement suivant
    }
}

