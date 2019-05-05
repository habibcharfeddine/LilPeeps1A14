

#include "defs.h"

/* Structures qui seront utilis�es pour g�rer le jeu */

/* Structure pour g�rer l'input (clavier puis joystick) */

typedef struct Input
{
	int left, right, up, down, jump, attack, enter, erase, pause;
} Input;


/* Structure pour g�rer le niveau (� compl�ter plus tard) */

typedef struct Gestion
{

    SDL_Surface *screen;

} Gestion;


/* Structure pour g�rer la map � afficher (� compl�ter plus tard) */

typedef struct Map
{

	SDL_Surface *background, *tileSet;

	/* Coordonn�es de d�but, lorsqu'on doit dessiner la map */
	int startX, startY;

	/* Coordonn�es max de fin de la map */
	int maxX, maxY;

	/* Tableau � double dimension repr�sentant la map de tiles */
	int tile[MAX_MAP_Y][MAX_MAP_X];

} Map;


/* Structure pour g�rer notre h�ros */

typedef struct Hero
{
    //Sprite du h�ros (pas d'animation pour l'instant)
	SDL_Surface *sprite;

	/* Coordonn�es du h�ros */
	int x, y;
	/* Largeur, hauteur du sprite */
	int h, w;

	/* Variables utiles pour l'animation */
	int frameNumber, frameTimer;
	int etat, direction;

	/* Variables utiles pour la gestion des collisions */
	int onGround, timerMort;
	float dirX, dirY;



} Hero;


