#include "jeuGraphique.h"
#include "deplacement.h"
#include "jeuTerminal.h"
#include "affichage.h"
#include "conditionVictoire.h"
#include "ia.h"

/*
Compiler :
  Windows
    >  gcc src/fichiers.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2
    >  gcc src/fichiers.c -o bin/prog -I include -L lib -lmingw32 -lSDL2main -lSDL2 -mwindows    (n'ouvre pas le terminal en plus, si ca faisait chier qq)
  GNU/Linux MacOS
    > gcc *.c $(sdl2-config --cflags --libs) -o prog
*/

int verificationSaisieMenu(void)
{
  int continuer = 1; // tant que la saisie n'est pas bonne, continuer
  int nb; // nombre a retourner
  int retour; // verifier la saisie
  while (continuer == 1) 
  {
    retour = scanf("%d", &nb); // demander le nombre
    if (retour != 0 && nb >= 1 && nb <= 5) // verifier que le nombre soit correct
    {
      continuer = 0;
    }
    else // recommencer la saisie
    {
      printf("Erreur de saisie, veuillez recommencer\n");
      if (retour == 0)
      {
        nb = getchar();
      }
    }
  }
  return nb;
}

int main (int argc, char** argv)
{
  srand(time(NULL));
  int choix;
  system(CLEAR);
  printf("██████████  ████████  ████████  ██    ██  ████████  ████████  ████████  ████████\n");
  printf("    ██      ██    ██  ██    ██  ██    ██  ██        ██    ██  ██        ██      \n");
  printf("    ██      ████████  ████████  ██    ██  ██████    ████████  ████████  ██████  \n");
  printf("    ██      ██ ███    ██    ██   ██  ██   ██        ██ ███          ██  ██      \n");
  printf("    ██      ██   ███  ██    ██     ██     ████████  ██   ███  ████████  ████████\n");
  printf("╔═════════════════════════════════╗\n");
  printf("║                                 ║\n");
  printf("║  %s-------------Menu------------%s  ║\n", BLUE, RESET);
  printf("║                                 ║\n");
  printf("║  Choisissez le mode de jeux     ║\n");
  printf("║                                 ║\n");
  printf("║  %s[1] Joueur Vs Joueur Terminal%s  ║\n", GREEN, RESET);
  printf("║                                 ║\n");
  printf("║  %s[2] Joueur Vs Joueur Graphique%s ║\n", ORANGE, RESET);
  printf("║                                 ║\n");
  printf("║  %s[3] Joueur Vs IA (facile)%s      ║\n", BLUE, RESET);
  printf("║                                 ║\n");
  printf("║  %s[4] Joueur Vs IA (Difficile)%s   ║\n", RED, RESET);
  printf("║                                 ║\n");
  printf("║  [5] Quitter                    ║\n");
  printf("║                                 ║\n");
  printf("╚═════════════════════════════════╝\n");
  choix = verificationSaisieMenu();
  switch (choix) 
  {
    case 1:
      jeuTerminal();
      break;
    
    case 2:
      jeuGraphique();
      break;

    case 3:
      jeuGraphiqueIA1();
      break;
    
    case 4:
      jeuGraphiqueIA2();
      break;

    default:
      exit(EXIT_FAILURE);
      break;
  }
  return EXIT_SUCCESS;
}
