#include "entite.h"
#include "display.h"
#include "game.h"
#include "player.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <assert.h>

int img_width, img_height;

 int main ()
 {
   /* Initialisation des entités */
   Game game;
   initializeGame(&game);

   //game.player = allocEntite(3,'H',0,0,0,0); // je crée un player et je le mets dans le Game
   //game.listObstacle = allocEntite(10,'o',9,9,0,0); // je crée un obstacle et je le mets dans le GAME
   game.listEnnemi = allocEntite(2,'E',5,5,0,0); // ennemi
   game.listProjectiles = allocEntite(10,'P',5.30,5,0,0);// projectiles
   /* test de chargement de la ppm */

   //addPlayerTolist(allocEntite(3,'H',0,0,0,0),&(game.player));
   addObstacleToList(allocEntite(1,'O',1,1,0,0),  &(game.listObstacle));
    if (!ReadPPM("map.ppm", &game)) {
      printf("err en lisant le ppm\n" );
      return EXIT_FAILURE;
    };
   // height 128
   // width 24
   //printf("entite de type : %c\n",game.player->type);
   //printf("entite de type : %c\n",game.listObstacle->type);
   printf("entite de type : %c\n",game.listEnnemi->type);
   printf("entite de type : %c\n",game.listProjectiles->type);

   /* Initialisation de la SDL */
	if (-1 == SDL_Init(SDL_INIT_VIDEO))
    {
  		fprintf(stderr, "Impossible d'initialiser la SDL. Fin du programme.\n");
  		return EXIT_FAILURE;
  	}

	/* Ouverture d'une fenêtre et création d'un contexte OpenGL */

	if (NULL == SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE))
    {
  		fprintf(stderr, "Impossible d'ouvrir la fenetre. Fin du programme.\n");
  		return EXIT_FAILURE;
  	}
	SDL_WM_SetCaption("Flapimac", NULL);
	resizeViewport();

	glClearColor(1., 1., 1., 1);
  /* Initialisation des entités du jeu */

  /* code */

  /* Récupération du temps au début de la boucle */
  Uint32 startTime = SDL_GetTicks();
  /* Boucle d'affichage */
  	int loop = 1;
    float i = 0;
	while(loop) {

    game.player->x=i;

		glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer
    /* Code de dessin */


    glPushMatrix();
      glScalef(20/(float)img_height, 20/(float)img_height,0);
      glTranslatef(-i,-img_height/2,0);
      //glTranslatef(2 - game.player->x, 0, 0); // Translation du monde pour suivre le joueur

      drawEntite(game.listObstacle); // rouge
      drawEntite(game.listEnnemi); // vert
      drawEntite(game.listProjectiles); //noir
      drawEntite(game.player); // bleu

      //glClear(GL_COLOR_BUFFER_BIT);
      //glPushMatrix();
  		//drawSquare(1,0,0); // Dessin d'un carré pour tester
    glPopMatrix();

		/* Déplacement du joueur */
    /* Boucle traitant les evenements */
    i+=0.05;

  SDL_Event e;
  while(SDL_PollEvent(&e)) {

    /* L'utilisateur ferme la fenêtre */
    if(e.type == SDL_QUIT) {
      loop = 0;
      break;
    }
    /* Traitement d'evenements :*/
    switch(e.type) {

       /*Touche clavier*/
      case SDL_KEYDOWN:
        // printf("touche pressée (code = %d)\n", e.key.keysym.sym);
        switch(e.key.keysym.sym)
        {

          case SDLK_q:
            loop = 0;
            break;

          case SDLK_UP:
            /* le player bouge en haut*/
           // game.player->y+=0.1;
          	moveUp(&game.player);
            printf("posY : %f\n",  game.player->y );
            break;
          case SDLK_DOWN:
            /* le player bouge en bas*/
          moveDown(&game.player);
           // game.player->y-=0.1;
            printf("posY : %f\n",  game.player->y );
            break;

          //case SDLK_SPACE:
            // Déclenchement du tir
          //  break;

          default:
            break;
        }

      case SDL_VIDEORESIZE:
        e.resize.w = WINDOW_WIDTH;
        e.resize.h = WINDOW_HEIGHT;
        resizeViewport();

      default:
        break;
    }
  }
    /* Echange du front et du back buffer : mise à jour de la fenêtre */
  SDL_GL_SwapBuffers();

  /* Calcul du temps écoulé */
  Uint32 elapsedTime = SDL_GetTicks() - startTime;

  /* Si trop peu de temps s'est écoulé, on met en pause le programme */
  if(elapsedTime < FRAMERATE_MILLISECONDS) {
    SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
  }
}

  /* Liberation des ressources associées à la SDL */
  SDL_Quit();

   return EXIT_SUCCESS;
 }
