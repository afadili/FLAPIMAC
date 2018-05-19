#include "game.h"

extern int img_height, img_width;


/* fonctions de gestion du game */

void drawGame(Game game)
{
  drawEntite(game.player); // bleu
  drawEntite(game.listObstacle); // rouge
  drawEntite(game.listEnnemi); // vert
  drawEntite(game.listProjectiles); //noir
}
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

}

// fonction qui supprime une entité du game
void removeEntiteFromGame(Game *game, Entite *entite)
{
  /* code */
}

// fonction de chargement du level avec la PPM

int ReadPPM(char * filename, Game *game)
{
  printf("Lecture du fichier PPM ! \n");
  FILE *inputFile = NULL;
  inputFile = fopen(filename,"r");
  if (inputFile != NULL)
    {
      int r, g, b;
      int Nbcolors;
      char codePPM;
      if (fscanf(inputFile,"%c",&codePPM)== EOF) return 0; // Lecture du permier caractère du fichier PPM qui est un code P6 ou P5
      if (fscanf(inputFile,"%c",&codePPM)== EOF) return 0;
      printf("%c\n",codePPM );
      if (fscanf(inputFile,"%d",&img_width)== EOF) return 0; // récupération du height de l'image du fichier PPM
      printf("WIDTH : %d\n",img_width );
      if (fscanf(inputFile,"%d",&img_height)== EOF) return 0; // récupération du width de l'image du fichier PPM
      printf("HEIGHT : %d\n",img_height );
      if (fscanf(inputFile,"%d",&Nbcolors)== EOF) return 0; // récupération du nombre de couleurs du fichier PPM
      printf("Nombre de couleurs : %d\n",Nbcolors );
      int x=0, y=0;
      for (y=0; y<img_height; y++)
      {
      for (x=0; x<img_width; x++)
      {
            if (fscanf(inputFile,"%d", &r) == EOF) return 0;// récupération des couleurs et on les mets dans les variables r, g et b
				    if (fscanf(inputFile,"%d", &g) == EOF) return 0;
				    if (fscanf(inputFile,"%d", &b) == EOF) return 0;
            printf("reading r g b done ! \n");
				    if (r != 255 || g!= 255 || b!= 255)
				    {
              printf("entre dans le premier if du blanc !!!!!\n");
				    	if (r == 0 && g == 0 && b == 255) /* si c'est bleu on crée un joueur */
				    	{
                printf("adding player from ppm !!!!!! \n");
                    addPlayerTolist(allocEntite(3,'H',x,y,0,0),&(game->player));;
              }

				    	if (r == 255 && g == 0 && b == 0) /* si c'est rouge on crée un obstacle */
				    	{
                      printf("adding obstacle from ppm !!!!!! \n");
                      printf("x : %d, y : %d\n", x, y);
				    	       addObstacleToList(allocEntite(1,'O',x,y,0,0),  &(game->listObstacle));
                      printf("adding obstacle done ........\n" );
				    	}
				    	if (r == 0 && g == 255 && b == 0) /* si c'est vert on crée un ennemi*/
				    	{
                        printf("adding ennemi from ppm !!!!!! \n");
				    	        addEnnemiToList(allocEntite(3,'E',x,y,0,0), &(game->listEnnemi));

				    	}
              if (r == 0 && g == 0 && b == 0) /* si c'est noir on crée un projectile */
              {
                      printf("adding projectile from ppm !!!!!! \n");
                    addProjectilesToList(allocEntite(1,'P',x,y,0,0), &(game->listProjectiles));

              }
        }
      }
    }
    fclose(inputFile);
    return 1;
	}

  else
    {
      printf("Impossible de lire le fichier ! \n");
      return 0;
    }
  printf("tout est OK ! \n");
  return 1;
}
