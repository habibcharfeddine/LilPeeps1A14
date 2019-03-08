
#include "sounds.h"

void loadSong( char filename[200] )
{

 /* On libère la chanson précédente s'il y en a une */
 if ( jeu.musique != NULL )
 {
    Mix_HaltMusic();
    Mix_FreeMusic(jeu.musique);
 }

 /* On charge la nouvelle chanson */
 jeu.musique = Mix_LoadMUS( filename );
 if (jeu.musique == NULL)
    {
        fprintf(stderr, "Can't read the music \n");
        exit(1);
    }

    /* On active la répétition de la musique à l'infini */
     if(Mix_PlayMusic(jeu.musique, -1)==-1)
     {
        printf("Mix_PlayMusic: %s\n", Mix_GetError());
     }

}

void loadSound(void)
{

 jeu.bumper_sound = Mix_LoadWAV("sounds/bumper.wav");
 if (jeu.bumper_sound == NULL)
    {
        fprintf(stderr, "Can't read the bumper sound FX \n");
        exit(1);
    }
 jeu.destroy_sound = Mix_LoadWAV("sounds/destroy.wav");
 if (jeu.destroy_sound == NULL)
    {
        fprintf(stderr, "Can't read the destroy sound FX \n");
        exit(1);
    }
 jeu.jump_sound = Mix_LoadWAV("sounds/jump.wav");
 if (jeu.jump_sound == NULL)
    {
        fprintf(stderr, "Can't read the jump sound FX \n");
        exit(1);
    }
 jeu.star_sound = Mix_LoadWAV("sounds/star.wav");
 if (jeu.star_sound == NULL)
    {
        fprintf(stderr, "Can't read the star sound FX \n");
        exit(1);
    }

}


void freeSound(void)
{

 Mix_FreeChunk(jeu.bumper_sound);
 Mix_FreeChunk(jeu.destroy_sound);
 Mix_FreeChunk(jeu.jump_sound);
 Mix_FreeChunk(jeu.star_sound);

}


void playSoundFx(int type)
{

    switch (type)
    {

        case BUMPER:
            Mix_PlayChannel(-1, jeu.bumper_sound, 0);
        break;

        case DESTROY:
            Mix_PlayChannel(-1, jeu.destroy_sound, 0);
        break;

        case JUMP :
            Mix_PlayChannel(-1, jeu.jump_sound, 0);
        break;

        case STAR:
            Mix_PlayChannel(-1, jeu.star_sound, 0);
        break;

   }


}



