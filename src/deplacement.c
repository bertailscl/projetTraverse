#include "deplacement.h"
#include "jeuTerminal.h"

void deplacementPossible(int **grille, coord pion)
{
  int choix = grille[pion.i][pion.j]; // choix de la pièce a dépalcer
  switch (choix)
  {
  case 1:
    positionActionsPossiblesCarre(grille, pion.i, pion.j, 0);
    break;
  case 2:
    positionActionsPossiblesTriangleJ1(grille, pion.i, pion.j, 0);
    break;
  case 3:
    positionActionsPossiblesLosange(grille, pion.i, pion.j, 0);
    break;
  case 4:
    positionActionsPossiblesRond(grille, pion.i, pion.j, 0);
    break;
  case 5:
    positionActionsPossiblesCarre(grille, pion.i, pion.j, 0);
    break;
  case 6:
    positionActionsPossiblesTriangleJ2(grille, pion.i, pion.j, 0);
    break;
  case 7:
    positionActionsPossiblesLosange(grille, pion.i, pion.j, 0);
    break;
  case 8:
    positionActionsPossiblesRond(grille, pion.i, pion.j, 0);
    break;
  default:
    exit(EXIT_FAILURE);
    break;
  }
}

void positionActionsPossiblesCarre(int **grille, int i, int j, int saut)
{ // possibilité : grille[i][j++], grille[i++][j], grille[i--][j], grille[i][j--] + tout les sauts
  if (j < 8)
  {
    verifCasActionCarre(grille, i, j+1, 1, saut); // cas 1
  }
  if (i < 9)
  {
    verifCasActionCarre(grille, i+1, j, 2, saut); // cas 2
  }
  
  if (i > 0)
  {
    verifCasActionCarre(grille, i-1, j, 3, saut); // cas 3
  }
  if (j > 1)
  {
    verifCasActionCarre(grille, i, j-1, 4, saut); // cas 4
  }
}

void verifCasActionCarre(int **grille, int i, int j, int cas, int saut)
{
  if (grille[i][j] == 0 && saut != 1) // pas d'autre pion sur la case verifiee
  {
    grille[i][j] = 9; // marquer le deplacement possible
  }
  else if (grille[i][j] != 0 && grille[i][j] != 9)
  {
    switch (cas)
    {
    case 1:
      if (j+1 < 10)
      {
        verifSautCarre(grille, i, j+1); // verifier tout les sauts depuis ce point
      }
      break;
    case 2:
      if (i+1 < 10) // verifier que le coup n est pas hors plateforme
      {
        verifSautCarre(grille, i+1, j); // verifier tout les sauts depuis ce point
      }
      break;
    case 3:
      if (i-1 > -1)
      {
        verifSautCarre(grille, i-1, j); // verifier tout les sauts depuis ce point
      }
      break;
    case 4:
      if (j-1 > -1)
      {
        verifSautCarre(grille, i, j-1); // verifier tout les sauts depuis ce point
      }
      break;
    default:
      exit(EXIT_FAILURE);
      break;
    }
  }
}

void verifSautCarre(int **grille, int i, int j)
{
  if (grille[i][j] == 0 && (j == 0 || j == 9)) // on est sur un bord libre (impossible de rester dessus)
  {
    positionActionsPossiblesCarre(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
  else if (grille[i][j] == 0)
  {
    grille[i][j] = 9; // marque le deplacement possible
    positionActionsPossiblesCarre(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
}

void positionActionsPossiblesTriangleJ1(int **grille, int i, int j, int saut)
{
  if (i < 9 && j < 8)
  {
    verifCasActionTriangleJ1(grille, i+1, j+1, 1, saut); // cas 1
  }
  if (i < 9 && j > 1)
  {
    verifCasActionTriangleJ1(grille, i+1, j-1, 2, saut); // cas 2
  }
  
  if (i > 0)
  {
    verifCasActionTriangleJ1(grille, i-1, j, 3, saut); // cas 3
  }
}

void verifCasActionTriangleJ1(int **grille, int i, int j, int cas, int saut)
{
  if (grille[i][j] == 0 && saut != 1) // pas d'autre pion sur la case verifiee
  {
    grille[i][j] = 9; // marquer le deplacement possible
  }
  else if (grille[i][j] != 0 && grille[i][j] != 9)
  {
    switch (cas)
    {
    case 1:
      if (i+1 < 10 && j+1 < 10)
      {
        verifSautTriangleJ1(grille, i+1, j+1); // verifier tout les sauts depuis ce point
      }
      break;
    case 2:
      if (i+1 < 10 && j-1 > -1)
      {
        verifSautTriangleJ1(grille, i+1, j-1); // verifier tout les sauts depuis ce point
      }
      break;
    case 3:
      if (i-1 > -1)
      {
        verifSautTriangleJ1(grille, i-1, j); // verifier tout les sauts depuis ce point
      }
      break;
    default:
      exit(EXIT_FAILURE);
      break;
    }
  }
}

void verifSautTriangleJ1(int **grille, int i, int j)
{
  if (grille[i][j] == 0 && (j == 0 || j == 9)) // on est sur un bord libre (impossible de rester dessus)
  {
    positionActionsPossiblesTriangleJ1(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
  else if (grille[i][j] == 0)
  {
    grille[i][j] = 9; // marque le deplacement possible
    positionActionsPossiblesTriangleJ1(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
}

void positionActionsPossiblesTriangleJ2(int **grille, int i, int j, int saut)
{
  if (i > 0 && j > 1)
  {
    verifCasActionTriangleJ2(grille, i-1, j-1, 1, saut); // cas 1
  }
  if (i > 0 && j < 8)
  {
    verifCasActionTriangleJ2(grille, i-1, j+1, 2, saut); // cas 2
  }
  if (i < 9)
  {
    verifCasActionTriangleJ2(grille, i+1, j, 3, saut); // cas 3
  }
}

void verifCasActionTriangleJ2(int **grille, int i, int j, int cas, int saut)
{
  if (grille[i][j] == 0 && saut != 1) // pas d'autre pion sur la case verifiee
  {
    grille[i][j] = 9; // marquer le deplacement possible
  }
  else if (grille[i][j] != 0 && grille[i][j] != 9)
  {
    switch (cas)
    {
    case 1:
      if (i-1 > -1 && j-1 > -1)
      {
        verifSautTriangleJ2(grille, i-1, j-1); // verifier tout les sauts depuis ce point
      }
      break;
    case 2:
      if (i-1 > -1 && j+1 < 10)
      {
        verifSautTriangleJ2(grille, i-1, j+1); // verifier tout les sauts depuis ce point
      }
      break;
    case 3:
      if (i+1 < 10)
      {
        verifSautTriangleJ2(grille, i+1, j); // verifier tout les sauts depuis ce point
      }
      break;
    default:
      exit(EXIT_FAILURE);
      break;
    }
  }
}

void verifSautTriangleJ2(int **grille, int i, int j)
{
  if (grille[i][j] == 0 && (j == 0 || j == 9)) // on est sur un bord libre (impossible de rester dessus)
  {
    positionActionsPossiblesTriangleJ2(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
  else if (grille[i][j] == 0)
  {
    grille[i][j] = 9; // marque le deplacement possible
    positionActionsPossiblesTriangleJ2(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
}

void positionActionsPossiblesLosange(int **grille, int i, int j, int saut)
{
  if (i > 0 && j > 1)
  {
    verifCasActionLosange(grille, i-1, j-1, 1, saut); // cas 1
  }
  if (i > 0 && j < 8)
  {
    verifCasActionLosange(grille, i-1, j+1, 2, saut); // cas 2
  }
  
  if (i < 9 && j > 1)
  {
    verifCasActionLosange(grille, i+1, j-1, 3, saut); // cas 3
  }
  if (i < 9 && j < 8)
  {
    verifCasActionLosange(grille, i+1, j+1, 4, saut); // cas 4
  }
}

void verifCasActionLosange(int **grille, int i, int j, int cas, int saut)
{
  if (grille[i][j] == 0 && saut != 1) // pas d'autre pion sur la case verifiee
  {
    grille[i][j] = 9; // marquer le deplacement possible
  }
  else if (grille[i][j] != 0 && grille[i][j] != 9)
  {
    switch (cas)
    {
    case 1:
      if (i-1 > -1 && j-1 > -1)
      {
        verifSautLosange(grille, i-1, j-1); // verifier tout les sauts depuis ce point
      }
      break;
    case 2:
      if (i-1 > -1 && j+1 < 10)
      {
        verifSautLosange(grille, i-1, j+1); // verifier tout les sauts depuis ce point
      }     
      break;
    case 3:
      if (i+1 < 10 && j-1 >-1)
      {
        verifSautLosange(grille, i+1, j-1); // verifier tout les sauts depuis ce point
      }
      break;
    case 4:
      if (i+1 < 10 && j+1 < 10)
      {
        verifSautLosange(grille, i+1, j+1); // verifier tout les sauts depuis ce point
      }
      break;
    default:
      exit(EXIT_FAILURE);
      break;
    }
  }
}

void verifSautLosange(int **grille, int i, int j)
{
  if (grille[i][j] == 0 && (j == 0 || j == 9)) // on est sur un bord libre (impossible de rester dessus)
  {
    positionActionsPossiblesLosange(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
  else if (grille[i][j] == 0)
  {
    grille[i][j] = 9; // marque le deplacement possible
    positionActionsPossiblesLosange(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
}

void positionActionsPossiblesRond(int **grille, int i, int j, int saut)
{ 
  if (i > 0 && j > 1)
  {
    verifCasActionRond(grille, i-1, j-1, 1, saut); // cas 1
  }
  if (i > 0 && j < 8)
  {
    verifCasActionRond(grille, i-1, j+1, 2, saut); // cas 2
  }
  if (i < 9 && j > 1)
  {
    verifCasActionRond(grille, i+1, j-1, 3, saut); // cas 3
  }
  if (i < 9 && j < 8)
  {
    verifCasActionRond(grille, i+1, j+1, 4, saut); // cas 4
  }
  if (j < 8)
  {
    verifCasActionRond(grille, i, j+1, 5, saut); // cas 5
  }
  if (i < 9)
  {
    verifCasActionRond(grille, i+1, j, 6, saut); // cas 6
  }
  
  if (i > 0)
  {
    verifCasActionRond(grille, i-1, j, 7, saut); // cas 7
  }
  if (j > 1)
  {
    verifCasActionRond(grille, i, j-1, 8, saut); // cas 8
  }
}

void verifCasActionRond(int **grille, int i, int j, int cas, int saut)
{
  if (grille[i][j] == 0 && saut != 1) // pas d'autre pion sur la case verifiee
  {
    grille[i][j] = 9; // marquer le deplacement possible
  }
  else if (grille[i][j] != 0 && grille[i][j] != 9)
  {
    switch (cas)
    {
    case 1:
      if (i-1 > -1 && j-1 > -1)
      {
        verifSautRond(grille, i-1, j-1); // verifier tout les sauts depuis ce point
      }
      break;

    case 2:
      if (i-1 > -1 && j+1 < 10)
      {
        verifSautRond(grille, i-1, j+1); // verifier tout les sauts depuis ce point
      }     
      break;

    case 3:
      if (i+1 < 10 && j-1 >-1)
      {
        verifSautRond(grille, i+1, j-1); // verifier tout les sauts depuis ce point
      }
      break;

    case 4:
      if (i+1 < 10 && j+1 < 10)
      {
        verifSautRond(grille, i+1, j+1); // verifier tout les sauts depuis ce point
      }
      break;

    case 5:
      if (j+1 < 10)
      {
        verifSautRond(grille, i, j+1); // verifier tout les sauts depuis ce point
      }
      break;

    case 6:
      if (i+1 < 10) // verifier que le coup n est pas hors plateforme
      {
        verifSautRond(grille, i+1, j); // verifier tout les sauts depuis ce point
      }
      break;

    case 7:
      if (i-1 > -1)
      {
        verifSautRond(grille, i-1, j); // verifier tout les sauts depuis ce point
      }
      break;

    case 8:
      if (j-1 > -1)
      {
        verifSautRond(grille, i, j-1); // verifier tout les sauts depuis ce point
      }
      break;

    default:
      exit(EXIT_FAILURE);
      break;
    }
  }
}

void verifSautRond(int **grille, int i, int j)
{
  if (grille[i][j] == 0 && (j == 0 || j == 9)) // on est sur un bord libre (impossible de rester dessus)
  {
    positionActionsPossiblesRond(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
  else if (grille[i][j] == 0)
  {
    grille[i][j] = 9; // marque le deplacement possible
    positionActionsPossiblesRond(grille, i, j, 1); // on reverifie tout les coter pour voir si un saut est disponible
  }
}

void deplacerPieceGraphique(int **grille, empla coup)
{
  grille[coup.emplacement.i][coup.emplacement.j] = grille[coup.pion.i][coup.pion.j];
  grille[coup.pion.i][coup.pion.j] = 0;
}

void deplacerPiece(int **grille, coord pion, coord emplacement)
{
  grille[emplacement.i][emplacement.j] = grille[pion.i][pion.j];
  grille[pion.i][pion.j] = 0;
}