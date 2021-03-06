

#include "structs.h"

/* Prototypes des fonctions utilisées */

extern void init(char *);
extern void cleanup(void);
extern void getInput(void);
extern void getInput2(void);
extern void draw(void);
extern void loadGame(void);
extern void delay(unsigned int frameLimit);
extern void updatePlayer();
extern void initializePlayer();
extern void initializePlayer2();
extern void updateMonsters(void);
extern void drawStartMenu(SDL_Surface *screen, int *sound, int *fullscreen);
extern void updateStartMenu(void);
extern void drawImage(SDL_Surface *image, int x, int y);
extern void drawPauseMenu(SDL_Surface *screen, int *sound, int *fullscreen);
extern void updatePauseMenu(void);
extern void drawMap(int);
extern void drawAnimatedEntity(GameObject *entity);
extern void drawHud(void);
extern void doFireballs(void);
extern void drawFireballs(void);
extern void doPlateforme(void);
extern void drawPlateforme(void);



/* Déclaration des structures globales utilisées par le jeu */

Input input,input2;
Gestion jeu;
Map map;
GameObject player;
GameObject player2;
GameObject monster[MONSTRES_MAX];
GameObject shuriken[10];
GameObject plateforme[50];
/* Déclaration de notre police de caractères */
TTF_Font *font;

