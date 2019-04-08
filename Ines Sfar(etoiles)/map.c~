
#include "map.h"

void loadMap(char *name)
{
	int x, y;
	FILE *fp;

	fp = fopen(name, "rb");

	/* Si on ne peut pas ouvrir le fichier, on quitte */
	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);
		exit(1);
	}

	/* Lit les données du fichier dans la map */
	map.maxX = map.maxY = 0;

	for (y=0;y<MAX_MAP_Y;y++)
	{
		for (x=0;x<MAX_MAP_X;x++)
		{
			/* On lit le numéro de la tile et on le copie dans notre tableau */
			fscanf(fp, "%d", &map.tile[y][x]);

			/* Permet de déterminer la taille de la map (voir plus bas) */
			if (map.tile[y][x] > 0)
			{
				if (x > map.maxX)
				{
					map.maxX = x;
				}

				if (y > map.maxY)
				{
					map.maxY = y;
				}
			}
		}
	}

	/* maxX et maxY sont les coordonnées de fin de la map.
	On les trouve dès qu'il n'y a plus que des zéros à la suite.
	Comme ça, on peut faire des maps de tailles différentes avec la même
	structure de fichier. */
	map.maxX = (map.maxX + 1) * TILE_SIZE;
	map.maxY = (map.maxY + 1) * TILE_SIZE;

	/* Remet à 0 les coordonnées de départ de la map */
	map.startX = map.startY = 0;

	/* Et on referme le fichier */
	fclose(fp);

}




void drawMap(void)
{
	int x, y, mapX, x1, x2, mapY, y1, y2, xsource, ysource, a;

	/* On initialise mapX à la 1ère colonne qu'on doit blitter.
	Celle-ci correspond au x de la map (en pixels) divisés par la taille d'une tile (32)
    pour obtenir la bonne colonne de notre map
    Exemple : si x du début de la map = 1026, on fait 1026 / 32
    et on sait qu'on doit commencer par afficher la 32eme colonne de tiles de notre map */
	mapX = map.startX / TILE_SIZE;

	/* Coordonnées de départ pour l'affichage de la map : permet
	de déterminer à quels coordonnées blitter la 1ère colonne de tiles au pixel près
	(par exemple, si la 1ère colonne n'est visible qu'en partie, on devra commencer à blitter
	hors écran, donc avoir des coordonnées négatives - d'où le -1). */
	x1 = (map.startX % TILE_SIZE) * -1;

	/* Calcul des coordonnées de la fin de la map : jusqu'où doit-on blitter ?
	Logiquement, on doit aller à x1 (départ) + SCREEN_WIDTH (la largeur de l'écran).
	Mais si on a commencé à blitter en dehors de l'écran la première colonne, il
	va falloir rajouter une autre colonne de tiles sinon on va avoir des pixels
	blancs. C'est ce que fait : x1 == 0 ? 0 : TILE_SIZE qu'on pourrait traduire par:
	if(x1 != 0)
        x2 = x1 + SCREEN_WIDTH + TILE_SIZE , mais forcément, c'est plus long ;)*/
	x2 = x1 + SCREEN_WIDTH + (x1 == 0 ? 0 : TILE_SIZE);

    /* On fait exactement pareil pour calculer y */
	mapY = map.startY / TILE_SIZE;
	y1 = (map.startY % TILE_SIZE) * -1;
	y2 = y1 + SCREEN_HEIGHT + (y1 == 0 ? 0 : TILE_SIZE);


    //On met en place un timer pour animer la map (chapitre 19)
    if(map.mapTimer <= 0)
    {
        if(map.tileSetNumber == 0)
        {
            map.tileSetNumber = 1;
            map.mapTimer = TIME_BETWEEN_2_FRAMES*3;
        }
        else
        {
            map.tileSetNumber = 0;
            map.mapTimer = TIME_BETWEEN_2_FRAMES*3;
        }

    }
    else
        map.mapTimer--;


	/* Dessine la carte en commençant par startX et startY */

    /* On dessine ligne par ligne en commençant par y1 (0) jusqu'à y2 (480)
    A chaque fois, on rajoute TILE_SIZE (donc 32), car on descend d'une ligne
    de tile (qui fait 32 pixels de hauteur) */
	for (y = y1; y < y2; y += TILE_SIZE)
	{
		/* A chaque début de ligne, on réinitialise mapX qui contient la colonne
		(0 au début puisqu'on ne scrolle pas) */
		mapX = map.startX / TILE_SIZE;

        /* A chaque colonne de tile, on dessine la bonne tile en allant
        de x = 0 à x = 640 */
		for (x = x1; x < x2; x += TILE_SIZE)
		{
		    //Si la tile à dessiner n'est pas une tile vide
		    if (map.tile[mapY][mapX] != 0)
            {
                /*On teste si c'est une tile monstre (tile numéro 10) */
                if (map.tile[mapY][mapX] == 10)
                {

                    //Et on efface cette tile de notre tableau pour éviter un spawn de monstres
                    //infini !
                    map.tile[mapY][mapX] = 0;
                }
            }

            /* Suivant le numéro de notre tile, on découpe le tileset (a = le numéro
            de la tile */
            a = map.tile[mapY][mapX];

            /* Calcul pour obtenir son y (pour un tileset de 10 tiles
            par ligne, d'où le 10 */
            ysource = a / 10 * TILE_SIZE;
            /* Et son x */
            xsource = a % 10 * TILE_SIZE;

            /* Fonction qui blitte la bonne tile au bon endroit suivant le timer */
            if(map.tileSetNumber == 0)
                drawTile(map.tileSet, x, y, xsource, ysource);
            else
                drawTile(map.tileSetB, x, y, xsource, ysource);

            mapX++;
		}

		mapY++;
	}
}


void changeLevel(void)
{

    char file[200];

	/* Charge la map depuis le fichier */
    sprintf(file, "map/map%d.txt", jeu.level );
    loadMap(file);

    //Charge le tileset
    if(map.tileSet != NULL)
    {
        SDL_FreeSurface(map.tileSet);
    }
    if(map.tileSetB != NULL)
    {
        SDL_FreeSurface(map.tileSetB);
    }
    sprintf(file, "graphics/tileset%d.png", jeu.level );
    map.tileSet = loadImage(file);
    sprintf(file, "graphics/tileset%dB.png", jeu.level );
    map.tileSetB = loadImage(file);

}




