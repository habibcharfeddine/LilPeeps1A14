

#include "structs.h"

/* Prototypes des fonctions utilis�es */

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



/* D�claration des structures globales utilis�es par le jeu */

Input input;
Gestion jeu;
Map map;
GameObject player;
GameObject monster[MONSTRES_MAX];
/* D�claration de notre police de caract�res */
TTF_Font *font;

