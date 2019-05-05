

#include "defs.h"

/* Structures qui seront utilisées pour gérer le jeu */

/* Structure pour gérer l'input (clavier puis joystick) */

typedef struct Input
{
	int left, right, up, down, jump, attack, enter, erase, pause;
} Input;


/* Structure pour gérer le niveau (à compléter plus tard) */

typedef struct Gestion
{

    SDL_Surface *screen;

} Gestion;


/* Structure pour gérer la map à afficher (à compléter plus tard) */

typedef struct Map
{

	SDL_Surface *background, *tileSet;

	/* Coordonnées de début, lorsqu'on doit dessiner la map */
	int startX, startY;

	/* Coordonnées max de fin de la map */
	int maxX, maxY;

	/* Tableau à double dimension représentant la map de tiles */
	int tile[MAX_MAP_Y][MAX_MAP_X];

} Map;


/* Structure pour gérer notre héros */

typedef struct Hero
{
    //Sprite du héros (pas d'animation pour l'instant)
	SDL_Surface *sprite;

	/* Coordonnées du héros */
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


