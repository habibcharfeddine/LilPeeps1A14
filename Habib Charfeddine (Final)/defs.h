

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
//On rajoute glsdl qui va remplacer la SDL
#include "glSDL.h"
/* #include <SDL/SDL.h> */

/* On inclut les libs suppl�mentaires */
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_rotozoom.h>
#include <SDL/SDL_gfxPrimitives.h>
/* Taille de la fen�tre / r�solution en plein �cran */
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 700

/* Valeur RGB pour la transparence (canal alpha) */
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255

/* Taille maxi de la map : on voit large : 400 x 300 tiles */
#define MAX_MAP_X 400
#define MAX_MAP_Y 300

/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32

/* Taille du sprite de notre h�ros (largeur = width et hauteur = heigth) */
#define PLAYER_WIDTH 40
#define PLAYER_HEIGTH 80

/* Constantes pour l'animation */
#define TIME_BETWEEN_2_FRAMES 8

//Vitesse de d�placement en pixels du sprite
#define PLAYER_SPEED 4

//Valeurs attribu�es aux �tats/directions
#define WALK_RIGHT 1
#define WALK_LEFT 2
#define IDLE 3
#define JUMP_RIGHT 4
#define JUMP_LEFT 5
#define RIGHT 1
#define LEFT 2

// Constante d�finissant le seuil entre les tiles traversables (blank) et les tiles solides
#define BLANK_TILE 10

//Autres Tiles sp�ciales

#define TILE_RESSORT 12
#define TILE_CHECKPOINT 9
#define TILE_MONSTRE 17

#define TILE_POWER_UP_DEBUT 7
#define TILE_POWER_UP_FIN 8

#define TILE_PLATEFORME_DEBUT 15
#define TILE_PLATEFORME_FIN 16

//Constantes d�finissant la gravit� et la vitesse max de chute
#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 10
#define JUMP_HEIGHT 13

//Nombre max de monstres � l'�cran
#define MONSTRES_MAX 50

//Nombre max de boules de feu � l'�cran
#define FIREBALLS_MAX 3

//Nombre max de levels
#define LEVEL_MAX 2

/* Gestion des plateformes mobiles */
#define PLATEFORMES_MAX 50
#define PLATEFORMES_TILES_DEBUT 15
#define PLATEFORMES_TILES_FIN 16
#define PLATEFORM_SPEED 2
#define UP 3
#define	DOWN 4




enum
{
	BUMPER,
	DESTROY,
	JUMP,
    STAR
};

enum
{
	START,
	PAUSE
};




