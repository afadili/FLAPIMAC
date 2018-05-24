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
char * textureDir="img/";
GLuint textures[NBTEXTURES];
//SDL_Surface *text = NULL;

 int main ()

 {


   /* Initialisation des entités */
   Game game;
   initializeGame(&game);

   //game.player = allocEntite(3,'H',0,0,0,0); // je crée un player et je le mets dans le Game
   //game.listObstacle = allocEntite(10,'o',9,9,0,0); // je crée un obstacle et je le mets dans le GAME
   //game.listEnnemi = allocEntite(2,'E',5,5,0,0); // ennemi
   //game.listProjectiles = allocEntite(10,'P',5.30,5,0,0);// projectiles
   /* test de chargement de la ppm */

   //addPlayerTolist(allocEntite(3,'H',0,0,0,0),&(game.player));
   //addObstacleToList(allocEntite(1,'O',1,1,0,0),  &(game.listObstacle));

    if (!ReadPPM("map6.ppm", &game)) {
      printf("err en lisant le ppm\n" );
      return EXIT_FAILURE;
    }
   // height 128
   // width 24
   //printf("entite de type : %c\n",game.player->type);
   //printf("entite de type : %c\n",game.listObstacle->type);
   //printf("entite de type : %c\n",game.listEnnemi->type);
   //printf("entite de type : %c\n",game.listProjectiles->type);

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



// musique de fond
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //Initialisation de l'API Mixer
    {
       printf("%s", Mix_GetError()); // si problème d'ouverture de son, on affiche les erreurs
    }
  Mix_AllocateChannels(10);
  Mix_Chunk *sound1;
  Mix_Chunk *sound2;
  Mix_Chunk *sound3;
  Mix_Chunk *sound4;
  sound1 = Mix_LoadWAV("./sound/shoot.wav");
  sound2 = Mix_LoadWAV("./sound/explosion.wav");
  sound3 = Mix_LoadWAV("./sound/deadenemy.wav");
  sound4 = Mix_LoadWAV("./sound/bonus.wav");
  Mix_VolumeChunk(sound1, MIX_MAX_VOLUME/2);  
  Mix_VolumeChunk(sound2, MIX_MAX_VOLUME*10);
  Mix_Music *music;
  music = Mix_LoadMUS("./sound/spongebobtheme.mp3");
  Mix_PlayMusic(music, -1); // -1 pour jouer en boucle





	resizeViewport();

	glClearColor(1., 1., 1., 1);
  /* Initialisation des entités du jeu */

  /* code */

  /* Récupération du temps au début de la boucle */
  Uint32 startTime = SDL_GetTicks();
  /* Boucle d'affichage */
  	int loop = 1;
    float i = 0;
    //int playerMove =0;
    int mode =0;
    GLuint textureID=0;

    const char* filename = "background.png";


    /* chargement de l'image d'après le fichier */
    SDL_Surface* image = IMG_Load(filename);
    if (image == NULL)
    {
      printf("Erreur de chargement de l'image\n");
      return 0;
    }

    loadTexture(textureDir,textures);
    printf("Pictures loaded success ! \n");


   /* if(TTF_Init() == -1)
{
    fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
    exit(EXIT_FAILURE);
}
TTF_Font *police = NULL;
police = TTF_OpenFont("./ttf/KrabbyPatty.ttf", 65);
SDL_Color colorBlack = {0, 0, 0};
text = TTF_RenderText_Blended(police, "BONUS", colorBlack);*/


  while(loop) {
    //game.player->x=i;
    glClear(GL_COLOR_BUFFER_BIT); // Toujours commencer par clear le buffer
    if (mode==0)
    {
      //printf("MENU PRINCIPAL\n");
      texturedMenu();

    //loadPictures(textureID, image);
    }
    else
    {

            //printf("DEBUT JEU \n");

      moveProjectile((game.listProjectiles));
        //printf("DEBUT JEU \n");
        /////////////////////////////////////////////////////////////////////////
       game.player->x=i;

         // moveRight(&game.player);


        /* Code de dessin */

        glDisable(GL_TEXTURE_2D);

          glPushMatrix();
          glScalef(20/(float)img_height, 20/(float)img_height,0);
          glTranslatef(-i,-img_height/2+0.5,0);
          //glTranslatef(2 - game.player->x, 0, 0); // Translation du monde pour suivre le joueur
          

          glColor3ub(255,255,255);
          drawEntite(game.listObstacle); // rouge
          drawEntite(game.listEnnemi); // vert
          drawEntite(game.listProjectiles); //noir
          drawEntite(game.player); // bleu
          drawEntite(game.listLine); // jaune
          drawEntite(game.listBonus); // magenta

          //glClear(GL_COLOR_BUFFER_BIT);
          //glPushMatrix();
      		//drawSquare(1,0,0); // Dessin d'un carré pour tester
        glPopMatrix();
        //////////////////////////////////////////////////////////////////////////
    }


    /* Déplacement du joueur
		if (playerMove == 1)
			moveUp(&game.player);
		else if (playerMove == -1)
			moveDown(&game.player);

    /* Boucle traitant les evenements */
    i+=0.03;
/* Gestion des collisions */

		

		if (checkCollision(game.player, &(game.listEnnemi)) || checkCollision(game.player, &(game.listObstacle))) { 
			printf("GAME OVER\n");
			break;
		}
		if (checkCollision(game.listProjectiles, &(game.listEnnemi))) { 
      Mix_PlayChannel(3, sound3, 0);
			printf("enemy dead\n");
		}

    if(game.player->bonus != 0)
    {
      if (checkCollision(game.listProjectiles, &(game.listObstacle))) { 
        Mix_PlayChannel(2, sound2, 0);
        game.player->bonus-=1;
        printf("nb bonus: %d\n", game.player->bonus);
      }   
    }
		if (checkCollision(game.listObstacle, &(game.listProjectiles))) { 
      Mix_PlayChannel(2, sound2, 0);
			printf("projectile crashed\n");
		}


    if (checkCollision(game.player, &(game.listBonus))) { 
      // effet du bonusgame.player
      Mix_PlayChannel(4, sound4, 0);
      game.player->bonus += 1;
      printf("bonus added!\n");
      printf("nb bonus: %d\n", game.player->bonus);
    }

		if (checkCollision(game.player, &(game.listLine))) { 

			printf("YOU WON\n");
			break;
		}

    if(checkCollision(game.listObstacle, &(game.listEnnemi))!=1){
     moveEnnemi(&(game.listEnnemi), &(game.listProjectiles));
    }


			//moveEnnemiUp(&(game.listEnnemi));

		


  /*  if (checkCollision(game.player, game.listEnnemi)==1) { 
>>>>>>> laurine
			printf("Niveau terminé !\n");
			loop=0;
			break;
		}*/

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
            moveUp(&game.player);
           // playerMove = 1;
            printf("posY : %f\n",  game.player->y );
            break;
          case SDLK_DOWN:
            /* le player bouge en bas*/
            moveDown(&game.player);
            //playerMove = -1;
            printf("posY : %f\n",  game.player->y );
            break;

            // déplacement du joueur non automatisé
            /*case SDLK_LEFT:
            /* le player bouge en bas
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
          printf("Déclenchement des tirs !!! \n");
           Mix_PlayChannel(1, sound1, 0);
          addProjectilesToList(allocEntite(1,0,'P',game.player->x,game.player->y,0,0),&(game.listProjectiles));
          //game.listProjectiles->x++;
            // Déclenchement du tir
            break;

            //game.listProjectiles->x+=10;
          case SDLK_ESCAPE:
          mode = 1;
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
      //game.listProjectiles->x++;
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
  Mix_FreeMusic(music); //Libération de la musique
  Mix_FreeChunk(sound1);
  Mix_FreeChunk(sound2);
  Mix_FreeChunk(sound3);
  Mix_CloseAudio();
  /*TTF_CloseFont(police); 
  TTF_Quit();*/
  SDL_Quit();

   return EXIT_SUCCESS;
 }
