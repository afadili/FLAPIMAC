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
         glVertex2f(-0.5, -0.5);
         glVertex2f(-0.5,  0.5);
         glVertex2f( 0.5,  0.5);
         glVertex2f( 0.5, -0.5);
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
