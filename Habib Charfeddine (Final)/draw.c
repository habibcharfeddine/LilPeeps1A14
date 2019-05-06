/**
* @file draw.c
* @brief draw
* @author lil peeps
* DRAW HUD CHARACTERS MONSTERS AND TILES NEEDED
*/
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

    /* Affiche la map de tiles : layer 1 */
    drawMap(1);

    /* Affiche le joueur */
    drawAnimatedEntity(&player);
    drawAnimatedEntity(&player2);

    /* Affiche les monstres */
    for(i = 0 ; i < jeu.nombreMonstres ; i++)
    {
        drawAnimatedEntity(&monster[i]);
    }

    //Affiche les plateformes flottantes
    drawPlateforme();

    //Affiche les boules de feu
    drawFireballs();

    /* Affiche la map de tiles : layer 2 */
    drawMap(2);

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
	image = SDL_DisplayFormatAlpha(temp);

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
    //On cr�e une variable qui contiendra notre texte (jusqu'� 200 caract�res, y'a de la marge ;) ).
    char text[200];

    int i;

    //Affiche le nombre de coeurs
    //On cr�e une boucle pour afficher de 1 � 3 coeurs
    //selon la vie, avec un d�calage de 32 pixels
    for( i = 0; i < player2.life; i++)
    {
        // Calcul pour d�couper le tileset comme dans la fonction drawMap()
        int ysource = TILE_POWER_UP_FIN / 10 * TILE_SIZE;
        int xsource = TILE_POWER_UP_FIN % 10 * TILE_SIZE;

        drawTile(map.tileSet, 1000 + i * 32, 20, xsource, ysource);
    }
      for( i = 0; i < player.life; i++)
    {
        // Calcul pour d�couper le tileset comme dans la fonction drawMap()
        int ysource = TILE_POWER_UP_FIN / 10 * TILE_SIZE;
        int xsource = TILE_POWER_UP_FIN % 10 * TILE_SIZE;

        drawTile(map.tileSet, 60 + i * 32, 20, xsource, ysource);
    }


    /* Affiche le nombre de vies en bas � droite */
    drawImage(jeu.HUD_vie, 1120 ,530);
    //Pour afficher le nombre de vies, on formate notre string pour qu'il prenne la valeur de la variable
    sprintf(text, "%d", jeu.vies2);
    //Puis on utilise notre fonction cr��e pr�c�demment
    drawString(text, 1200, 530, font);

/* Affiche le nombre de vies en bas � droite */
    drawImage(jeu.HUD_vie, 60 ,530);
    //Pour afficher le nombre de vies, on formate notre string pour qu'il prenne la valeur de la variable
    sprintf(text, "%d", jeu.vies);
    //Puis on utilise notre fonction cr��e pr�c�demment
    drawString(text, 140, 530, font);

    /* Affiche le nombre d'�toiles en haut � gauche */
    drawImage(jeu.HUD_etoiles, 1040, 60);
    sprintf(text, "%d", jeu.etoiles2);
    drawString(text, 1080, 57, font);
    
	/* Affiche le nombre d'�toiles en haut � gauche */
    drawImage(jeu.HUD_etoiles, 60, 60);
    sprintf(text, "%d", jeu.etoiles);
    drawString(text, 100, 57, font);


}

