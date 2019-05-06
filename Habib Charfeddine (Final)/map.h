
#include "structs.h"

/* Prototypes des fonctions utilisées */
extern void drawImage(SDL_Surface *, int, int);
extern void drawTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy);
extern void initializeMonster(int x, int y);
extern void getItem(int itemNumber);
extern void getItem2(int itemNumber);
extern void playSoundFx(int type);
extern SDL_Surface *loadImage(char *name);
extern void changeLevel(void);
extern void initializePlayer(void);
extern void initPlateforme(int x, int y, int type);
extern void ShowEnigme(void);


extern Gestion jeu;
extern Map map;
extern GameObject plateforme[];

