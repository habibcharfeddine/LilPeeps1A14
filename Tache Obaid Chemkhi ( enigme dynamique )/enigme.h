#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "time.h"
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include<math.h>

int generate_question(int*n);
void init_afficher_question(int n,SDL_Surface *screen);
int resolution(int n);
int reponse(int *rep );
void afficher_resultat (SDL_Surface * screen,int solution,int r);
