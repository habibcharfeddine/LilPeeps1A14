
#include "structs.h"

extern Gestion jeu;
extern Hero player;
extern Input input;
extern Map map;

/* Prototypes des fonctions utilisées */
extern SDL_Surface *loadImage(char *name);
extern void centerScrollingOnPlayer(void);
extern void mapCollision(Hero *entity);
