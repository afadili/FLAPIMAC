#include "display.h"

/* Fichier de gestion de l'affichage avec OpenGL */
 // TODO : les fonctions de texturing et de chargement du PPM
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
   int r=0, g=0, b=0;

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
           default:
               break;
       }
      //printf("%d,%d,%d\n",r,g,b );
       glColor3ub(r, g, b);
      /* glPushMatrix();
       printf("entite %f \n",entite->y);
           glTranslatef(1 + entite->x, 1 + entite->y, 0);
           if (entite->type == 0)
           {
               glRotatef(entite->vitesseY* 60, 0, 0, 1);
               printf("drawsquare !!!!!!! \n");
          }*/
           drawSquare(1,entite->x,entite->y);
       //glPopMatrix();
       entite = entite->nextEntite;
   }
}
