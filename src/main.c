#include "entite.h"
#include "display.h"
#include "game.h"
#include "player.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <assert.h>





 int main ()
 {
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

	glClearColor(0.5, 0.5, 0.5, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
  /* Initialisation des entités du jeu */

  /* code */

  /* Boucle d'affichage */
  	int loop = 1;
	while(loop) {

		/* Récupération du temps au début de la boucle */
		Uint32 startTime = SDL_GetTicks();

		/* Code de dessin */

		glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer

		drawSquare(1); // Dessin d'un carré pour tester

		/* Déplacement du joueur */
    /* Boucle traitant les evenements */
  SDL_Event e;
  while(SDL_PollEvent(&e)) {

    /* L'utilisateur ferme la fenêtre : */
    if(e.type == SDL_QUIT) {
      loop = 0;
      break;
    }

    /* Traitement d'evenements : */
    switch(e.type) {

      /* Touche clavier */
      case SDL_KEYDOWN:
        // printf("touche pressée (code = %d)\n", e.key.keysym.sym);
        switch(e.key.keysym.sym)
        {

          case SDLK_q:
            loop = 0;
            break;

          case SDLK_UP:
            /* le player bouge en haut  */
            break;

          case SDLK_DOWN:
            /* le player bouge en bas  */
            break;

          case SDLK_SPACE:
            // Déclenchement du tir
            break;

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
