
#include "init.h"


void init(char *title)
{
	/* Initialise SDL Video */
	if (SDL_Init(SDL_INIT_VIDEO ) < 0)
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	jeu.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWPALETTE|SDL_DOUBLEBUF);

    if (jeu.screen == NULL)
        {
            printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
            exit(1);
        }

	/* Titre de la fenetre */
	SDL_WM_SetCaption(title, NULL);

	/* Initialise SDL_TTF */
	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());

		exit(1);
	}





      int flags=MIX_INIT_MP3;
    int initted=Mix_Init(flags);
	/* open 44.1KHz, signed 16bit, system byte order,
           stereo audio, using 1024 byte chunks */
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
    


    /* Définit le nombre de channels à mixer */
    Mix_AllocateChannels(32);



}


void loadGame(void)
{

    /* Charge l'image du fond et le tileset */
    map.background = loadImage("graphics/background.png");

    //On commence au premier niveau
    jeu.level = 1;
    changeLevel();

    //On initialise le timer
     map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
     map.tileSetNumber = 0;

    /* On initialise les variables du jeu */
    jeu.vies = 3;
    jeu.etoiles = 0;



}



void cleanup()
{

    int i;

    /* Libère l'image du background */
	if (map.background != NULL)
	{
		SDL_FreeSurface(map.background);
	}


    /* Libère l'image des tilesets */
    if (map.tileSet != NULL)
    {
        SDL_FreeSurface(map.tileSet);
    }
    if (map.tileSetB != NULL)
    {
        SDL_FreeSurface(map.tileSetB);
    }


	/* Quitte la SDL */
	SDL_Quit();

}



