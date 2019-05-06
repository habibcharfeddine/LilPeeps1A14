#ifndef JEUX
#define JEUX
#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
typedef struct
{
SDL_Surface *screen;
SDL_Surface *image,*imagemap;
SDL_Rect positionecran,positionecran1,positionmap;
}sec;

typedef struct 
{
TTF_Font *font;
SDL_Surface *score;
SDL_Rect position_score;
int sscore;
}sco;


typedef struct
{
SDL_Surface *imagedep,*imagejoueur;
SDL_Rect positionsp,positionjoueur;
int intermin;
int intermax;
}ennemi;

typedef struct
{
SDL_Surface *imageperso,*imagemape;
SDL_Rect positionperso,positionmape;
int start;
}deplacement;


void initialiser_score(sco *s,sec se);
void DepAlea(ennemi *en,deplacement *d);
void menu(sec se,ennemi *en);
void deplacement_perso(deplacement *d);
#endif
