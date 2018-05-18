#include "display.h"

/* Fichier de gestion de l'affichage avec OpenGL */
 // TODO : les fonctions de texturing et de chargement du PPM
 // fonction qui dessine un carré

 void drawSquare(int full) {
     GLenum primitive;
     if (full == 1)
     {
       primitive = GL_QUADS;
     }
     else
     {
       primitive = GL_LINE_LOOP;
     }
     glBegin(primitive);
         glVertex2f(-0.1, -0.1);
         glVertex2f(-0.1,  0.1);
         glVertex2f( 0.1,  0.1);
         glVertex2f( 0.1, -0.1);
     glEnd();
 }

 void resizeViewport()
 {
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-1., 1., -1.,1.);
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
           case 0:
               b = 255;
               r = 255;
               g = 255;
               break;
           case 1:
               break;
           case 2:
               r = 255;
               break;
           case 3:
               g = 255;
               break;
           case 4:
               b = 255;
               break;
           case 5:
               r = 255;
               g = 255;
               break;
           default:
               break;
       }
       glColor3ub(r, g, b);
       glPushMatrix();
           glTranslatef(0.5 + entite->x, 0.5 + entite->y, 0);
           if (entite->type == 0)
               glRotatef(entite->vitesseY* 60, 0, 0, 1);
           drawSquare(1);
       glPopMatrix();
       entite = entite->nextEntite;
   }
}
