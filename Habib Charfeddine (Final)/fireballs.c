/**
* @file fireballs.c
* @brief FIREBALLS
* @author lil peeps
* FIREBALLS RELEASED BY THE CHARACTER
*/

#include "fireballs.h"


void createFireBall(void)
{
    /* Si on peut créer une boule de feu, on la crée */
    if (jeu.nombreFireballs < FIREBALLS_MAX)
    {
        //On enregistre la taille de l'image
        //(pour que vous puissiez la changer sans souci ;) )
        shuriken[jeu.nombreFireballs].w = jeu.Shuriken_image->w;
        shuriken[jeu.nombreFireballs].h = jeu.Shuriken_image->h;

        /* Direction de la boule de feu
        Les valeurs sont proportionnelles au perso - à adpater
        manuellement selon les cas :) */
        if ( player.direction == RIGHT )
            {
                shuriken[jeu.nombreFireballs].x = player.x + 15;
                shuriken[jeu.nombreFireballs].y = player.y + 35;
                shuriken[jeu.nombreFireballs].direction = 1;
            }
        else
            {
                shuriken[jeu.nombreFireballs].x = player.x - 15;
                shuriken[jeu.nombreFireballs].y = player.y + 35;
                shuriken[jeu.nombreFireballs].direction = 0;
            }
        jeu.nombreFireballs++;
    }

}
void createFireBall2(void)
{
    /* Si on peut créer une boule de feu, on la crée */
    if (jeu.nombreFireballs < FIREBALLS_MAX)
    {
        //On enregistre la taille de l'image
        //(pour que vous puissiez la changer sans souci ;) )
        shuriken[jeu.nombreFireballs].w = jeu.Shuriken_image->w;
        shuriken[jeu.nombreFireballs].h = jeu.Shuriken_image->h;

        /* Direction de la boule de feu
        Les valeurs sont proportionnelles au perso - à adpater
        manuellement selon les cas :) */
        if ( player2.direction == RIGHT )
            {
                shuriken[jeu.nombreFireballs].x = player2.x + 15;
                shuriken[jeu.nombreFireballs].y = player2.y + 35;
                shuriken[jeu.nombreFireballs].direction = 1;
            }
        else
            {
                shuriken[jeu.nombreFireballs].x = player2.x - 15;
                shuriken[jeu.nombreFireballs].y = player2.y + 35;
                shuriken[jeu.nombreFireballs].direction = 0;
            }
        jeu.nombreFireballs++;
    }

}


void doFireballs(void)
{
    int i;

    //On passe en boucle toutes les boules de feu ;)
    for ( i = 0; i < jeu.nombreFireballs; i++ )
    {
        /* On se déplace : vers la droite :  */
        if (shuriken[i].direction == 1)
        {
            shuriken[i].x += 10;
        }
        /* - vers la gauche : */
        else
        {
            shuriken[i].x -= 10;
        }


        /* Si elle sort de l'écran, on supprime la boule de feu */
        if ( shuriken[i].x < map.startX ||
             shuriken[i].x > map.startX + SCREEN_WIDTH
            )
        {
             shuriken[i] = shuriken[jeu.nombreFireballs-1];
             jeu.nombreFireballs--;
        }

    }

}


void drawFireballs(void)
{

    int i;

    //On affiche toutes les boules de feu
    for ( i = 0; i < jeu.nombreFireballs; i++ )
    {
        drawImage(jeu.Shuriken_image, shuriken[i].x - map.startX, shuriken[i].y - map.startY);
    }

}

