
#include "player.h"


void initializePlayer(void)
{

    /* Charge le sprite de notre héros */
    player.sprite = loadImage("graphics/walkright.png");

    //Indique l'état et la direction de notre héros
    player.direction = RIGHT;
    player.etat = WALK;

    //Réinitialise le timer de l'animation et la frame
    player.frameNumber = 0;
    player.frameTimer = TIME_BETWEEN_2_FRAMES;

    /* Coordonnées de démarrage de notre héros */
    player.x = 0;
    player.y = 0;

    /* Hauteur et largeur de notre héros */
    player.w = PLAYER_WIDTH;
    player.h = PLAYER_HEIGTH;

    //Variables nécessaires au fonctionnement de la gestion des collisions
    player.timerMort = 0;
    player.onGround = 0;

}


void drawplayer()
{
    /* Rectangle de destination à blitter */
	SDL_Rect dest;

    // On soustrait des coordonnées de notre héros, ceux du début de la map, pour qu'il colle
    //au scrolling :
	dest.x = player.x - map.startX;
	dest.y = player.y - map.startY;
	dest.w = PLAYER_WIDTH;
	dest.h = PLAYER_HEIGTH;

	/* Rectangle source à blitter */
	SDL_Rect src;

    //Pour connaître le X de la bonne frame à blitter, il suffit de multiplier
    //la largeur du sprite par le numéro de la frame à afficher -> 0 = 0; 1 = 40; 2 = 80...
	src.x = player.frameNumber * PLAYER_WIDTH;
	src.y = 0;
	src.w = PLAYER_WIDTH;
	src.h = PLAYER_HEIGTH;

	/* Blitte notre héros sur l'écran aux coordonnées x et y */

	SDL_BlitSurface(player.sprite, &src, jeu.screen, &dest);

}


void updatePlayer(void)
{

   //On rajoute un timer au cas où notre héros mourrait lamentablement en tombant dans un trou...
   //Si le timer vaut 0, c'est que tout va bien, sinon, on le décrémente jusqu'à 0, et là,
   //on réinitialise.
   //C'est pour ça qu'on ne gère le joueur que si ce timer vaut 0.
  if (player.timerMort == 0)
  {

    //On réinitialise notre vecteur de déplacement latéral (X), pour éviter que le perso
    //ne fonce de plus en plus vite pour atteindre la vitesse de la lumière ! ;)
    //Essayez de le désactiver pour voir !
	player.dirX = 0;

    // La gravité fait toujours tomber le perso : on incrémente donc le vecteur Y
	player.dirY += GRAVITY_SPEED;

    //Mais on le limite pour ne pas que le joueur se mette à tomber trop vite quand même
	if (player.dirY >= MAX_FALL_SPEED)
	{
		player.dirY = MAX_FALL_SPEED;
	}

    //Voilà, au lieu de changer directement les coordonnées du joueur, on passe par un vecteur
    //qui sera utilisé par la fonction mapCollision(), qui regardera si on peut ou pas déplacer
    //le joueur selon ce vecteur et changera les coordonnées du player en fonction.
 	if (input.left == 1)
	{
		player.dirX -= PLAYER_SPEED;

        //On teste le sens pour l'animation : si le joueur allait dans le sens contraire
        //précédemment, il faut recharger le spritesheet pour l'animation.
		if(player.direction == RIGHT)
		{
		    player.direction = LEFT;
		    player.sprite = loadImage("graphics/walkleft.png");
		}
	}

	else if (input.right == 1)
	{
		player.dirX += PLAYER_SPEED;

		if(player.direction == LEFT)
		{
		    player.direction =  RIGHT;
		    player.sprite = loadImage("graphics/walkright.png");
		}

    }

    //Et voici la fonction de saut très simple :
    //Si on appuie sur la touche saut et qu'on est sur le sol, alors on attribue une valeur
    //négative au vecteur Y
    //parce que sauter veut dire se rapprocher du haut de l'écran et donc de y=0.
    if (input.jump == 1 && player.onGround)
	{
		player.dirY = -JUMP_HEIGHT;
		player.onGround = 0;

	}

    //On rajoute notre fonction de détection des collisions qui va mettre à jour les coordonnées
    //de notre super lapin, puis on centre le scrolling comme avant.
    mapCollision(&player);
    centerScrollingOnPlayer();

  }

    //Gestion de la mort quand le héros tombe dans un trou :
    //Si timerMort est différent de 0, c'est qu'il faut réinitialiser le joueur.
    //On ignore alors ce qui précède et on joue cette boucle (un wait en fait) jusqu'à ce que
    // timerMort == 1. A ce moment-là, on le décrémente encore -> il vaut 0 et on réinitialise
    //le jeu avec notre bonne vieille fonction d'initialisation ;) !
    if (player.timerMort > 0)
	{
		player.timerMort--;

		if (player.timerMort == 0)
		{
			/* Si on est mort */
			initializePlayer();
		}
	}

}


void centerScrollingOnPlayer(void)
{
	//On définit les coordonnées du début de l'affichage de la map par rapport à celles
	//du joueur.
	//Pour centrer le joueur, la map doit donc s'afficher à un demi-écran avant la position
	//du joueur.
	//Puis on "clamp" (limite) l'affichage de l'écran pour ne pas sortir de la map.
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




