/**
* @file init.c
* @brief INITIALISATION
* @author lil peeps
* LOAD GAME WITH INITIAL SETTINGS
*/
#include "init.h"


void init(char *title)
{
	/* Initialise SDL Video */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_GLSDL) < 0)
	{
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		exit(1);
	}

	jeu.screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_HWPALETTE|SDL_DOUBLEBUF);

    if (jeu.screen == NULL)
        {
            printf("Couldn't set screen mode to %d x %d: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
            exit(1);
        }

	/* Titre de la fenetre */
	SDL_WM_SetCaption(title, NULL);


	/* Cache le curseur de la souris */
	//SDL_ShowCursor(SDL_DISABLE);


	/* Initialise SDL_TTF */
	if (TTF_Init() < 0)
	{
		printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());

		exit(1);
	}

	/* Chargement de la police */
	font = loadFont("font/GenBasB.ttf", 32);


	/* Initialise SDL_Mixer */

     int flags=MIX_INIT_MP3;
    int initted=Mix_Init(flags);
	/* open 44.1KHz, signed 16bit, system byte order,
           stereo audio, using 1024 byte chunks */
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1)
    {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(1);
    }
    


    /* D�finit le nombre de channels � mixer */
    Mix_AllocateChannels(32);

}


void loadGame(void)
{

    /* Charge l'image du fond et le tileset */
    map.background = loadImage("graphics/background.png");
    //map.background = rotozoomSurface  (map.background, 0, 2, 1);


    //On commence au premier niveau
    jeu.level = 1;
    changeLevel();

    //On initialise le timer
     map.mapTimer = TIME_BETWEEN_2_FRAMES * 3;
     map.tileSetNumber = 0;

    /* On initialise les variables du jeu */
    jeu.vies = 3;
    jeu.vies2 = 3;
    jeu.etoiles = 0;
    jeu.etoiles2 = 0;

    /* On charge le HUD */
    jeu.HUD_vie = loadImage("graphics/life.png");
    jeu.HUD_etoiles = loadImage("graphics/stars.png");

    //On charge le shuriken
    jeu.Shuriken_image = loadImage("graphics/shuriken.png");

    //On charge notre plateforme
    loadPlateforme();

    //On charge la musique
    loadSong("music/RabidjaGo.mp3");

    /* On charge les sounds Fx */
    loadSound();

    //On commence par le menu start
    jeu.onMenu = 1;
    jeu.menuType = START;

}



void cleanup()
{

    int i;

    /* Lib�re l'image du background */
	if (map.background != NULL)
	{
		SDL_FreeSurface(map.background);
	}


    /* Lib�re l'image des tilesets */
    if (map.tileSet != NULL)
    {
        SDL_FreeSurface(map.tileSet);
    }
    if (map.tileSetB != NULL)
    {
        SDL_FreeSurface(map.tileSetB);
    }


	/* Lib�re le sprite du h�ros */
	if (player.sprite != NULL)
	{
		SDL_FreeSurface(player.sprite);
	}

	/* Lib�re le sprite des monstres */
	for(i = 0 ; i < MONSTRES_MAX ; i++)
    {
        if (monster[i].sprite != NULL)
        {
            SDL_FreeSurface(monster[i].sprite);
        }
    }

	//Lib�re le HUD
	if (jeu.HUD_etoiles != NULL)
	{
		SDL_FreeSurface(jeu.HUD_etoiles);
	}
	if (jeu.HUD_vie != NULL)
	{
		SDL_FreeSurface(jeu.HUD_vie);
	}

	//Lib�re le shuriken
	if (jeu.Shuriken_image != NULL)
	{
		SDL_FreeSurface(jeu.Shuriken_image);
	}

	//Lib�re la plateforme
	if (jeu.plateforme != NULL)
	{
		SDL_FreeSurface(jeu.plateforme);
	}

	/* On lib�re la chanson */
    if ( jeu.musique != NULL )
        Mix_FreeMusic(jeu.musique);

    //On lib�re les sons
    freeSound();

	// Quitte SDL_Mixer et d�charge la m�moire
    Mix_CloseAudio();
    Mix_Quit();

	/* Close the font */
	closeFont(font);

	/* Close SDL_TTF */
	TTF_Quit();

	/* Quitte la SDL */
	SDL_Quit();

}



