#include "display.h"
#include <dirent.h>
/* Fichier de gestion de l'affichage avec OpenGL */
 // les fonctions de texturing


// fonction qui retourne l'id de l 'image à partie de son nom de fichier
// les fichiers sont nommés avec ID_nomdufichier cette fonction prend l'id et le retourne
int getImgId(char* filename)
{
  {
    if ('0' <= filename[0] && filename[0] <= '9' && '0' <= filename[1] && filename[1] <= '9' ) // si les deux premiers élements sont des nombres
    return 10 * (filename[0] - '0') + filename[1] - '0';
  }
  // sinon retourne -1
  return -1;
}
 // fonction qui vérifie qu'une SDL_Surface est bien chargée
 int loaded(SDL_Surface* image)
 {
   // retourne 1 si la surface SDL est bien chargée
   if (image == NULL)
   {
     printf("Erreur de chargement de la texture \n");
     SDL_Quit();
     return 0;
   }
   return 1;
 }

int loadTexture(char* directory, GLuint textureID[])
// Chargement des textures depuis un dossier et classement dans un dossier

{
  DIR *d;
  struct dirent *dir;
  d = opendir(directory);
  if (!d)
  {
    printf("Impossible d'ouvrir le dossier des textures ! \n");
    return 0;
  }

  // Chargement de la texture
  SDL_Surface* textures[NBTEXTURES];
  glGenTextures(NBTEXTURES, textureID);

  int i=0;

  // parcours du dossier des textures
  while ((dir = readdir(d)) != NULL)
  {
    printf("parcours du dossier \n");
    // on trie juste les fichiers de textures et pas les fichiers d'avant (avec . et ..)
    if (strcmp(dir->d_name,"..") != 0 && strcmp(dir->d_name,".") != 0)
    {
      i = getImgId(dir->d_name);
      // tmp : chemin de l'image chargée
      char tmp[50];
      strcpy(tmp, directory);
      strcat(tmp, dir->d_name);
      printf("Chargement de la texture : %s\n",tmp );

      textures[i] = IMG_Load(tmp);
      if (!loaded(textures[i])) return 0;
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glBindTexture(GL_TEXTURE_2D, textureID[i]);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

            // Envoie des données texture à la carte graphique
            glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RGBA,
                textures[i]->w,
                textures[i]->h,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                textures[i]->pixels);

            // Libération des données CPU
            SDL_FreeSurface(textures[i]);
            glBindTexture(GL_TEXTURE_2D, 0);
      }
    }
  closedir(d);
return 1;
}


 void loadPictures(GLuint textureID, SDL_Surface* image)
 {
   // TODO: Chargement et traitement de la texture
   // charger toutes les images
   glGenTextures(1,&textureID);
   glBindTexture(GL_TEXTURE_2D,textureID);
   glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   // Envoi des données à la carte graphique
   glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->w,image->h,0,GL_RGBA,GL_UNSIGNED_BYTE,image->pixels);
   // Détachement de la texture de son point de bind
   glBindTexture(GL_TEXTURE_2D,0);



       SDL_FreeSurface(image);

           glClear(GL_COLOR_BUFFER_BIT);


                   glEnable(GL_TEXTURE_2D);
                   glBindTexture(GL_TEXTURE_2D,textureID);
 }

 void texturedMenu(GLuint textureID, SDL_Surface* image)
 {
   // Code de dessin
   glPushMatrix();
   glScalef(10,10,1);
   glBegin(GL_QUADS);
       glTexCoord2f(0,0);
       glVertex2f(-1,1);
       glTexCoord2f(1,0);
       glVertex2f(1,1);
       glTexCoord2f(1,1);
       glVertex2f(1,-1);
       glTexCoord2f(0,1);
       glVertex2f(-1,-1);
   glEnd();
   glPopMatrix();
   // Fin du code de dessin


   //glDisable(GL_TEXTURE_2D);
   //glBindTexture(GL_TEXTURE_2D,0);
   glDeleteTextures(1,&textureID);

 }


 // fonction qui dessine un carré

 void drawSquare(int full, float x, float y) {
     GLenum primitive;
     if (full == 1)
     {
       primitive = GL_QUADS;
     }
     else
     {
       primitive = GL_LINE_LOOP;
     }
      glPushMatrix();
        glTranslatef(x,y, 0);
            glBegin(primitive);
                glVertex2f(-0.5, -0.5);
                glVertex2f(-0.5,  0.5);
                glVertex2f( 0.5,  0.5);
                glVertex2f( 0.5, -0.5);
            glEnd();
    glPopMatrix();
 }

 void resizeViewport()
 {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-10., 10., -10.,10.);
	SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, BIT_PER_PIXEL, SDL_OPENGL | SDL_RESIZABLE);
}

void drawEntite(listEntite entite)
{
   int r, g, b;
   r = 0;
   g = 0;
   b = 0;
   while (entite != NULL)
    {
       switch (entite->type){
           case 'H': // hero
               r = 0;
               g = 0;
               b = 255;
               //printf("dessin de la texture dans le game !!!!!!!!!!!!!!!!\n");
               //drawTexturedSquare(01);
               break;
        	case 'E': //ennemi
               r = 0;
               g = 255;
               b = 0;
               //printf("dessin de la texture ENNEMI dans le game !!!!!!!!!!!!!!!!\n");
               //drawTexturedSquare(01);
               break;
        	case 'O': // obstacle
               r = 255;
               g = 0;
               b = 0;
               //printf("dessin de la texture OBSTACLE dans le game !!!!!!!!!!!!!!!!\n");
               //drawTexturedSquare(01);
               break;
        	case 'P': //projectile
               r = 0;
               g = 0;
               b = 0;
               //printf("dessin de la texture PROJECTILE dans le game !!!!!!!!!!!!!!!!\n");
               //drawTexturedSquare(01);
               break;
        	case 'L': //ligne de fin
               r = 255;
               g = 255;
               b = 0;
               break;
           default:
               break;
       }
      //printf("%d,%d,%d\n",r,g,b );
       glColor3ub(r, g, b);
       drawSquare(1,entite->x,entite->y);
       //drawTexturedSquare(01);
       //glPopMatrix();
       entite = entite->nextEntite;
   }
}

void drawTexturedSquare(GLuint textureID)
{
    //draws a textured square of size 1x1
    glEnable(GL_TEXTURE_2D);
     glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, textureID);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 1);
            glVertex2f(-0.5,-0.5);
            glTexCoord2f(0, 0);
            glVertex2f(-0.5,0.5);
            glTexCoord2f(1, 0);
            glVertex2f(0.5,0.5);
            glTexCoord2f(1, 1);
            glVertex2f(0.5,-0.5);
        glEnd();
    glDisable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, 0);
}


/* glPushMatrix();
 printf("entite %f \n",entite->y);
     glTranslatef(1 + entite->x, 1 + entite->y, 0);
     if (entite->type == 0)
     {
         glRotatef(entite->vitesseY* 60, 0, 0, 1);
         printf("drawsquare !!!!!!! \n");
    }*/
