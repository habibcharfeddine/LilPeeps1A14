

#include "main.h"


int main(int argc, char *argv[])
{
	unsigned int frameLimit = SDL_GetTicks() + 16;
	int go, i,fullscreen=0,sound=1;
	
	Mix_OpenAudio(44100,MIX_DEFAULT_FORMAT,MIX_DEFAULT_CHANNELS,1024);
	Mix_AllocateChannels(10);
	Mix_VolumeMusic(128);   	
	/* Initialisation de la SDL */
	init("Wales");

	/* On initialise le joueur */
	initializePlayer();

	/* Chargement des ressources (graphismes, sons) */
	loadGame();

	/* Appelle la fonction cleanup à la fin du programme */
	atexit(cleanup);

	go = 1;


	/* Boucle infinie, principale, du jeu */

	while (go == 1)
	{
		/* On prend en compte les input (clavier, joystick... */
		getInput();

        //Si on n'est pas dans un menu
        if(jeu.onMenu == 0)
        {
            /* On met à jour le jeu */
            updatePlayer();
            updateMonsters();
        }
        else
        {
            if(jeu.menuType == START)
                drawStartMenu(jeu.screen,&sound,&fullscreen);
            else if(jeu.menuType == PAUSE)
                updatePauseMenu();
        }


        //Si on n'est pas dans un menu
        if(jeu.onMenu == 0)
        {
            /* On affiche tout */
            draw();
        }
        else
        {
            if(jeu.menuType == START)
            {
                //drawImage(map.background, 0, 0);
                drawStartMenu(jeu.screen,&sound,&fullscreen);
                SDL_Flip(jeu.screen);
                SDL_Delay(1);
            }
            else if(jeu.menuType == PAUSE)
            {
                drawPauseMenu(jeu.screen,&sound,&fullscreen);
                SDL_Flip(jeu.screen);
                SDL_Delay(1);
            }

        }
		/* Gestion des 60 fps (1000ms/60 = 16.6 -> 16 */
		delay(frameLimit);
		frameLimit = SDL_GetTicks() + 16;

		
	}

	/* Exit */
	exit(0);
}

