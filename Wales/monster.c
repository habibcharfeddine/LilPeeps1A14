
#include "monster.h"


void initializeMonster(int x, int y)
{
    //Si on n'est pas rendu au max, on rajoute un monstre dont le num�ro est �gal
    //� nombreMonstres : monster[0] si c'est le 1er, monster[1], si c'est le 2eme, etc...
    if (jeu.nombreMonstres < MONSTRES_MAX )
	{

        monster[jeu.nombreMonstres].sprite = loadImage("graphics/monster1.png");

        //On r�initialise la frame et le timer
        monster[jeu.nombreMonstres].frameNumber = 0;
        monster[jeu.nombreMonstres].frameTimer = TIME_BETWEEN_2_FRAMES;

        //On indique sa direction (il viendra � l'inverse du joueur, logique)
        monster[jeu.nombreMonstres].direction = LEFT;

        /* Ses coordonn�es de d�marrage seront envoy�es par la fonction drawMap() en arguments */
        monster[jeu.nombreMonstres].x = x;
        monster[jeu.nombreMonstres].y = y;

        /* Hauteur et largeur de notre monstre (une tile ici, soit 32x32) */
        monster[jeu.nombreMonstres].w = TILE_SIZE;
        monster[jeu.nombreMonstres].h = TILE_SIZE;

        //Variables n�cessaires au fonctionnement de la gestion des collisions comme pour le h�ros
        monster[jeu.nombreMonstres].timerMort = 0;
        monster[jeu.nombreMonstres].onGround = 0;

        jeu.nombreMonstres++;

	}

}


void updateMonsters(void)
{

    int i;

    //On passe en boucle tous les monstres du tableau
    for ( i = 0; i < jeu.nombreMonstres; i++ )
    {
        //M�me fonctionnement que pour le joueur
        if (monster[i].timerMort == 0)
        {

            monster[i].dirX = 0;
            monster[i].dirY += GRAVITY_SPEED;

            if (monster[i].dirY >= MAX_FALL_SPEED)
                monster[i].dirY = MAX_FALL_SPEED;

            //Test de collision dans un mur : si la variable x reste la m�me, deux tours de boucle
            //durant, le monstre est bloqu� et on lui fait faire demi-tour.
            if (monster[i].x == monster[i].saveX || checkFall(monster[i]) == 1 )
            {
                if (monster[i].direction == LEFT)
                {
                    monster[i].direction = RIGHT;
                    changeAnimation(&monster[i], "graphics/monster1right.png");
                }
                else
                {
                    monster[i].direction = LEFT;
                    changeAnimation(&monster[i], "graphics/monster1.png");
                }

            }

            //D�placement du joueur selon la direction
            if(monster[i].direction == LEFT)
                monster[i].dirX -= 2;
            else
                monster[i].dirX += 2;


            //On sauvegarde les coordonn�es du joueur pour g�rer le demi-tour
            //avant que mapCollision ne les modifie.
            monster[i].saveX = monster[i].x;

            //On d�tecte les collisions avec la map comme pour le joueur
            monsterCollisionToMap(&monster[i]);


            //On d�tecte les collisions avec le joueur
            //Si c'est �gal � 1, on tue le joueur... Sniff...
            if (collide(&player, &monster[i]) == 1)
            {
                //On met le timer � 1 pour tuer le joueur intantan�ment
                player.timerMort = 1;
                playSoundFx(DESTROY);
            }
            else if (collide(&player, &monster[i]) == 2)
            {
                //On met le timer � 1 pour tuer le monstre intantan�ment
                monster[i].timerMort = 1;
                playSoundFx(DESTROY);
            }


          }

        //Si le monstre meurt, on active une tempo
        if (monster[i].timerMort > 0)
        {
            monster[i].timerMort--;

            /* Et on le remplace simplement par le dernier du tableau puis on
            r�tr�cit le tableau d'une case (on ne peut pas laisser de case vide) */
            if (monster[i].timerMort == 0)
            {
                /* Lib�re le sprite */
                if (monster[i].sprite != NULL)
                {
                    SDL_FreeSurface(monster[i].sprite);
                }
                monster[i] = monster[jeu.nombreMonstres-1];
                jeu.nombreMonstres--;
            }
        }
    }

}


//Fonction de gestion des collisions
int collide(GameObject *player, GameObject *monster)
{
    //On teste pour voir s'il n'y a pas collision, si c'est le cas, on renvoie 0
    if ((player->x >= monster->x + monster->w)
    || (player->x + player->w <= monster->x)
    || (player->y >= monster->y + monster->h)
    || (player->y + player->h <= monster->y)
    )
        return 0;
    //Sinon, il y a collision. Si le joueur est au-dessus du monstre (avec une marge
    //de 10 pixels pour �viter les frustrations dues au pixel perfect), on renvoie 2.
    //On devra alors tuer le monstre et on fera rebondir le joueur.
    else if (player->y + player->h <= monster->y + 10)
    {
        player->dirY = -JUMP_HEIGHT;
        return 2;
    }
    //Sinon, on renvoie 1 et c'est le joueur qui meurt...
    else
        return 1;
}



int checkFall(GameObject monster)
{
    int x, y;

    //Fonction qui teste s'il y a du sol sous un monstre
    //Retourne 1 s'il doit tomber, 0 sinon

    //On teste la direction, pour savoir si on doit prendre en compte x ou x + w (cf. sch�ma)
    if (monster.direction == LEFT)
    {
        //On va � gauche : on calcule l� o� devrait se trouver le monstre apr�s d�placement.
        //S'il sort de la map, on met � jour x et y pour �viter de sortir de notre tableau
        //(source d'erreur possible qui peut planter notre jeu...).
        x = (int)(monster.x + monster.dirX) / TILE_SIZE;
        y = (int)(monster.y + monster.h - 1) /  TILE_SIZE;
        if (y < 0)
            y = 1;
        if (y > MAX_MAP_Y)
            y = MAX_MAP_Y;
        if (x < 0)
            x = 1;
        if (x > MAX_MAP_X)
            x = MAX_MAP_X;

        //On teste si la tile sous le monstre est traversable (du vide quoi...).
        //Si c'est le cas, on renvoie 1, sinon 0.
        if (map.tile[y + 1][x] < BLANK_TILE)
            return 1;

        else
            return 0;
    }
    else
    {
        //M�me chose quand on va � droite
        x = (int)(monster.x + monster.w + monster.dirX) / TILE_SIZE;
        y = (int)(monster.y + monster.h - 1) / TILE_SIZE;
        if (y <= 0)
            y = 1;
        if (y >= MAX_MAP_Y)
            y = MAX_MAP_Y - 1;
        if (x <= 0)
            x = 1;
        if (x >= MAX_MAP_X)
            x = MAX_MAP_X - 1;

        if (map.tile[y + 1][x] < BLANK_TILE)
            return 1;

        else
            return 0;
    }
}





