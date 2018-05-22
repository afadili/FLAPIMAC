#include "display.h"

/* Fichier de gestion de l'affichage avec OpenGL */
 // les fonctions de texturing

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
               break;
        	case 'E': //ennemi
               r = 0;
               g = 255;
               b = 0;
               break;
        	case 'O': // obstacle
               r = 255;
               g = 0;
               b = 0;
               break;
        	case 'P': //projectile
               r = 0;
               g = 0;
               b = 0;
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
       //glPopMatrix();
       entite = entite->nextEntite;
   }
}

/* glPushMatrix();
 printf("entite %f \n",entite->y);
     glTranslatef(1 + entite->x, 1 + entite->y, 0);
    /*z if (entite->type == 0)
     {
         glRotatef(entite->vitesseY* 60, 0, 0, 1);
         printf("drawsquare !!!!!!! \n");
    }*/
