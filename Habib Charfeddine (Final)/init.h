
#include "structs.h"

/* Prototypes des fonctions utilis�es */
extern SDL_Surface *loadImage(char *name);
extern void loadMap(char *name);
extern void closeFont(TTF_Font *font);
extern TTF_Font *loadFont(char *, int);
extern void loadSong( char filename[200] );
extern void loadSound(void);
extern void freeSound(void);
extern void changeLevel(void);
extern void loadPlateforme(void);
extern enigme Init_Enigme(enigme e);


extern Gestion jeu;
extern Map map;
extern TTF_Font *font;
extern GameObject player;
extern GameObject player2;
extern GameObject monster[MONSTRES_MAX];

