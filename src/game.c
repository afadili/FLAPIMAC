#include "game.h"


/* fonctions de gestion du game */

// fonction qui initialise les listes du game
void initializeGame(Game *game)
{
  game->player = NULL;
  game->listObsctacle = NULL;
  game->listEnnemi = NULL;
  game->listMissiles = NULL;
}

// fonction qui libère le Game
void freeGame(Game *game)
{
  free((*game).player);
  freeObstacleList(&(*game).listObsctacle);
  freeEnnemiList(&(*game).listEnnemi);
  freeMissilesList(&(*game).listMissiles);
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
int ReadPPM(char * filename, Obstacle* Obstacle, Ennemi* Ennemi, Missiles* Missiles)
{
  printf("Lecture du fichier PPM ! \n");
  FILE *inputFile = NULL;
  inputFile = fopen(filename,"r");
  if (inputFile != NULL)
    {
      int r, g, b;
      int Nbcolors;
      char codePPM;
      int Image_width, Image_height;
      if (fscanf(inputFile,"%c",&codePPM)== EOF) return 0; // Lecture du permier caractère du fichier PPM qui est un code P6 ou P5
      if (fscanf(inputFile,"%c",&codePPM)== EOF) return 0;
      printf("%c\n",codePPM );
      if (fscanf(inputFile,"%d",&Image_height)== EOF) return 0; // récupération du height de l'image du fichier PPM
      printf("HEIGHT : %d\n",Image_height );
      if (fscanf(inputFile,"%d",&Image_width)== EOF) return 0; // récupération du width de l'image du fichier PPM
      printf("WIDTH : %d\n",Image_width );
      if (fscanf(inputFile,"%d",&Nbcolors)== EOF) return 0; // récupération du nombre de couleurs du fichier PPM
      printf("Nombre de couleurs : %d\n",Nbcolors );
      int x=0, y=0;
      for (x=0; x<Image_width; x++)
      {
        for (y=0; y<Image_height; y++)
        {
            if (fscanf(inputFile,"%d", &r) == EOF) return 0;// récupération des couleurs et on les mets dans les variables r, g et b
				    if (fscanf(inputFile,"%d", &g) == EOF) return 0;
				    if (fscanf(inputFile,"%d", &b) == EOF) return 0;
				    if (r != 255 || g!= 255 || b!= 255)
				    {
				    	if (r == 0 && g == 0 && b == 255) /* si c'est bleu crée un joueur */
				    	{

				    	if (r == 255 && g == 0 && b == 0) /* si c'est rouge crée un obstacle */
				    	{
				    	       addObstacleToList(allocEntite(1,3,10,10,0,0), Obstacle);
				    	}
				    	if (r == 0 && g == 255 && b == 0) /* si c'est vert crée un ennemi*/
				    	{
				    	        addEnnemiToList(allocEntite(3,2,10,10,0,0), Ennemi);
				    	}
              if (r == 0 && g == 0 && b == 0) /* si c'est noir crée un missile */
              {
                    addMissilesToList(allocEntite(1,4,20,20,0,0), Missiles);
              }
        }
      }
      fclose(inputFile);
    }
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
