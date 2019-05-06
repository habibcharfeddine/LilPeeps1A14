#ifndef JEU_H
#define JEU_H
#include <SDL/SDL.h>
#include "background.h"
#include "personnage.h"
#include "scorevie.h"

struct jeu 
{ 
perso p1 ;
perso p2;
int game_over ;
int passe;
Background B1;
Background B2;
score s1;
vie v1;
score s2;
vie v2;
int i;
} ;
typedef struct jeu jeu ;






#endif
