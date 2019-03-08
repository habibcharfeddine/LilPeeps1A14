
#include "draw.h"


void drawImage(SDL_Surface *image, int x, int y)
{
	SDL_Rect dest;

	/* R�gle le rectangle � blitter selon la taille de l'image source */
	dest.x = x;
	dest.y = y;
	dest.w = image->w;
	dest.h = image->h;

	/* Blitte l'image enti�re sur l'�cran aux coordonn�es x et y */
	SDL_BlitSurface(image, NULL, jeu.screen, &dest);
}


void drawTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy)
{
    /* Rectangle de destination � blitter */
	SDL_Rect dest;

	dest.x = destx;
	dest.y = desty;
	dest.w = TILE_SIZE;
	dest.h = TILE_SIZE;

	/* Rectangle source � blitter */
	SDL_Rect src;

	src.x = srcx;
	src.y = srcy;
	src.w = TILE_SIZE;
	src.h = TILE_SIZE;

	/* Blitte la tile choisie sur l'�cran aux coordonn�es x et y */
	SDL_BlitSurface(image, &src, jeu.screen, &dest);
}


void draw(void)
{

    int i;

    /* Affiche le fond (background) aux coordonn�es (0,0) */
    drawImage(map.background, 0, 0);

    /* Affiche la map de tiles */
    drawMap();

    /* Affiche le joueur */
    drawAnimatedEntity(&player);

    /* Affiche les monstres */
    for(i = 0 ; i < jeu.nombreMonstres ; i++)
    {
        drawAnimatedEntity(&monster[i]);
    }

    //On affiche le HUD par-dessus tout le reste
    drawHud();

    /* Affiche l'�cran */
    SDL_Flip(jeu.screen);

    /* Delai */
    SDL_Delay(1);

}



SDL_Surface *loadImage(char *name)
{
	/* Charge les images avec SDL Image */
	SDL_Surface *temp = IMG_Load(name);
	SDL_Surface *image;

	if (temp == NULL)
	{
		printf("Failed to load image %s\n", name);
		return NULL;
	}

	/* Gestion de la transparence */
	SDL_SetColorKey(temp, (SDL_SRCCOLORKEY|SDL_RLEACCEL), SDL_MapRGB(temp->format, TRANS_R, TRANS_G, TRANS_B));


	/* Convertit l'image au format de l'�cran (screen) */
	image = SDL_DisplayFormat(temp);

	SDL_FreeSurface(temp);

	if (image == NULL)
	{
		printf("Failed to convert image %s to native format\n", name);

		return NULL;
	}

	/* Retourne l'image au format de l'�cran pour acc�l�rer son blit */
	return image;

}



void delay(unsigned int frameLimit)
{

    /* Gestion des 60 fps */
    unsigned int ticks = SDL_GetTicks();

    if (frameLimit < ticks)
    {
        return;
    }

    if (frameLimit > ticks + 16)
    {
        SDL_Delay(16);
    }

    else
    {
        SDL_Delay(frameLimit - ticks);
    }
}


void drawHud(void)
{
    //On cr�e une varuiable qui contiendra notre texte (jusqu'� 200 caract�res, y'a de la marge ;) ).
    char text[200];

    /* Affiche le nombre de vies en bas � droite */
    drawImage(jeu.HUD_vie, 480, 410);
    //Pour afficher le nombre de vies, on formate notre string pour qu'il prenne la valeur de la variable
    sprintf(text, "%d", jeu.vies);
    //Puis on utilise notre fonction cr��e pr�c�demment
    drawString(text, 560, 420, font);

    /* Affiche le nombre d'�toiles en haut � gauche */
    drawImage(jeu.HUD_etoiles, 60, 60);
    sprintf(text, "%d", jeu.etoiles);
    drawString(text, 100, 57, font);

}


