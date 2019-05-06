#include "save.h"

void sauvegarde (char fich[20],jeu *game)
{
	int i;
	FILE *f;
	
	f=fopen(fich,"wb");

	
	fwrite(&(game->p1),sizeof(perso),1,f);
	fwrite(&(game->B1),sizeof(Background),1,f);
	fwrite(&(game->p2),sizeof(perso),1,f);
	fwrite(&(game->B2),sizeof(Background),1,f);
	fwrite(&(game->s1),sizeof(score),1,f);
	fwrite(&(game->v1),sizeof(vie),1,f);
	fwrite(&(game->s2),sizeof(score),1,f);
	fwrite(&(game->v2),sizeof(vie),1,f);
	

	
	fclose(f);
	
}

void lire (char fich[20],jeu *game)
{
	int i;
	FILE *f;
	
	f=fopen(fich,"rb");
	if (f==NULL)
	{
	   
		printf("erreur, fichier ne peut pas etre ouvert\n");
		exit(0);

		
	}
	
	else
	{
		
		
	fread(&(game->p1),sizeof(perso),1,f);
	fread(&(game->B1),sizeof(Background),1,f);
	fread(&(game->p2),sizeof(perso),1,f);
	fread(&(game->B2),sizeof(Background),1,f);
	fread(&(game->v1),sizeof(vie),1,f);
	fread(&(game->s1),sizeof(score),1,f);
	fread(&(game->s2),sizeof(score),1,f);
	fread(&(game->v2),sizeof(vie),1,f);
	
	}
	
	fclose(f);
}
