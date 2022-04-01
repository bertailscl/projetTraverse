#ifndef DEPLACEMENT_H
#define DEPLACEMENT_H
#include "lib/sdl/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/sdl_image/SDL_image.h"

#include "affichage.h"
#include "jeuGraphique.h"
#include "jeuTerminal.h"
#include "conditionVictoire.h"
#include "ia.h"

#ifndef STRUCT_EMPLA
#define STRUCT_EMPLA
typedef struct empla
{
  coord pion;
  coord emplacement;
}empla;
#endif // STRUCT_EMPLA

void deplacementPossible(int **grille, coord pion);

void positionActionsPossiblesCarre(int **grille, int i, int j, int saut);

void verifCasActionCarre(int **grille, int i, int j, int cas, int saut);

void verifSautCarre(int **grille, int i, int j);

void positionActionsPossiblesTriangleJ1(int **grille, int i, int j, int saut);

void verifCasActionTriangleJ1(int **grille, int i, int j, int cas, int saut);

void verifSautTriangleJ1(int **grille, int i, int j);

void positionActionsPossiblesTriangleJ2(int **grille, int i, int j, int saut);

void verifCasActionTriangleJ2(int **grille, int i, int j, int cas, int saut);

void verifSautTriangleJ2(int **grille, int i, int j);

void positionActionsPossiblesLosange(int **grille, int i, int j, int saut);

void verifCasActionLosange(int **grille, int i, int j, int cas, int saut);

void verifSautLosange(int **grille, int i, int j);

void positionActionsPossiblesRond(int **grille, int i, int j, int saut);

void verifCasActionRond(int **grille, int i, int j, int cas, int saut);

void verifSautRond(int **grille, int i, int j);

void deplacerPieceGraphique(int **grille, empla coup);

void deplacerPiece(int **grille, coord pion, coord emplacement);

#endif // DEPLACEMENT_H