#include <SDL/SDL.h>
#include "main.h"
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "entite.h"
#include "display.h"
#include "game.h"
#include "player.h"
#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <assert.h>
#include <dirent.h>

int img_width, img_height;
int mode =0;
float score = 0;
char * textureDir="img/";
GLuint textures[NBTEXTURES];
Mix_Chunk *sound1;
Mix_Chunk *sound2;
Mix_Chunk *sound3;
Mix_Chunk *sound4;
Mix_Chunk *sound5;
Mix_Music *music;

 int main ()

 {


   /* Initialisation des entités */
   Game game;
   initializeGame(&game);

    if (!ReadPPM("ppm/map6.ppm", &game)) {
      printf("err en lisant le ppm\n" );
      return EXIT_FAILURE;
    }

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
	SDL_WM_SetCaption("Bobimac", NULL);



// musique de fond
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
       printf("%s", Mix_GetError()); // si problème d'ouverture de son, on affiche les erreurs
    }
  Mix_AllocateChannels(10);
  sound1 = Mix_LoadWAV("./sound/shoot.wav");
  sound2 = Mix_LoadWAV("./sound/explosion.wav");
  sound3 = Mix_LoadWAV("./sound/deadenemy.wav");
  sound4 = Mix_LoadWAV("./sound/bonus.wav");
  sound5 = Mix_LoadWAV("./sound/gameover.wav");
  Mix_VolumeChunk(sound1, MIX_MAX_VOLUME/2);
  Mix_VolumeChunk(sound2, MIX_MAX_VOLUME*10);
  music = Mix_LoadMUS("./sound/spongebobtheme.mp3");
  Mix_PlayMusic(music, -1); // -1 pour jouer en boucle


	resizeViewport();

	glClearColor(1., 1., 1., 1);

  /* Récupération du temps au début de la boucle */
  Uint32 startTime = SDL_GetTicks();

  /* Boucle d'affichage */
  	int loop = 1;
    float i = 0;
    int mode =0;


    loadTexture(textureDir,textures);

  while(loop)
  {
    glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer

    if (mode == 0)
      {
        texturedMenu();
      }
    else if (mode == 2)
    {
      drawYouWin();
    }
    else if (mode == -1)
    {
      drawYouLose();
    }
      else
      {
        drawBG();
        moveProjectile((game.listProjectiles));
        game.player->x=i;

          /* Code de dessin */

          glDisable(GL_TEXTURE_2D);

          glPushMatrix();
              glScalef(20/(float)img_height, 20/(float)img_height,0);
              glTranslatef(-i,-img_height/2+0.5,0);
              glColor3ub(255,255,255);
              drawEntite(game.listObstacle); // rouge
              drawEntite(game.listEnnemi); // vert
              drawEntite(game.listProjectiles); //noir
              drawEntite(game.player); // bleu
              drawEntite(game.listLine); // jaune
              drawEntite(game.listBonus); // magenta
          glPopMatrix();

          i+=0.03;
      }

		if (checkCollision(game.player, &(game.listEnnemi)) || checkCollision(game.player, &(game.listObstacle))) {
        mode = -1;
		}
		if (checkCollision(game.listProjectiles, &(game.listEnnemi))) {
      Mix_PlayChannel(3, sound3, 0);
      score+=20;
      printf("score : %.2f\n", score);
		}


    if(game.player->bonus != 0)
    {
      if (checkCollision(game.listProjectiles, &(game.listObstacle))) {
        Mix_PlayChannel(2, sound2, 0);
        game.player->bonus-=1;
        printf("nb bonus: %d\n", game.player->bonus);
        score+=10;
        printf("score : %.2f\n", score);

      }
    }
		if (checkCollision(game.listObstacle, &(game.listProjectiles))) {
      Mix_PlayChannel(2, sound2, 0);
		}

    if (checkCollision(game.player, &(game.listBonus))) {
      Mix_PlayChannel(4, sound4, 0);
      game.player->bonus += 3;
      printf("bonus added!\n");
      score+=5;
      printf("nb bonus: %d\n", game.player->bonus);
    }

		if (checkCollision(game.player, &(game.listLine)))
    {
      printf("score : %.2f\n", score);
      mode = 2;
		}

   if(checkCollision(game.listObstacle, &(game.listEnnemi))!=1){
     moveEnnemi(&(game.listEnnemi), &(game.listProjectiles));
    }

  SDL_Event e;
  while(SDL_PollEvent(&e))
  {
    /* L'utilisateur ferme la fenêtre */
    if(e.type == SDL_QUIT)
    {
      loop = 0;
      break;
    }
    /* Traitement d'evenements :*/
    switch(e.type)
    {
       /*Touche clavier*/
      case SDL_KEYDOWN:
        switch(e.key.keysym.sym)
        {
          case SDLK_q:
            loop = 0;
            break;

          case SDLK_UP:
            /* le player bouge en haut*/
            moveUp(&game.player);
            break;

          case SDLK_DOWN:
            /* le player bouge en bas*/
            moveDown(&game.player);
            break;

            // déplacement du joueur non automatisé
            /*case SDLK_LEFT:
             le player bouge en bas
            moveLeft(&game.player);
            //playerMove = -1;
            printf("posX : %f\n",  game.player->x );
            break;

            case SDLK_RIGHT:
            moveRight(&game.player);
            //playerMove = -1;
            printf("posX : %f\n",  game.player->x );
            break;*/

          case SDLK_SPACE:
            score-=0.5;
            Mix_PlayChannel(1, sound1, 0);
            addProjectilesToList(allocEntite(1,0,'P',game.player->x,game.player->y,0,0),&(game.listProjectiles));
            // Déclenchement du tir
              break;

          case SDLK_ESCAPE:
          if(mode== -1){
            mode = -1;
          }
          else {
            if(mode== 2){
            mode = 2;
          }
          else
              mode = 1;
          }
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
  if(elapsedTime < FRAMERATE_MILLISECONDS)
  {
    SDL_Delay(FRAMERATE_MILLISECONDS - elapsedTime);
  }
}
  /* Liberation des ressources associées à la SDL */
  Mix_FreeMusic(music); //Libération de la musique
  Mix_FreeChunk(sound1);
  Mix_FreeChunk(sound2);
  Mix_FreeChunk(sound3);
  Mix_CloseAudio();

  SDL_Quit();

   return EXIT_SUCCESS;
 }
