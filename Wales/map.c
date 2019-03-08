
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
                    //On initialise un monstre en envoyant les coordonnées de la tile
                    initializeMonster(mapX * TILE_SIZE, mapY * TILE_SIZE);
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



void mapCollision(GameObject *entity)
{

	int i, x1, x2, y1, y2;

	/* D'abord, on place le joueur en l'air jusqu'à temps d'être sûr qu'il touche le sol */
	entity->onGround = 0;

	/* Ensuite, on va tester les mouvements horizontaux en premier (axe des X) */
	//On va se servir de i comme compteur pour notre boucle. En fait, on va découper notre sprite
	//en blocs de tiles pour voir quelles tiles il est susceptible de recouvrir.
	//On va donc commencer en donnant la valeur de Tile_Size à i pour qu'il teste la tile où se trouve
	//le x du joueur mais aussi la suivante SAUF dans le cas où notre sprite serait inférieur à
	//la taille d'une tile. Dans ce cas, on lui donnera la vraie valeur de la taille du sprite
	//Et on testera ensuite 2 fois la même tile. Mais comme ça notre code sera opérationnel quelle que
	//soit la taille de nos sprites !

	if(entity->h > TILE_SIZE)
		i = TILE_SIZE;
    else
		i = entity->h;

    //On lance alors une boucle for infinie car on l'interrompra selon les résultats de nos calculs
	for (;;)
	{
		//On va calculer ici les coins de notre sprite à gauche et à droite pour voir quelle tile ils
		//touchent.
		x1 = (entity->x + entity->dirX) / TILE_SIZE;
		x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

        //Même chose avec y, sauf qu'on va monter au fur et à mesure pour tester toute la hauteur
        //de notre sprite, grâce à notre fameuse variable i.
		y1 = (entity->y) / TILE_SIZE;
		y2 = (entity->y + i - 1) / TILE_SIZE;

        //De là, on va tester les mouvements initiés dans updatePlayer grâce aux vecteurs
        //dirX et dirY, tout en testant avant qu'on se situe bien dans les limites de l'écran.
		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			//Si on a un mouvement à droite
			if (entity->dirX > 0)
			{

                //Test de la tile Power-up : Etoile (= tile N°5)
				if (map.tile[y1][x2] == 5)
				{
				    //On appelle la fonction getItem()
				    getItem();

				    //On remplace la tile power-up par une tile transparente
				    map.tile[y1][x2] = 0;
				}
				else if(map.tile[y2][x2] == 5)
				{
				    //On appelle la fonction getItem()
				    getItem();
				    //On remplace la tile power-up par une tile transparente
				    map.tile[y2][x2] = 0;
				}

				//On vérifie si les tiles recouvertes sont solides
				if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
				{
					// Si c'est le cas, on place le joueur aussi près que possible
					// de ces tiles, en mettant à jour ses coordonnées. Enfin, on réinitialise
					//son vecteur déplacement (dirX).

					entity->x = x2 * TILE_SIZE;
					entity->x -= entity->w + 1;
					entity->dirX = 0;

				}

			}

            //Même chose à gauche
			else if (entity->dirX < 0)
			{

				//Test de la tile Power-up : Etoile (= tile N°5)
				if (map.tile[y1][x1] == 5)
				{
				    //On appelle la fonction getItem()
				    getItem();

				    //On remplace la tile power-up par une tile transparente
				    map.tile[y1][x1] = 0;
				}
				else if(map.tile[y2][x1] == 5)
				{
				    //On appelle la fonction getItem()
				    getItem();
				    //On remplace la tile power-up par une tile transparente
				    map.tile[y2][x1] = 0;
				}


				if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
				{
					entity->x = (x1 + 1) * TILE_SIZE;
					entity->dirX = 0;
				}

			}

		}

		//On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
		if (i == entity->h)
		{
			break;
		}

		//Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
		i += TILE_SIZE;

		if (i > entity->h)
		{
			i = entity->h;
		}
	}

	//On recommence la même chose avec le mouvement vertical (axe des Y)
    if(entity->w > TILE_SIZE)
		i = TILE_SIZE;
    else
		i = entity->w;


	for (;;)
	{
		x1 = (entity->x) / TILE_SIZE;
		x2 = (entity->x + i) / TILE_SIZE;

		y1 = (entity->y + entity->dirY) / TILE_SIZE;
		y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (entity->dirY > 0)
			{

				/* Déplacement en bas */

				//Test de la tile Power-up : Etoile (= tile N°5)
				if (map.tile[y2][x1] == 5)
				{
				    //On appelle la fonction getItem()
				    getItem();

				    //On remplace la tile power-up par une tile transparente
				    map.tile[y2][x1] = 0;
				}
				else if(map.tile[y2][x2] == 5)
				{
				    //On appelle la fonction getItem()
				    getItem();
				    //On remplace la tile power-up par une tile transparente
				    map.tile[y2][x2] = 0;
				}


				/* Gestion du ressort */
				if ((map.tile[y2][x1] == 7 ) || (map.tile[y2][x2] == 7 ))
				{
					entity->dirY = -20;
					//On indique au jeu qu'il a atterri pour réinitialiser le double saut
					entity->onGround = 1;
					playSoundFx(BUMPER);
				}


				else if (map.tile[y2][x1] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
				{
                    //Si la tile est solide, on y colle le joueur et
                    //on le déclare sur le sol (onGround).
					entity->y = y2 * TILE_SIZE;
					entity->y -= entity->h;
					entity->dirY = 0;
					entity->onGround = 1;
				}

			}

			else if (entity->dirY < 0)
			{

				/* Déplacement vers le haut */

				//Test de la tile Power-up : Etoile (= tile N°5)
				if (map.tile[y1][x1] == 5)
				{
				    //On appelle la fonction getItem()
				    getItem();

				    //On remplace la tile power-up par une tile transparente
				    map.tile[y1][x1] = 0;
				}
				else if(map.tile[y1][x2] == 5)
				{
				    //On appelle la fonction getItem()
				    getItem();
				    //On remplace la tile power-up par une tile transparente
				    map.tile[y1][x2] = 0;
				}


				if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
				{
					entity->y = (y1 + 1) * TILE_SIZE;
					entity->dirY = 0;
				}

            }
		}

        //On teste la largeur du sprite (même technique que pour la hauteur précédemment)
		if (i == entity->w)
		{
			break;
		}

		i += TILE_SIZE;

		if (i > entity->w)
		{
			i = entity->w;
		}
	}

	/* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
	entity->x += entity->dirX;
	entity->y += entity->dirY;

    //Et on contraint son déplacement aux limites de l'écran, comme avant.
	if (entity->x < 0)
	{
		entity->x = 0;
	}

	else if (entity->x + entity->w >= map.maxX)
	{
	    //Si on touche le bord droit de l'écran, on passe au niveau sup
	    jeu.level++;
	    //Si on dépasse le niveau max, on annule et on limite le déplacement du joueur
		if(jeu.level > LEVEL_MAX)
		{
		    jeu.level = LEVEL_MAX;
		    entity->x = map.maxX - entity->w - 1;
		}
		//Sion, on passe au niveau sup, on charge la nouvelle map et on réinitialise le joueur
		else
		{
		    changeLevel();
		    initializePlayer();
		}

	}

    //Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
    //qui gère sa mort et sa réinitialisation (plus tard on gèrera aussi les vies).
	if (entity->y > map.maxY)
	{
		entity->timerMort = 60;
	}
}


void monsterCollisionToMap(GameObject *entity)
{

	int i, x1, x2, y1, y2;

	entity->onGround = 0;

	if(entity->h > TILE_SIZE)
		i = TILE_SIZE;
    else
		i = entity->h;

	for (;;)
	{
		x1 = (entity->x + entity->dirX) / TILE_SIZE;
		x2 = (entity->x + entity->dirX + entity->w - 1) / TILE_SIZE;

		y1 = (entity->y) / TILE_SIZE;
		y2 = (entity->y + i - 1) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			//Si on a un mouvement à droite
			if (entity->dirX > 0)
			{
				//On vérifie si les tiles recouvertes sont solides
				if (map.tile[y1][x2] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
				{
					entity->x = x2 * TILE_SIZE;
					entity->x -= entity->w + 1;
					entity->dirX = 0;

				}

			}

            //Même chose à gauche
			else if (entity->dirX < 0)
			{

				if (map.tile[y1][x1] > BLANK_TILE || map.tile[y2][x1] > BLANK_TILE)
				{
					entity->x = (x1 + 1) * TILE_SIZE;
					entity->dirX = 0;
				}

			}

		}

		//On sort de la boucle si on a testé toutes les tiles le long de la hauteur du sprite.
		if (i == entity->h)
		{
			break;
		}

		//Sinon, on teste les tiles supérieures en se limitant à la heuteur du sprite.
		i += TILE_SIZE;

		if (i > entity->h)
		{
			i = entity->h;
		}
	}

	//On recommence la même chose avec le mouvement vertical (axe des Y)
    if(entity->w > TILE_SIZE)
		i = TILE_SIZE;
    else
		i = entity->w;


	for (;;)
	{
		x1 = (entity->x) / TILE_SIZE;
		x2 = (entity->x + i) / TILE_SIZE;

		y1 = (entity->y + entity->dirY) / TILE_SIZE;
		y2 = (entity->y + entity->dirY + entity->h) / TILE_SIZE;

		if (x1 >= 0 && x2 < MAX_MAP_X && y1 >= 0 && y2 < MAX_MAP_Y)
		{
			if (entity->dirY > 0)
			{

				/* Déplacement en bas */

				if (map.tile[y2][x1] > BLANK_TILE || map.tile[y2][x2] > BLANK_TILE)
				{
					entity->y = y2 * TILE_SIZE;
					entity->y -= entity->h;
					entity->dirY = 0;
					entity->onGround = 1;
				}

			}

			else if (entity->dirY < 0)
			{

				/* Déplacement vers le haut */

				if (map.tile[y1][x1] > BLANK_TILE || map.tile[y1][x2] > BLANK_TILE)
				{
					entity->y = (y1 + 1) * TILE_SIZE;
					entity->dirY = 0;
				}

            }
		}

        //On teste la largeur du sprite (même technique que pour la hauteur précédemment)
		if (i == entity->w)
		{
			break;
		}

		i += TILE_SIZE;

		if (i > entity->w)
		{
			i = entity->w;
		}
	}

	/* Maintenant, on applique les vecteurs de mouvement si le sprite n'est pas bloqué */
	entity->x += entity->dirX;
	entity->y += entity->dirY;

    //Et on contraint son déplacement aux limites de l'écran, comme avant.
	if (entity->x < 0)
	{
		entity->x = 0;
	}

	else if (entity->x + entity->w >= map.maxX)
	{
	    entity->x = map.maxX - entity->w - 1;
	}

    //Maintenant, s'il sort de l'écran par le bas (chute dans un trou sans fond), on lance le timer
    //qui gère sa mort et sa réinitialisation (plus tard on gèrera aussi les vies).
	if (entity->y > map.maxY)
	{
		entity->timerMort = 60;
	}
}


