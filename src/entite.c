#include <entite.h>

/* Fichier de gestion du jeu dans la mémoire */

// fonctions de gestion de l'entité
 Entite* allocEntite(int life, int type, float x, float y , bBox box)
 {
   if (entite == NULL)
   {
     Entite* entite = (Entite*)malloc(sizeof(Entite));
     if (entite == NULL)
     {
       printf("Erreur d'allocation !\n");
     }
     entite->life = life;
     entite->type = type;
     entite->x = x;
     entite->y = y;
     entite->box = NULL;
     return entite;
   }
 }// à debuger et à tester et rajouter x et y dans une autre fonction qui s'en occupe plus tard


 void deleteEntite(Entite entite)
 {
   /* code */

 }

void addObstacleToList(Entite entite, Obstacle liste)
{
  /* code */
}

void addEnnemiToList(Entite entite, Ennemi liste)
{
  /* code */
}

void addMissilesToList(Entite entite, Missiles liste)
{
  /* code */
}

// faire les mêmes fonctions avec RemoveEntiteFromList

// fonction de gestion des collisions
