#include <entite.h>

/* Fichier de gestion du jeu dans la mémoire */

// fonctions de gestion de l'entité
// Fonction qui alloue la mémoire nécessaire d'une entité,
// on initialise les champs avec les valeurs x,y,type,life,bBox passées en paramètre


 Entite* allocEntite(int life, char type, float x, float y, float vitesseY, float vitesseX/*, bBox box*/)
 {
   Entite* entite;
   entite = malloc(sizeof(Entite));
     if (entite == NULL)
     {
       printf("Allocation error !\n");
     }
     entite->life = life;
     entite->type = type;
     entite->x = x;
     entite->y = y;
     //entite->box = NULL;
     entite->vitesseX = vitesseX;
     entite->vitesseY = vitesseY;
     entite->nextEntite=NULL;
     return entite;
   }
 // à debuger et à tester et rajouter x et y dans une autre fonction qui s'en occupe plus tard

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

// faire les mêmes fonctions avec RemoveEntiteFromList

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
// fonction de gestion des collisions
