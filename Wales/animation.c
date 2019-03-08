
#include "animation.h"


void drawAnimatedEntity(GameObject *entity)
{
    /* Gestion du timer */
    // Si notre timer (un compte à rebours en fait) arrive à zéro
    if (entity->frameTimer <= 0)
    {
        //On le réinitialise
        entity->frameTimer = TIME_BETWEEN_2_FRAMES;

        //Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
        entity->frameNumber++;

        //Mais si on dépasse la frame max, il faut revenir à la première
        if(entity->frameNumber >= entity->sprite->w / entity->w)
            entity->frameNumber = 0;

    }
    //Sinon, on décrémente notre timer
    else
        entity->frameTimer--;


    //Ensuite, on peut passer la main à notre fonction

    /* Rectangle de destination à blitter */
	SDL_Rect dest;

    // On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle
    //au scrolling :
	dest.x = entity->x - map.startX;
	dest.y = entity->y - map.startY;
	dest.w = entity->w;
	dest.h = entity->h;

	/* Rectangle source à blitter */
	SDL_Rect src;

    //Pour connaître le X de la bonne frame à blitter, il suffit de multiplier
    //la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80...
	src.x = entity->frameNumber * entity->w;
	src.y = 0;
	src.w = entity->w;
	src.h = entity->h;

	/* Blitte notre héros sur l'écran aux coordonnées x et y */
	SDL_BlitSurface(entity->sprite, &src, jeu.screen, &dest);

}


void changeAnimation(GameObject *entity, char *name)
{
    //On libère l'animation précédente
    if (entity->sprite != NULL)
	{
		SDL_FreeSurface(entity->sprite);
	}
	//On charge la nouvelle
    entity->sprite = loadImage(name);
    //On réinitialise la frame et le timer
    entity->frameNumber = 0;
    entity->frameTimer = TIME_BETWEEN_2_FRAMES;
}

