#ifndef CONDITIONVICTOIRE_H
#define CONDITIONVICTOIRE_H
#include "lib/sdl/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/sdl_image/SDL_image.h"

#include "jeuGraphique.h"
#include "deplacement.h"
#include "jeuTerminal.h"
#include "affichage.h"
#include "ia.h"


#ifndef STRUCT_VICTORY
#define STRUCT_VICTORY
typedef struct victory
{
  int continuer; // 1 = continuer, 0 = arret
  int gagner; // 1 = le joueur 1 a gagner, 2 = le joueur 2  a gagner, 0 egalite
}victoire;
#endif

victoire conditionVictoire(int **grille, int tour, int joueur);

victoire condition1(int **grille, int tour, int joueur);

victoire condition2(int **grille);

#endif // CONDITIONVICTOIRE_H