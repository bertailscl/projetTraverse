#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "lib/sdl/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/sdl_image/SDL_image.h"

//#include "jeuGraphique.h"
#include "deplacement.h"
#include "jeuTerminal.h"
#include "conditionVictoire.h"
#include "ia.h"

// Fenetre
#define LARGEUR 900
#define HAUTEUR 650
#define LARGEUR_PIECE 65
#define HAUTEUR_PIECE 65
#define MODE_FENETRE 0

// Textes
#define NOM_JEU "Jeu de Traverse"

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


// Exit/destruction
void SDL_ExitErreur(const char* message);

void destructionTout(SDL_Window *window, SDL_Renderer *renderer, textures texture);


// Fenetre
SDL_Window* creationFenetre (SDL_Window *window);


// Rendu
SDL_Renderer* creationRendu(SDL_Window *window, SDL_Renderer *renderer);


// Textures
//SDL_Texture* creationTextureBMP(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, char* chemin);

SDL_Texture* creationTexture(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, textures allTextures, char* chemin);

    // Centre l'image si coord < 0
void afficherTexture(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, textures allTextures, int x, int y);

void afficherGrille(SDL_Window *window, SDL_Renderer *renderer, textures texture, int **grille, int joueur);

void afficherGrilleIA(SDL_Window *window, SDL_Renderer *renderer, textures texture, int **grille, int joueur);

textures chargerTextures(SDL_Window *window, SDL_Renderer *renderer, textures texture);

#endif