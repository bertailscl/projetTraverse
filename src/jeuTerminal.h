#ifndef JEUTERMINAL_H
#define JEUTERMINAL_H
#include "lib/sdl/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/sdl_image/SDL_image.h"

#include "affichage.h"
#include "jeuGraphique.h"
#include "deplacement.h"
#include "conditionVictoire.h"
#include "ia.h"

#ifndef STRUCT_COORD
#define STRUCT_COORD
typedef struct coord
{
  int i;
  int j;
}coord;
#endif

#ifdef linux
#define CLEAR "clear"
#elif _WIN32
#define CLEAR "cls"
#endif

#define TAILLE 10
#define RED "\033[31m"
#define GREEN "\033[32m" 
#define ORANGE "\033[33m"
#define BLUE "\033[34m"
#define RESET "\033[37m"

void jeuTerminal (void);

void tourJoueur(int **grille, int joueur);

int** creationGrille (void);

void affGrille(int ** grille);

void initialiserGrille(int **grille);

void EnleverActionPossibleGrille(int **grille);

coord saisiePion(int **grille, int joueur);

coord saisieEmplacement(int **grille);

int saisieNb(void);

coord selectionPiece(int **grille, int joueur);

void freeInt2(int** tab, int m);

#endif // JEUTERMINAL_H
