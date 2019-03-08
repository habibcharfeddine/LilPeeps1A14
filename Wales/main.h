

#include "structs.h"

/* Prototypes des fonctions utilisées */

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern void draw(void);
extern void loadGame(void);
extern void delay(unsigned int frameLimit);
extern void updatePlayer(void);
extern void initializePlayer(void);
extern void updateMonsters(void);
extern void drawStartMenu(SDL_Surface *screen, int *sound, int *fullscreen);
extern void updateStartMenu(void);
extern void drawImage(SDL_Surface *image, int x, int y);
extern void drawPauseMenu(SDL_Surface *screen, int *sound, int *fullscreen);
extern void updatePauseMenu(void);



/* Déclaration des structures globales utilisées par le jeu */

Input input;
Gestion jeu;
Map map;
GameObject player;
GameObject monster[MONSTRES_MAX];
/* Déclaration de notre police de caractères */
TTF_Font *font;

