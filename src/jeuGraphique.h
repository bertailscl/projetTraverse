#ifndef JEUGRAPHIQUE_H
#define JEUGRAPHIQUE_H
#include "lib/sdl/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/sdl_image/SDL_image.h"

#include "affichage.h"
#include "deplacement.h"
#include "jeuTerminal.h"
#include "conditionVictoire.h"
#include "ia.h"

#ifndef STRUCT_TEXTURES
#define STRUCT_TEXTURES
typedef struct textu {
    SDL_Texture *plateau;
    SDL_Texture *coupPossible;
    SDL_Texture *selection;
    SDL_Texture *J1carre;
    SDL_Texture *J1triangle;
    SDL_Texture *J1losange;
    SDL_Texture *J1rond;
    SDL_Texture *J2carre;
    SDL_Texture *J2triangle;
    SDL_Texture *J2losange;
    SDL_Texture *J2rond;
    SDL_Texture *J1victoire;
    SDL_Texture *J2victoire;
    SDL_Texture *Jvictoire;
    SDL_Texture *Jdefaite;
    SDL_Texture *J1panel;
    SDL_Texture *J2panel;
    SDL_Texture *Jpanel;
    SDL_Texture *Ordipanel;
} textures;
#endif


#ifndef STRUCT_COORD
#define STRUCT_COORD
typedef struct coord
{
  int i;
  int j;
}coord;
#endif // STRUCT_COORD

#ifndef STRUCT_EMPLA
#define STRUCT_EMPLA
typedef struct empla
{
  coord pion;
  coord emplacement;
}empla;
#endif // STRUCT_EMPLA

void jeuGraphique(void);

void tourJoueurGraphique(int **grille, int joueur, SDL_Window *window, SDL_Renderer *renderer, textures texture);

empla saisieEmplacementGraphique(int **grille, int joueur, SDL_Window *window, SDL_Renderer *renderer, textures texture);

coord recupererClick(void);

void jeuGraphiqueIA1(void);

void jeuGraphiqueIA2(void);

#endif // JEUGRAPHIQUE_H