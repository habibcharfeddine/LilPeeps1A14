/**
* @file cinematic.c
* @brief load cinematic
* @author lil peeps
* load game cinematic
*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <SDL/SDL_ttf.h>
#include <string.h>

void animation(SDL_Surface *ecran)
{
SDL_Surface *img;
SDL_Rect pos; pos.x=0;pos.y=0;
char chaine[20];

int i=0;
int g=1;
Mix_Music *musique;
char nom[10],nn[10];
SDL_Event event;
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
				musique = Mix_LoadMUS("./C1/a.mp3");
			Mix_PlayMusic(musique, -1);
			Mix_VolumeMusic(MIX_MAX_VOLUME);

while(g==1)
{

	strcpy(nom,"./C1/coat0000");
				if(i>9){strcpy(nom,"./C1/coat000");}
				if(i>99){strcpy(nom,"./C1/coat00");}

			sprintf(nn,"%d",i);
			strcat(nom,nn);
			strcat(nom,".jpg");
			img= IMG_Load(nom);
			SDL_BlitSurface(img,NULL,ecran,&pos);
			SDL_Flip(ecran);
			SDL_FreeSurface(img);
			i++;
while(SDL_PollEvent(&event)){

	switch(event.type)
		{		
				case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
			{case SDLK_RETURN:
				g=0;
				break;
				case SDLK_BACKSPACE:
				g=0;
				break;
			}
			break;}

}
if(i==384){g=0;}
}

Mix_CloseAudio();
Mix_FreeMusic(musique);
}




void load(SDL_Surface *ecran)
{ 
TTF_Init();
TTF_Font *police = NULL;
SDL_Surface *img;
SDL_Color blanc={250,250,250};
 police = TTF_OpenFont("./font/angelina.TTF", 80); 
SDL_Surface *texte=NULL;

SDL_Rect postexte;postexte.x=500;postexte.y=500;
texte = TTF_RenderText_Blended(police, "l", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(700);
texte = TTF_RenderText_Blended(police, "lo", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(700);
texte = TTF_RenderText_Blended(police, "loa", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(500);
texte = TTF_RenderText_Blended(police, "load", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(700);
texte = TTF_RenderText_Blended(police, "loadi", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(800);
texte = TTF_RenderText_Blended(police, "loadin", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(700);
texte = TTF_RenderText_Blended(police, "loading", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(700);
texte = TTF_RenderText_Blended(police, "loading.", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(700);
			texte = TTF_RenderText_Blended(police, "loading..", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(700);
			texte = TTF_RenderText_Blended(police, "loading...", blanc);
			SDL_BlitSurface(texte,NULL,ecran,&postexte);
			SDL_Flip(ecran);SDL_Delay(700);
	TTF_CloseFont(police);
SDL_FreeSurface(texte);
TTF_Quit();


}


void animation_coat(SDL_Surface *ecran)
{
SDL_Surface *img;
SDL_Rect pos; pos.x=0;pos.y=0;
char chaine[20];

int i=0;
int g=1;
Mix_Music *musique;
char nom[10],nn[10];
SDL_Event event;
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
				musique = Mix_LoadMUS("./c/c.mp3");
			Mix_PlayMusic(musique, -1);
			Mix_VolumeMusic(MIX_MAX_VOLUME);

while(g==1)
{

	strcpy(nom,"./C/c0000");
				if(i>9){strcpy(nom,"./c/c000");}
				if(i>99){strcpy(nom,"./c/c00");}

			sprintf(nn,"%d",i);
			strcat(nom,nn);
			strcat(nom,".png");
			img= IMG_Load(nom);
			SDL_BlitSurface(img,NULL,ecran,&pos);
			SDL_Flip(ecran);
			SDL_FreeSurface(img);
			i++;
while(SDL_PollEvent(&event)){

	switch(event.type)
		{		
				case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
			{case SDLK_RETURN:
				g=0;
				break;
				case SDLK_BACKSPACE:
				g=0;
				break;
			}
			break;}

}
if(i==543){g=0;}
}

Mix_CloseAudio();
Mix_FreeMusic(musique);
}

void animation_coatss(SDL_Surface *ecran)
{

SDL_Surface *img;
SDL_Rect pos; pos.x=0;pos.y=0;
char chaine[20];

int i=0;
int g=1;
int t=0;
Mix_Music *musique;
char nom[10],nn[10];
SDL_Event event;
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
				musique = Mix_LoadMUS("./c/c.mp3");
			Mix_PlayMusic(musique, -1);
			Mix_VolumeMusic(MIX_MAX_VOLUME);
while(g==1)
{

	strcpy(nom,"./coa/c0000");
				if(i>9){strcpy(nom,"./c/c000");}
				if(i>99){strcpy(nom,"./c/c00");}

			sprintf(nn,"%d",i);
			strcat(nom,nn);
			strcat(nom,".jpg");
			img= IMG_Load(nom);
			SDL_BlitSurface(img,NULL,ecran,&pos);
			SDL_Flip(ecran);
			SDL_FreeSurface(img);
			i++;
while(SDL_PollEvent(&event)){

	switch(event.type)
		{		
				case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
			{case SDLK_RETURN:
				g=0;
				break;
				case SDLK_BACKSPACE:
				g=0;
				break;
			}
			break;}

}
if(i==187){
	if(t==6){g=0;}
t++;
i=130;
	
}
}
Mix_CloseAudio();
Mix_FreeMusic(musique);
}


void animation_logo(SDL_Surface *ecran)
{
SDL_Surface *img;
SDL_Rect pos; pos.x=0;pos.y=0;
char chaine[20];

int i=0;
int g=1;
int t=0;
Mix_Music *musique;
char nom[10],nn[10];
SDL_Event event;
Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
				musique = Mix_LoadMUS("./logo/logo_music.mp3");
			Mix_PlayMusic(musique, -1);
			Mix_VolumeMusic(MIX_MAX_VOLUME);
while(g==1)
{

	strcpy(nom,"./logo/logo0000");
				if(i>9){strcpy(nom,"./logo/logo000");}
				if(i>99){strcpy(nom,"./logo/logo00");}

			sprintf(nn,"%d",i);
			strcat(nom,nn);
			strcat(nom,".jpg");
			img= IMG_Load(nom);
			SDL_BlitSurface(img,NULL,ecran,&pos);
			SDL_Flip(ecran);
			SDL_FreeSurface(img);
			i++;
while(SDL_PollEvent(&event)){

	switch(event.type)
		{		
				case SDL_KEYDOWN:
		switch(event.key.keysym.sym)
			{case SDLK_RETURN:
				g=0;
				break;
				case SDLK_BACKSPACE:
				g=0;
				break;
			}
			break;}

}
if(i==543){g=0;}

}
Mix_CloseAudio();
Mix_FreeMusic(musique);


}





