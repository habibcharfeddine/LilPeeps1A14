
#include "structs.h"

/* Prototypes des fonctions utilis�es */
extern void drawMap(int);
extern void drawAnimatedEntity(GameObject *entity);
extern void drawHud(void);
extern void drawString(char *text, int x, int y, TTF_Font *font);
extern void drawFireballs(void);
extern void drawPlateforme(void);


/* Structures globales */
extern Gestion jeu;
extern Map map;
extern GameObject player;
extern GameObject player2;
extern GameObject monster[];
extern TTF_Font *font;
