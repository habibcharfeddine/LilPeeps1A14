#include<stdio.h>
#include<stdlib.h>
#include"SDL/SDL.h"
#include<SDL/SDL_image.h>
#include<SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include "jeux.h"
int main(void)
{
sec se; 
sco s;
ennemi en;
deplacement d;
int v=1;
int done=1;
SDL_Rect positionecran,positionecran1;
SDL_Event event;
SDL_Init(SDL_INIT_VIDEO);

if( SDL_Init(SDL_INIT_VIDEO)!=0)
{
printf("unabel to initialize SDL:%s\n",SDL_GetError());
return (-1);
}
se.screen=SDL_SetVideoMode(1700,790,32, SDL_HWSURFACE |SDL_DOUBLEBUF);
se.image=SDL_LoadBMP("marche2.bmp");
se.imagemap=SDL_LoadBMP("map2.bmp");

se.positionecran.x=0;
se.positionecran.y=0;
se.positionecran.w=se.image->w;
se.positionecran.h=se.image->h;
se.positionecran1.x=0;
se.positionecran1.y=0;//background
se.positionecran1.w=se.image->w;
se.positionecran1.h=se.image->h;

se.positionmap.x=700;
se.positionmap.y=650;//minimap
se.positionmap.w=se.imagemap->w;
se.positionmap.h=se.imagemap->h;


en.positionsp.x=200;//ennemi
en.positionsp.y=590;//ennemi
d.positionperso.x=600;//position habib
d.positionperso.y=590;

en.intermin=60;
en.intermax=360;



en.positionjoueur.x=740;//position joueur mini
en.positionjoueur.y=766;

d.positionmape.x=790;
d.positionmape.y=766;




en.imagedep=IMG_Load("imagedep.png");//nokta habib mini 
d.imageperso=IMG_Load("imageperso.png");//hero
d.imagemape=IMG_Load("imagemape.png");//nokta ennmi

SDL_BlitSurface(se.image,&se.positionecran1,se.screen,&se.positionecran);
SDL_BlitSurface(se.imagemap,NULL,se.screen,&se.positionmap);
SDL_BlitSurface(en.imagedep,NULL,se.screen,&en.positionsp);
SDL_BlitSurface(d.imageperso,NULL,se.screen,&d.positionperso);
SDL_BlitSurface(d.imagemape,NULL,se.screen,&d.positionmape);

while(done)
{
SDL_EnableKeyRepeat(10,10);
SDL_PollEvent(&event);
  switch(event.type) 
    {
       case SDL_QUIT: 
         done = 0; 
        SDL_Quit();
          break;
          case SDL_KEYDOWN:
            switch(event.key.keysym.sym)
                {
                    case SDLK_LEFT:  
			d.positionperso.x += -4; 
			d.positionmape.x +=-1;
                         break;
                    case SDLK_RIGHT:
			d.positionperso.x += 4; 
			d.positionmape.x +=1;
                        break;
                    case SDLK_a: 
                       s.sscore=s.sscore+10; 
                         break;
                 }
     break;
  }
deplacement_perso(&d);
if(d.start==1)
{
DepAlea(&en,&d);
}
initialiser_score(&s,se);
switch(v)
{
case 1: 
SDL_BlitSurface(se.image,&se.positionecran1,se.screen,&se.positionecran);
SDL_BlitSurface(se.imagemap,NULL,se.screen,&se.positionmap);
SDL_BlitSurface(en.imagedep,NULL,se.screen,&en.positionsp);
SDL_BlitSurface(d.imageperso,NULL,se.screen,&d.positionperso);
SDL_BlitSurface(d.imagemape,NULL,se.screen,&d.positionmape);
menu(se,&en);
break;
}
}
SDL_Quit();
return 0;
}
