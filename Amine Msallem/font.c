#include "font.h"

TTF_Font *loadFont(char *name, int size)
{
    /* Utilise SDL_TTF pour charger la police à la taille désirée */

    TTF_Font *font = TTF_OpenFont(name, size);

    if (font == NULL)
    {
        printf("Failed to open Font %s: %s\n", name, TTF_GetError());

        exit(1);
    }

    return font;
}


void closeFont(TTF_Font *font)
{
    /* Ferme la police quand on n'en a plus besoin (avant de quitter) */

    if (font != NULL)
    {
        TTF_CloseFont(font);
    }
}


void drawString(char *text, int x, int y, TTF_Font *font)
{
    SDL_Rect dest;
    SDL_Surface *surface;
    SDL_Color foregroundColor;

    /* On choisit d'écrire le texte en noir */
    foregroundColor.r = 0;
    foregroundColor.g = 0;
    foregroundColor.b = 0;


    /* On utilise SDL_TTF pour générer une SDL_Surface à partir d'une chaîne de caractères (string) */

    surface = TTF_RenderUTF8_Blended(font, text, foregroundColor);


    if (surface == NULL)
    {
        printf("Couldn't create String %s: %s\n", text, SDL_GetError());

        return;
    }

    /* On blitte cette SDL_Surface à l'écran */

    dest.x = x;
    dest.y = y;
    dest.w = surface->w;
    dest.h = surface->h;

    SDL_BlitSurface(surface, NULL, jeu.screen, &dest);

    /* On libère la SDL_Surface temporaire (pour éviter les fuites de mémoire - cf. chapitre dédié) */
    SDL_FreeSurface(surface);
}
