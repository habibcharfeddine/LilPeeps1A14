
#include "animation.h"


void drawanimatedplayer(void)
{
    /* Gestion du timer */
    // Si notre timer (un compte à rebours en fait) arrive à zéro
    if (player.frameTimer <= 0)
    {
        //On le réinitialise
        player.frameTimer = TIME_BETWEEN_2_FRAMES;

        //Et on incrémente notre variable qui compte les frames de 1 pour passer à la suivante
        player.frameNumber++;

        //Mais si on dépasse la frame max, il faut revenir à la première
        //Pour connaître la frame max, il suffit de diviser la longueur du spritesheet
        //par la longueur de notre héros : 480 / 40 = 12 frames
        //Puisque la première frame est la numéro 0, la dernière est donc la numéro 11
        if(player.frameNumber >= player.sprite->w / PLAYER_WIDTH - 1)
            player.frameNumber = 0;

    }
    //Sinon, on décrémente notre timer
    else
        player.frameTimer--;


    //Ensuite, on peut passer la main à notre fonction
    drawplayer();


}


