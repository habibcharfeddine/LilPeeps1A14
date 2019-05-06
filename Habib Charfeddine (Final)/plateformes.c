/**
* @file plateformes.c
* @brief flying plateformes
* @author lil peeps
* PLATEFORMES ANIMATION AND COLLISION
*/

#include "plateformes.h"


void loadPlateforme(void)
{
    //On charge l'image de la plateforme
    jeu.plateforme = loadImage("graphics/plateforme.png");

	/* Si on ne peut pas, on quitte, et on l'indique en erreur ;) */
	if (jeu.plateforme == NULL)
	{
		printf("Impossible de charger l'image de la plateforme : graphics/plateforme.png/n");
		exit(1);
	}
}


void initPlateforme(int x, int y, int type)
{

    /* On rajoute une plateforme � la liste des plateformes */
    jeu.nombrePlateformes++;

    //S'il y en a trop, on fait une erreur et on quitte
    if (jeu.nombrePlateformes > PLATEFORMES_MAX)
    {
        printf("Trop de plateformes initialisees !\nEnlevez-en ou changez leur nombre max.\n");
		exit(1);
    }

    //On remplit notre structure
    plateforme[jeu.nombrePlateformes].x = plateforme[jeu.nombrePlateformes].beginX = x;
    plateforme[jeu.nombrePlateformes].y = plateforme[jeu.nombrePlateformes].beginY = y;
    plateforme[jeu.nombrePlateformes].w = jeu.plateforme->w;
    plateforme[jeu.nombrePlateformes].h = jeu.plateforme->h;
    plateforme[jeu.nombrePlateformes].type = type;

    //Si elle est du type 2, elle monte, sinon elle va � droite
    if (plateforme[jeu.nombrePlateformes].type == 2)
        plateforme[jeu.nombrePlateformes].direction = UP;
    else
        plateforme[jeu.nombrePlateformes].direction = RIGHT;



}


void doPlateforme(void)
{

    int i;

    for ( i = 1; i <= jeu.nombrePlateformes; i++ )
    {
        /* D�placement UP/DOWN (haut/bas) */
        if (plateforme[i].type == 2)
        {
            if (plateforme[i].direction == UP)
            {
                plateforme[i].y -= PLATEFORM_SPEED;
                 /* Si le joueur est dessus, on le d�place avec
                 pour �viter qu'il ne reste immobile et que la
                 plateforme se barre comme sur certains vieux
                 (mauvais) jeux...*/
                if (plateforme[i].player_dessus == 1)
                    player.y -= PLATEFORM_SPEED;
            }
            else
            {
                plateforme[i].y += PLATEFORM_SPEED;
                 /* Si le joueur est dessus, on le d�place avec */
                if (plateforme[i].player_dessus == 1)
                    player.y += PLATEFORM_SPEED;
            }

            if (plateforme[i].y > plateforme[i].beginY + 5 * TILE_SIZE)
               plateforme[i].direction = UP;


            if (plateforme[i].y < plateforme[i].beginY)
                plateforme[i].direction = DOWN;
        }

        /* D�placement RIGHT/LEFT */
        else
        {
            if (plateforme[i].direction == RIGHT)
            {
                plateforme[i].x += PLATEFORM_SPEED;
                /* Si le joueur est dessus, on le d�place avec */
                if (plateforme[i].player_dessus == 1)
                    player.x += PLATEFORM_SPEED;
            }
            else
            {
                plateforme[i].x -= PLATEFORM_SPEED;
                /* Si le joueur est dessus, on le d�place avec */
                if (plateforme[i].player_dessus == 1)
                    player.x -= PLATEFORM_SPEED;
            }

            //Test : si la plateforme d�passe 5 tiles de longueur,
            //on lui fait faire demi-tour pour ne pas qu'elle
            //fasse toute la map ! :D
            if (plateforme[i].x > plateforme[i].beginX + 5 * TILE_SIZE)
               plateforme[i].direction = LEFT;

            if (plateforme[i].x < plateforme[i].beginX)
                plateforme[i].direction = RIGHT;
        }



    }



}


void drawPlateforme(void)
{

    int i;

    for ( i = 1; i <= jeu.nombrePlateformes; i++ )
    {
        drawImage(jeu.plateforme, plateforme[i].x - map.startX, plateforme[i].y - map.startY);
    }

}






