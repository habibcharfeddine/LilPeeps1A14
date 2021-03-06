
#include "player.h"


void initializePlayer()
{
    //PV � 3
    player.life = 3;

    //Timer d'invincibilit� � 0
    player.invincibleTimer = 0;

    //Nombre de boules de feu / shurikens � 0
    jeu.nombreFireballs = 0;

    //Nombre de plateformes flottantes � 0
    jeu.nombrePlateformes = 0;

    /* Charge le sprite de notre h�ros */
    changeAnimation(&player, "graphics/walkright.png");

    //Indique l'�tat et la direction de notre h�ros
    player.direction = RIGHT;
    player.etat = IDLE;

    /* Coordonn�es de d�marrage/respawn de notre h�ros */
    if(player.checkpointActif == 1)
    {
        player.x = player.respawnX;
        player.y = player.respawnY;
    }
    else
    {
        player.x = 0;
        player.y = 0;
    }


    /* Hauteur et largeur de notre h�ros */
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;

    //Variables n�cessaires au fonctionnement de la gestion des collisions
    player.timerMort = 0;
    player.onGround = 0;

    //Nombre de monstres
    jeu.nombreMonstres = 0;

}
void initializePlayer2()
{
    //PV � 3
    player2.life = 3;

    //Timer d'invincibilit� � 0
    player2.invincibleTimer = 0;

    //Nombre de boules de feu / shurikens � 0
    jeu.nombreFireballs = 0;

    //Nombre de plateformes flottantes � 0
    jeu.nombrePlateformes = 0;

    /* Charge le sprite de notre h�ros */
    changeAnimation(&player2, "graphics/walkright.png");

    //Indique l'�tat et la direction de notre h�ros
    player2.direction = RIGHT;
    player2.etat = IDLE;

    /* Coordonn�es de d�marrage/respawn de notre h�ros */

    if(player.checkpointActif == 1)
    {
        player2.x = player.respawnX;
        player2.y = player.respawnY;
    }
    else
    {
        player2.x = 100;
        player2.y = 0;
    }


    /* Hauteur et largeur de notre h�ros */
    player2.w = PLAYER_WIDTH;
    player2.h = PLAYER_HEIGTH;

    //Variables n�cessaires au fonctionnement de la gestion des collisions
    player2.timerMort = 0;
    player2.onGround = 0;

    //Nombre de monstres
    jeu.nombreMonstres = 0;

}


void updatePlayer()
{

   //On rajoute un timer au cas o� notre h�ros mourrait lamentablement en tombant dans un trou...
   //Si le timer vaut 0, c'est que tout va bien, sinon, on le d�cr�mente jusqu'� 0, et l�,
   //on r�initialise.
   //C'est pour �a qu'on ne g�re le joueur que si ce timer vaut 0.
  if (player.timerMort == 0)
  {
      //On g�re le timer de l'invincibilit�
      if(player.invincibleTimer > 0)
        player.invincibleTimer--;

    //On r�initialise notre vecteur de d�placement lat�ral (X), pour �viter que le perso
    //ne fonce de plus en plus vite pour atteindre la vitesse de la lumi�re ! ;)
    //Essayez de le d�sactiver pour voir !
	player.dirX = 0;

    // La gravit� fait toujours tomber le perso : on incr�mente donc le vecteur Y
	player.dirY += GRAVITY_SPEED;

    //Mais on le limite pour ne pas que le joueur se mette � tomber trop vite quand m�me
	if (player.dirY >= MAX_FALL_SPEED)
	{
		player.dirY = MAX_FALL_SPEED;
	}

    //Voil�, au lieu de changer directement les coordonn�es du joueur, on passe par un vecteur
    //qui sera utilis� par la fonction mapCollision(), qui regardera si on peut ou pas d�placer
    //le joueur selon ce vecteur et changera les coordonn�es du player en fonction.
 	if (input.left == 1)
	{
		player.dirX -= PLAYER_SPEED;
		player.direction = LEFT;

		if(player.etat != WALK_LEFT && player.onGround == 1)
		{
		    player.etat = WALK_LEFT;
		    changeAnimation(&player, "graphics/walkleft.png");
		}
	}

	else if (input.right == 1)

	{
		player.dirX += PLAYER_SPEED;
		player.direction = RIGHT;

		if(player.etat != WALK_RIGHT && player.onGround == 1)
		{
		    player.etat = WALK_RIGHT;
		    changeAnimation(&player, "graphics/walkright.png");
		}
    }

    //Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivit� (Idle)
    else if(input.right == 0 && input.left == 0 && player.onGround == 1)
    {
        //On teste si le joueur n'�tait pas d�j� inactif, pour ne pas recharger l'animation
        //� chaque tour de boucle

        if(player.etat != IDLE)
        {
            player.etat = IDLE;
            //On change l'animation selon la direction
            if(player.direction == LEFT)
            {
		        changeAnimation(&player, "graphics/IdleLeft.png");
            }
            else
            {
		        changeAnimation(&player, "graphics/IdleRight.png");
            }

        }

    }


    //Et voici la fonction de saut tr�s simple :
    //Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur
    //n�gative au vecteur Y
    //parce que sauter veut dire se rapprocher du haut de l'�cran et donc de y=0.
    if (input.jump == 1)
    {
        if(player.onGround == 1)
        {
            player.dirY = -JUMP_HEIGHT;
            player.onGround = 0;
            player.jump = 1;
            playSoundFx(JUMP);
        }
        /* Si on est en saut 1, on peut faire un deuxi�me bond et on remet jump1 � 0 */
        else if (player.jump == 1)
        {
            player.dirY = -JUMP_HEIGHT;
            player.jump = 0;
            playSoundFx(JUMP);
        }
        input.jump = 0;
    }

    if(input.enter == 1)
    {
        //On met le jeu en pause
        jeu.onMenu = 1;
        jeu.menuType = PAUSE;
        input.enter = 0;
    }

    //On g�re le lancer de shurikens
    if(input.attack == 1)
    {
        createFireBall();
        input.attack = 0;
    }


    /* R�active la possibilit� de double saut si on tombe sans sauter */
    if (player.onGround == 1)
		player.jump = 1;


	//On g�re l'anim du saut
	if(player.onGround == 0)
	{
	    if(player.direction == RIGHT && player.etat != JUMP_RIGHT)
        {
            player.etat = JUMP_RIGHT;
            changeAnimation(&player, "graphics/JumpRight.png");
        }
        else if(player.direction == LEFT && player.etat != JUMP_LEFT)
        {
            player.etat = JUMP_LEFT;
            changeAnimation(&player, "graphics/JumpLeft.png");
        }

    }


    //On rajoute notre fonction de d�tection des collisions qui va mettre � jour les coordonn�es
    //de notre super lapin, puis on centre le scrolling comme avant.
    mapCollision(&player);
    centerScrollingOnPlayer();

  }

    //Gestion de la mort quand le h�ros tombe dans un trou :
    //Si timerMort est diff�rent de 0, c'est qu'il faut r�initialiser le joueur.
    //On ignore alors ce qui pr�c�de et on joue cette boucle (un wait en fait) jusqu'� ce que
    // timerMort == 1. A ce moment-l�, on le d�cr�mente encore -> il vaut 0 et on r�initialise
    //le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (player.timerMort > 0)
	{
		player.timerMort--;

		if (player.timerMort == 0)
		{
			/* Si on est mort */
			jeu.vies--;
			if(jeu.vies < 1)
			{

				//On retourne au menu start
                		jeu.onMenu = 1;
                		jeu.menuType = START;
			}
			initializePlayer();
			changeLevel();
		}
	}
}

void updatePlayer2()
{

   //On rajoute un timer au cas o� notre h�ros mourrait lamentablement en tombant dans un trou...
   //Si le timer vaut 0, c'est que tout va bien, sinon, on le d�cr�mente jusqu'� 0, et l�,
   //on r�initialise.
   //C'est pour �a qu'on ne g�re le joueur que si ce timer vaut 0.
  if (player2.timerMort == 0)
  {
      //On g�re le timer de l'invincibilit�
      if(player2.invincibleTimer > 0)
        player2.invincibleTimer--;

    //On r�initialise notre vecteur de d�placement lat�ral (X), pour �viter que le perso
    //ne fonce de plus en plus vite pour atteindre la vitesse de la lumi�re ! ;)
    //Essayez de le d�sactiver pour voir !
	player2.dirX = 0;

    // La gravit� fait toujours tomber le perso : on incr�mente donc le vecteur Y
	player2.dirY += GRAVITY_SPEED;

    //Mais on le limite pour ne pas que le joueur se mette � tomber trop vite quand m�me
	if (player2.dirY >= MAX_FALL_SPEED)
	{
		player2.dirY = MAX_FALL_SPEED;
	}

    //Voil�, au lieu de changer directement les coordonn�es du joueur, on passe par un vecteur
    //qui sera utilis� par la fonction mapCollision(), qui regardera si on peut ou pas d�placer
    //le joueur selon ce vecteur et changera les coordonn�es du player en fonction.
 	if (input2.left == 1)
	{
		player2.dirX -= PLAYER_SPEED;
		player2.direction = LEFT;

		if(player2.etat != WALK_LEFT && player2.onGround == 1)
		{
		    player2.etat = WALK_LEFT;
		    changeAnimation(&player2, "graphics/walkleft.png");
		}
	}

	else if (input2.right == 1)
	{
		player2.dirX += PLAYER_SPEED;
		player2.direction = RIGHT;

		if(player2.etat != WALK_RIGHT && player2.onGround == 1)
		{
		    player2.etat = WALK_RIGHT;
		    changeAnimation(&player2, "graphics/walkright.png");
		}
    }

    //Si on n'appuie sur rien et qu'on est sur le sol, on charge l'animation marquant l'inactivit� (Idle)
    else if(input2.right == 0 && input2.left == 0 && player2.onGround == 1)
    {
        //On teste si le joueur n'�tait pas d�j� inactif, pour ne pas recharger l'animation
        //� chaque tour de boucle

        if(player2.etat != IDLE)
        {
            player2.etat = IDLE;
            //On change l'animation selon la direction
            if(player2.direction == LEFT)
            {
		        changeAnimation(&player2, "graphics/IdleLeft.png");
            }
            else
            {
		        changeAnimation(&player2, "graphics/IdleRight.png");
            }

        }

    }


    //Et voici la fonction de saut tr�s simple :
    //Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur
    //n�gative au vecteur Y
    //parce que sauter veut dire se rapprocher du haut de l'�cran et donc de y=0.
    if (input2.jump == 1)
    {
        if(player2.onGround == 1)
        {
            player2.dirY = -JUMP_HEIGHT;
            player2.onGround = 0;
            player2.jump = 1;
            playSoundFx(JUMP);
        }
        /* Si on est en saut 1, on peut faire un deuxi�me bond et on remet jump1 � 0 */
        else if (player2.jump == 1)
        {
            player2.dirY = -JUMP_HEIGHT;
            player2.jump = 0;
            playSoundFx(JUMP);
        }
        input2.jump = 0;
    }

    if(input2.enter == 1)
    {
        //On met le jeu en pause
        jeu.onMenu = 1;
        jeu.menuType = PAUSE;
        input2.enter = 0;
    }

    //On g�re le lancer de shurikens
    if(input2.attack == 1)
    {
        createFireBall2();
        input2.attack = 0;
    }


    /* R�active la possibilit� de double saut si on tombe sans sauter */
    if (player2.onGround == 1)
		player2.jump = 1;


	//On g�re l'anim du saut
	if(player2.onGround == 0)
	{
	    if(player2.direction == RIGHT && player2.etat != JUMP_RIGHT)
        {
            player2.etat = JUMP_RIGHT;
            changeAnimation(&player2, "graphics/JumpRight.png");
        }
        else if(player2.direction == LEFT && player2.etat != JUMP_LEFT)
        {
            player2.etat = JUMP_LEFT;
            changeAnimation(&player2, "graphics/JumpLeft.png");
        }

    }


    //On rajoute notre fonction de d�tection des collisions qui va mettre � jour les coordonn�es
    //de notre super lapin, puis on centre le scrolling comme avant.
    mapCollision2(&player2);
    //centerScrollingOnPlayer();

  }

    //Gestion de la mort quand le h�ros tombe dans un trou :
    //Si timerMort est diff�rent de 0, c'est qu'il faut r�initialiser le joueur.
    //On ignore alors ce qui pr�c�de et on joue cette boucle (un wait en fait) jusqu'� ce que
    // timerMort == 1. A ce moment-l�, on le d�cr�mente encore -> il vaut 0 et on r�initialise
    //le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (player2.timerMort > 0)
	{
		player2.timerMort--;

		if (player2.timerMort == 0)
		{
			/* Si on est mort */
			jeu.vies2--;
			if(jeu.vies2 < 1)
			{

				//On retourne au menu start
                		jeu.onMenu = 1;
                		jeu.menuType = START;
			}
			initializePlayer2();
			changeLevel();
		}
	}

}


void centerScrollingOnPlayer()
{
	//On d�finit les coordonn�es du d�but de l'affichage de la map par rapport � celles
	//du joueur.
	//Pour centrer le joueur, la map doit donc s'afficher � un demi-�cran avant la position
	//du joueur.
	//Puis on "clamp" (limite) l'affichage de l'�cran pour ne pas sortir de la map.
	map.startX = player.x - (SCREEN_WIDTH / 2);

	if (map.startX < 0)
	{
		map.startX = 0;
	}

	else if (map.startX + SCREEN_WIDTH >= map.maxX)
	{
		map.startX = map.maxX - SCREEN_WIDTH;
	}

	map.startY = player.y - (SCREEN_HEIGHT / 2);

	if (map.startY < 0)
	{
		map.startY = 0;
	}

	else if (map.startY + SCREEN_HEIGHT >= map.maxY)
	{
		map.startY = map.maxY - SCREEN_HEIGHT;
	}
}


void getItem(int itemNumber)
{
    switch(itemNumber)
    {
        //Gestion des �toiles
        case 1:
        //On incr�mente le compteur Etoile
        jeu.etoiles++;
        playSoundFx(STAR);

        //On teste s'il y a 100 �toiles : on remet le compteur � 0 et on rajoute une vie ;)
        if(jeu.etoiles >= 100)
        {
            jeu.etoiles = 0;
            jeu.vies++;
        }
        break;

        //Gestion des coeurs
        case 2:
        //On incr�mente le compteur Etoile
        if(player.life < 3)
            player.life++;

        playSoundFx(STAR);
        break;

        default:
        break;
    }
}
void getItem2(int itemNumber)
{
    switch(itemNumber)
    {
        //Gestion des �toiles
        case 1:
        //On incr�mente le compteur Etoile
        jeu.etoiles2++;
        playSoundFx(STAR);

        //On teste s'il y a 100 �toiles : on remet le compteur � 0 et on rajoute une vie ;)
        if(jeu.etoiles2 >= 100)
        {
            jeu.etoiles2 = 0;
            jeu.vies2++;
        }
        break;

        //Gestion des coeurs
        case 2:
        //On incr�mente le compteur Etoile
        if(player2.life < 3)
            player2.life++;

        playSoundFx(STAR);
        break;

        default:
        break;
    }


}





