#include "game.h"


/* fonctions de gestion du game */

// fonction qui initialise les listes du game
void initializeGame(Game *game)
{
  game->player = NULL;
  game->listObstacle = NULL;
  game->listEnnemi = NULL;
  game->listProjectiles = NULL;
}

// fonction qui libère le Game
void freeGame(Game *game)
{
  free((*game).player);
  freeObstacleList(&(*game).listObstacle);
  freeEnnemiList(&(*game).listEnnemi);
  freeProjectilesList(&(*game).listProjectiles);
}

// fonction qui ajoute une entité au Game
void addEntiteToGame(Game *game, Entite entite)
{
  /* code */
}

// fonction qui supprime une entité du game
void removeEntiteFromGame(Game *game, Entite *entite)
{
  /* code */
}

// fonction de chargement du level avec la PPM
<<<<<<< HEAD
int ReadPPM(char * filename,Game *game)
=======
int ReadPPM(char * filename, Obstacle* Obstacle, Ennemi* Ennemi, Projectiles* Projectile)
>>>>>>> 150836d5f05326c4cc48986fb55b10bad0d39a59
{
  printf("Lecture du fichier PPM ! \n");
  FILE *inputFile = NULL;
  inputFile = fopen(filename,"r");
  if (inputFile != NULL)
    {
      int r, g, b;
      int Nbcolors;
      char codePPM;
      int img_width, img_height;
      if (fscanf(inputFile,"%c",&codePPM)== EOF) return 0; // Lecture du permier caractère du fichier PPM qui est un code P6 ou P5
      if (fscanf(inputFile,"%c",&codePPM)== EOF) return 0;
      printf("%c\n",codePPM );
      if (fscanf(inputFile,"%d",&img_height)== EOF) return 0; // récupération du height de l'image du fichier PPM
      printf("HEIGHT : %d\n",img_height );
      if (fscanf(inputFile,"%d",&img_width)== EOF) return 0; // récupération du width de l'image du fichier PPM
      printf("WIDTH : %d\n",img_width );
      if (fscanf(inputFile,"%d",&Nbcolors)== EOF) return 0; // récupération du nombre de couleurs du fichier PPM
      printf("Nombre de couleurs : %d\n",Nbcolors );
      int x=0, y=0;
      for (x=0; x<img_width; x++)
      {
        for (y=0; y<img_height; y++)
        {
            if (fscanf(inputFile,"%d", &r) == EOF) return 0;// récupération des couleurs et on les mets dans les variables r, g et b
				    if (fscanf(inputFile,"%d", &g) == EOF) return 0;
				    if (fscanf(inputFile,"%d", &b) == EOF) return 0;
				    if (r != 255 || g!= 255 || b!= 255)
				    {
				    	if (r == 0 && g == 0 && b == 255) /* si c'est bleu on crée un joueur */
				    	{
                allocEntite(3,'H',0,400,0,0);
              }

				    	if (r == 255 && g == 0 && b == 0) /* si c'est rouge on crée un obstacle */
				    	{
<<<<<<< HEAD
				    	       addObstacleToList(allocEntite(1,3,10,10,0,0), game->listObsctacle);
=======
				    	       addObstacleToList(allocEntite(1,'O',10,10,0,0), Obstacle);
>>>>>>> 150836d5f05326c4cc48986fb55b10bad0d39a59
				    	}
				    	if (r == 0 && g == 255 && b == 0) /* si c'est vert on crée un ennemi*/
				    	{
<<<<<<< HEAD
				    	        addEnnemiToList(allocEntite(3,2,10,10,0,0), game->listEnnemi);
=======
				    	        addEnnemiToList(allocEntite(3,'E',10,10,0,0), Ennemi);
>>>>>>> 150836d5f05326c4cc48986fb55b10bad0d39a59
				    	}
              if (r == 0 && g == 0 && b == 0) /* si c'est noir on crée un projectile */
              {
<<<<<<< HEAD
                    addMissilesToList(allocEntite(1,4,20,20,0,0), game->listMissiles);
=======
                    addProjectilesToList(allocEntite(1,'P',20,20,0,0), Projectile);
>>>>>>> 150836d5f05326c4cc48986fb55b10bad0d39a59
              }
        }
      }
      fclose(inputFile);
    }
	}

  else
    {
      printf("Impossible de lire le fichier ! \n");
      return 0;
    }
  printf("tout est OK ! \n");
  return 1;
}
