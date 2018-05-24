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
    // on trie juste les fichiers de textures et pas les fichiers d'avant (avec . et ..)
    if (strcmp(dir->d_name,"..") != 0 && strcmp(dir->d_name,".") != 0)
    {
      i = getImgId(dir->d_name);
      // tmp : chemin de l'image chargée
      char tmp[50];
      strcpy(tmp, directory);
      strcat(tmp, dir->d_name);

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

// Fonction qui dessine le menu du jeu
 void texturedMenu()
 {
   // Code de dessin
   glPushMatrix();
   glScalef(20,20,1);
    drawTexturedSquare(1);
   glPopMatrix();
   // Fin du code de dessin
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

// Fonction qui dessine une liste d'entités
void drawEntite(listEntite entite)
{
   while (entite != NULL)
    {
       switch (entite->type){
           case 'H': // hero
               drawPlayer(entite);
               break;
        	case 'E': //ennemi
               drawEnnemi(entite);
               break;
        	case 'O': // obstacle
               drawObstacle(entite);
               break;
        	case 'P': //projectile
               drawProj(entite);
          case 'M': //projectile ennemi
               drawProj(entite);
               break;
        	case 'L': //ligne de fin
               drawLine(entite);
               break;
          case 'B': //bonus
               drawBonus(entite);
               break;
           default:
               break;
       }
       entite = entite->nextEntite;
   }
}

// Fonction qui dessine une texture sur un carré 1x1
void drawTexturedSquare(GLuint textureID)
{
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

// Les fonctions qui dessine chaque entité en texture
void drawPlayer(Hero player)
{
    glPushMatrix();
    glTranslatef(player->x, player->y, 0);
    drawTexturedSquare(2);
    glPopMatrix();
}

void drawObstacle(Obstacle obstacle)
{
    glPushMatrix();
    glTranslatef(obstacle->x, obstacle->y, 0);
    drawTexturedSquare(4);
    glPopMatrix();
}

void drawEnnemi(Ennemi ennemi)
{
    glPushMatrix();
    glTranslatef(ennemi->x, ennemi->y, 0);
    drawTexturedSquare(3);
    glPopMatrix();
}

void drawProj(Projectiles proj)
{
    glPushMatrix();
    glTranslatef(proj->x, proj->y, 0);
    drawTexturedSquare(5);
    glPopMatrix();
}

void drawLine(Line line)
{
    glPushMatrix();
    glTranslatef(line->x, line->y, 0);
    drawTexturedSquare(7);
    glPopMatrix();
}



void drawBonus(Bonus bonus)
{
    glPushMatrix();
    glTranslatef(bonus->x, bonus->y, 0);
    drawTexturedSquare(6);
    glPopMatrix();
}

void drawBG()
{
  // Code de dessin
  glPushMatrix();
  glScalef(20,20,1);
   drawTexturedSquare(8);
  glPopMatrix();
  // Fin du code de dessin
}

void drawYouWin()
{
  // Code de dessin
  glPushMatrix();
  glScalef(20,20,1);
   drawTexturedSquare(10);
  glPopMatrix();
  // Fin du code de dessin
}

void drawYouLose()
{
  // Code de dessin
  glPushMatrix();
  glScalef(20,20,1);
   drawTexturedSquare(9);
  glPopMatrix();
  // Fin du code de dessin
}
