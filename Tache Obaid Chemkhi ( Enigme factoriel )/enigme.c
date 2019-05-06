#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "time.h"
#include "SDL/SDL.h"
#include <SDL/SDL_image.h>
#include<math.h>
#include "SDL/SDL_ttf.h"
#include "enigme.h"

int generate_question(int*n)
{
    int a;
	srand(time(NULL));
 *n= 1+ rand()%6;
  a=(*n);
 return a;
}

void init_afficher_question(int n,SDL_Surface *screen)
{
char question[100];

 sprintf(question ,"calculate the factorial of %d",n);
 SDL_Surface *background = NULL;
SDL_Surface *message = NULL;
//Le Font qu'on va utiliser
TTF_Font *font=NULL;
//La couleur du Font
SDL_Color textColor = { 0, 76, 153 };
//Initialisation de SDL_TTF
	if( TTF_Init() == -1 ) {
		printf("false");
	}

	//Mise en place de la barre caption


 background = IMG_Load("background.png" );
 font = TTF_OpenFont( "Ariel.ttf", 30 );
//Mise en place du texte sur la surface message
message = TTF_RenderText_Solid( font, question, textColor );
 //Application des images sur l'écran
SDL_Rect *p;
p->x=260;
p->y=150;
 SDL_BlitSurface( background, NULL,  screen,NULL );
 SDL_BlitSurface( message, NULL,  screen,p );
 SDL_Flip(screen) ;

	//Fermeture des Fonts qu'on a utilisé
	TTF_CloseFont( font );
	//On quitte SDL_ttf
	TTF_Quit();
}
int resolution(int n)
{
int i,fact;
fact = 1;
for(i=1;i<=n;i++)
{
    fact = fact*i;
}
 return fact;

}


int reponse(int *rep )
{
    int i,r,y,z,coff;
    (*rep)=0;
	SDL_Event event ;
  	int continuer=1;
	while(continuer)
	{
	    SDL_WaitEvent(&event);
        switch(event.type)
	{
		  case SDL_QUIT:
            continuer=0;
          break ;

       case SDL_KEYDOWN :
            switch( event.key.keysym.sym )
                {
			  case  SDLK_KP1:
                  r= 1;
                  (*rep)=(r*100);
                    continuer=0;
			   break ;
			   case  SDLK_KP2 :
                   r=2;
                   (*rep)=(r*100);
                    continuer=0;
			   break;
			   case SDLK_KP3:
                   r=3;
                   (*rep)=(r*100);
                    continuer=0;
			  break;

              case  SDLK_KP4:
                  r=4;
                  (*rep)=(r*100);
                  continuer=0;
			   break ;
              case  SDLK_KP5:
                  r= 5;
                  (*rep)=(r*100);
                  continuer=0;
			   break ;
              case  SDLK_KP6:
			  r= 6;
			  (*rep)=(r*100);
            continuer=0;
			   break ;
            case  SDLK_KP7:
			  r= 7;
			  (*rep)=(r*100);
              continuer=0;
			   break ;
             case  SDLK_KP8:
                  r= 8;
                  (*rep)=(r*100);
                  continuer=0;
			   break ;
                case  SDLK_KP9:
                      r= 9;
                      (*rep)=(r*100);
                      continuer=0;
			   break ;
                case  SDLK_KP0:
                  r= 0;
                  (*rep)=(*rep)+z;
                  continuer=0;
			   break ;
}
       break ;


	}
	}
	continuer=1;

/*second int*/
	while(continuer)
	{
    SDL_WaitEvent(&event);
	switch(event.type)
	{
        case SDL_QUIT:
            continuer=0;
        break ;

       case SDL_KEYDOWN :
            switch( event.key.keysym.sym )
                {
			  case  SDLK_KP1:
			   y= 1;
			  (*rep)=(*rep)+(y*10);
              continuer=0;
			   break ;
			   case  SDLK_KP2 :
			   y= 2;(*rep)=(*rep)+(y*10);
				continuer=0;
			   break;
			   case SDLK_KP3:
			   y=3 ;(*rep)=(*rep)+(y*10);
			continuer=0;
			  break;

             case  SDLK_KP4:
			  y= 4;
			  (*rep)=(*rep)+(y*10);
              continuer=0;
			   break ;
             case  SDLK_KP5:
			  y= 5;
			  (*rep)=(*rep)+(y*10);
              continuer=0;
			   break ;
             case  SDLK_KP6:
			  y= 6;(*rep)=(*rep)+(y*10);
				continuer=0;
			   break ;
             case  SDLK_KP7:
			  y= 7;
			  (*rep)=(*rep)+(y*10);
              continuer=0;
			   break ;
             case  SDLK_KP8:
			  y= 8;
			  (*rep)=(*rep)+(y*10);
              continuer=0;
			   break ;
             case  SDLK_9:
			  y= 9;
			  (*rep)=(*rep)+(y*10);
              continuer=0;
			   break ;
             case  SDLK_KP0:
			  y= 0;
			  (*rep)=(*rep)+z;
				continuer=0;
			   break ;
}
       break ;


	}
	}continuer=1;

/*third int*/
while(continuer)
	{SDL_WaitEvent(&event);
	switch(event.type)
	{
		  case SDL_QUIT:
		continuer=0;
				break ;

       case SDL_KEYDOWN :
            switch( event.key.keysym.sym )
                {
			  case  SDLK_KP1:
			  z= 1;(*rep)=(*rep)+z;
				continuer=0;
			   break ;
			   case  SDLK_KP2 :
			   z= 2;(*rep)=(*rep)+z;
				continuer=0;
			   break;
			   case SDLK_KP3:
			   z=3 ;(*rep)=(*rep)+z;
			continuer=0;
			  break;

             case  SDLK_KP4:
			  z= 4;(*rep)=(*rep)+z;
				continuer=0;
			   break ;
             case  SDLK_KP5:
			  z= 5;(*rep)=(*rep)+z;
				continuer=0;
			   break ;
             case  SDLK_KP6:
			  z= 6;(*rep)=(*rep)+z;
				continuer=0;
			   break ;
             case  SDLK_KP7:
			  z= 7;
			  (*rep)=(*rep)+z;
				continuer=0;
			   break ;
             case  SDLK_KP8:
			  z= 8;
			  (*rep)=(*rep)+z;
				continuer=0;
			   break ;
             case  SDLK_KP9:
			  z= 9;(*rep)=(*rep)+z;
				continuer=0;
			   break ;
             case  SDLK_KP0:
			  z= 0;
			  (*rep)=(*rep)+z;
              continuer=0;
			   break ;
}
       break ;


	}
	}


int b;
b=(*rep);
return b;
}


void afficher_resultat (SDL_Surface * screen,int solution,int r)
 {SDL_Surface *background; background=NULL;

 	if (r==solution)
 	{
 		background=IMG_Load("00.png");
 		SDL_BlitSurface(background, NULL, screen, NULL) ;
        SDL_Flip(screen);
	SDL_Delay(3000);
 	}
 	else
 	{
 		background=IMG_Load("11.png");
 		SDL_BlitSurface(background, NULL, screen, NULL) ;
        SDL_Flip(screen);
	SDL_Delay(3000);
 	}
 }

