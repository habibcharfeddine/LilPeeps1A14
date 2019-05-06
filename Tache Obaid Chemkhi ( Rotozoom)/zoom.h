#include<stdio.h>
#include"SDL/SDL.h"
#include"SDL/SDL_image.h"
#ifndef ZOOM_H_INCLUDED
#define ZOOM_H_INCLUDED
void roto(SDL_Surface *screen,SDL_Surface *image, SDL_Surface *rotation,SDL_Rect rect , SDL_Event event);

#endif // ZOOM_H_INCLUDED
