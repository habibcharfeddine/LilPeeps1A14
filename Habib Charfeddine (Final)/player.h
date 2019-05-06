
#include "structs.h"

extern Gestion jeu;
extern GameObject player;
extern GameObject player2;
extern Input input,input2;
extern Map map;

/* Prototypes des fonctions utilisées */
extern SDL_Surface *loadImage(char *name);
extern void centerScrollingOnPlayer(void);
extern void mapCollision(GameObject *entity);
extern void mapCollision2(GameObject *entity);
extern void loadMap(char *name);
extern void changeAnimation(GameObject *entity, char *name);
extern void playSoundFx(int type);
extern void changeLevel(void);
extern void createFireBall(void);
