#include<stdio.h>
#include"SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "jeux.h"

void initialiser_score(sco *score,sec se)
{
TTF_Init();
score->font=TTF_OpenFont("BebasNeue-Book.ttf", 50);
SDL_Color color={255,0,0};
char ch[10];
sprintf(ch,"%d XP",score->sscore);
score->score=TTF_RenderText_Solid(score->font,ch,color);
SDL_BlitSurface(score->score,NULL,se.screen,&score->position_score);
SDL_Flip(se.screen);
TTF_Quit();
}


void DepAlea(ennemi *en,deplacement *d)
{ 
    int x;
    x=(rand()%2)+1;
    switch(x)
       {
       case 1:
        if((en->positionsp.x<en->intermax))
            en->positionsp.x+=20;
	    en->positionjoueur.x+=4;
        break;
       case 2:
        if((en->positionsp.x>en->intermin))
            en->positionsp.x-=20;
	    en->positionjoueur.x-=4;
        break;
       }
}


void menu(sec se,ennemi *en)
{
en->imagejoueur=IMG_Load("joueur.png"); //position mini map ennmi
SDL_BlitSurface(en->imagejoueur,NULL,se.screen,&en->positionjoueur);
}

void deplacement_perso(deplacement *d)
{
d->start=0;
if(d->positionperso.x<=500)
{
d->start=1;
}
SDL_Delay(100);
}
