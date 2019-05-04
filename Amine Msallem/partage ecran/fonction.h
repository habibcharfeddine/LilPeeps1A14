#ifndef FONCTION_H_
#define FONCTION_H_
#include<stdio.h>
#include<stdlib.h>
#include<SDL/SDL.h>
#include <SDL/SDL_image.h>


typedef struct  {
SDL_Surface *screen,*image,*background1,*image2,*background2;
SDL_Event event ;
SDL_Rect rect ,rect2 ;
int running;
int frame,frame2;
//SDL_Rect camera1,back1,camera2,back2;
SDL_Rect rects[6],rects2[6];
}acteur;

void setrects_right(SDL_Rect clip[]);
void setrects_left(SDL_Rect clip[]);
void scrollingleft(SDL_Rect *rect , SDL_Rect *positionFond );
void scrollingright(SDL_Rect *rect , SDL_Rect *positionFond );
void scrollingleft2(SDL_Rect *rect , SDL_Rect *positionFond );
void scrollingright2(SDL_Rect *rect , SDL_Rect *positionFond );
void animation(acteur *acteur);

#endif
