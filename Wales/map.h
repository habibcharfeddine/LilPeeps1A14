
#include "structs.h"

/* Prototypes des fonctions utilisées */
extern void drawImage(SDL_Surface *, int, int);
extern void drawTile(SDL_Surface *image, int destx, int desty, int srcx, int srcy);
extern void initializeMonster(int x, int y);
extern void getItem(void);
extern void playSoundFx(int type);
extern SDL_Surface *loadImage(char *name);
extern void changeLevel(void);
extern void initializePlayer(void);


extern Gestion jeu;
extern Map map;
