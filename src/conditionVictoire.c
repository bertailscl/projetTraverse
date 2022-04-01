#include "conditionVictoire.h"

victoire conditionVictoire(int **grille, int tour, int joueur) // verifie si un des joueurs a gagner
{
  victoire cond1 = condition1(grille, tour, joueur);
  victoire cond2 = condition2(grille);
  victoire res;
  res.continuer = 1;
  res.gagner = -1;
  if (cond1.continuer == 0 || cond2.continuer == 0)
  {
    res.continuer = 0;
    if (cond1.gagner == 1 || cond2.gagner == 1)
    {
      res.gagner = 1;
    }
    else if (cond1.gagner == 2 || cond2.gagner == 2)
    {
      res.gagner = 2;
    }
  }
  return res;
}

victoire condition1(int **grille, int tour, int joueur)
{
  victoire res;
  res.gagner = -1;
  res.continuer = 1;
  if (!joueur)
  for (int i = 0; i < 10; i++)    // Verif ligne 0 (gagnant 2)
  {
    if (tour > 30 && grille[0][i] > 0 && grille[0][i] < 5) // Tour > 30 et le pion 1 a pas bouge
    {
      res.gagner = 2;
      res.continuer = 0;
    }
  }
  if (joueur)
  {
    for (int i = 0; i < 10; i++)    // Verif ligne 9 (gagnant 1)
    {
      if (tour > 30 && grille[9][i] > 4 && grille[9][i] < 9)
      {
        res.gagner = 1;
        res.continuer = 0;
      }
    }
  }
  return res;
}

victoire condition2(int **grille)
{
  victoire res;
  res.gagner = -1;
  res.continuer = 1;
  int pionGagnants = 0;
  for (int i = 0; i < 10; i++)    // Verif ligne 0 (gagnant 2)
  {
    if (grille[0][i] > 4 && grille[0][i] < 9)
    {
      pionGagnants++;
    }
  }
  if (pionGagnants == 8)
  {
    res.gagner = 2;
    res.continuer = 0;
  }
  pionGagnants = 0;
  for (int i = 0; i < 10; i++)    // Verif ligne 9 (gagnant 1)
  {
    if (grille[9][i] > 0 && grille[9][i] < 5)
    {
      pionGagnants++;
    }
  }
  if (pionGagnants == 8)
  {
    res.gagner = 1;
    res.continuer = 0;
  }
  
  return res;
}
