

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <SDL/SDL.h>
/* On inclut les libs supplémentaires */
#include <SDL/SDL_image.h>

/* Taille de la fenêtre / résolution en plein écran */
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

/* Valeur RGB pour la transparence (canal alpha) */
#define TRANS_R 255
#define TRANS_G 0
#define TRANS_B 255

/* Taille maxi de la map : on voit large : 400 x 300 tiles */
#define MAX_MAP_X 400
#define MAX_MAP_Y 300

/* Taille d'une tile (32 x 32 pixels) */
#define TILE_SIZE 32

/* Taille du sprite de notre héros (largeur = width et hauteur = heigth) */
#define PLAYER_WIDTH 40
#define PLAYER_HEIGTH 80

/* Constantes pour l'animation */
#define TIME_BETWEEN_2_FRAMES 8

//Vitesse de déplacement en pixels du sprite
#define PLAYER_SPEED 4

//Valeurs attribuées aux états/directions
#define WALK 1
#define IDLE 2
#define JUMP 3
#define RIGHT 1
#define LEFT 2

// Constante définissant le seuil entre les tiles traversables (blank) et les tiles solides
#define BLANK_TILE 5

//Constantes définissant la gravité et la vitesse max de chute
#define GRAVITY_SPEED 0.6
#define MAX_FALL_SPEED 10
#define JUMP_HEIGHT 13


