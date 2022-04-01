#include "jeuTerminal.h"

void jeuTerminal (void)
{ // jeu sur le terminal
  int continuer = 1; // variable d'arret du jeu
  int joueur = 0; // numero du joueur
  int tour = 1; // numero du tour
  int **grille = creationGrille(); // grille de jeu
  victoire res;
  initialiserGrille(grille);
  while (continuer)
  {
    tourJoueur(grille, joueur); // tour du joueur
    res = conditionVictoire(grille, tour, joueur);
    continuer = res.continuer;
    joueur = (joueur+1)%2;
    tour += 0.5;
  }
  switch (res.gagner)
  {
  case 1:
    printf("Le joueur 1 a gagner\n");
    break;

  case 2:
    printf("Le joueur 2 a gagner\n");
    break;

  default:
    exit(EXIT_FAILURE);
    break;
  }
  freeInt2(grille, TAILLE);
}

void tourJoueur(int **grille, int joueur)
{ // tour du joueur (terminal)
  coord pion; // pion a bouger
  coord emplacement; // emplacement choisi parmis ceux proposer
  system(CLEAR);
  printf("A vous de jouer : Joueur %d\n", joueur+1);
	affGrille(grille);
  pion = selectionPiece(grille, joueur);
  emplacement = saisieEmplacement(grille);
  system(CLEAR);
  printf("Voici les coups possible pour cette pièce :\n");
  affGrille(grille);
  deplacerPiece(grille, pion, emplacement);
  EnleverActionPossibleGrille(grille);
}

void affGrille(int ** grille)
{ // afficher la grille sur le terminal
  printf("  1   2   3   4   5   6   7   8   9   10\n");
  printf("╔═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╦═══╗\n"); // afficher haut
  for (int i = 0; i < TAILLE; i++) {
    for (int j = 0; j < TAILLE; j++) {
      if (grille[i][j] == 1 || grille[i][j] == 2 || grille [i][j] == 3 || grille[i][j] == 4) // pion joueur 1
      {
        printf("║%s %d %s", ORANGE, grille[i][j], RESET);
      }
      else if (grille[i][j] == 5 || grille[i][j] == 6 || grille [i][j] == 7 || grille[i][j] == 8) // pion joueur 2
      {
        printf("║%s %d %s", GREEN, grille[i][j], RESET);
      }
      else if (grille[i][j] == 9) // case disponible pour action
      {
        printf("║%s %d %s", RED, grille[i][j], RESET);
      }
      else
      {
        printf("║ %d ", grille[i][j]);
      }
    }
    printf("║ %d\n", i+1); // fin de ligne
    if (i != 9) {
      printf("╠═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╬═══╣\n" ); // separtaion entre 2 lignes
    }
  }
  printf("╚═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╩═══╝\n"); // afficher bas
}

int** creationGrille (void)
{ // creer la grille de jeu
  int **grille = malloc(sizeof(int*) * TAILLE); // allouer le tableau 2 dimensions
  if (grille == NULL) // verifier l'allocation
  {
    printf("Erreur Allocation Grille\n");
    exit(EXIT_FAILURE);
  }
  for (int i = 0; i < TAILLE; i++) // allouer tout les int* determiner precedemment
  {
    grille[i] = malloc(sizeof(int) * TAILLE);
    if (grille[i] == NULL) // verifier l'allocation
    {
      printf("Erreur Allocation Grille\n");
      exit(EXIT_FAILURE);
    }
  }
  for (int i = 0; i < TAILLE; i++) // initialiser la grille de jeu
  {
    for (int j = 0; j < TAILLE; j++)
    {
      grille[i][j] = 0;
    }
  }
  return grille;
}

void initialiserGrille(int **grille)
{ // initialiser la grille de jeu (1 = carre, 2 = triangle, 3 = losange, 4 = rond -> joueur 1)(5 = carre, 6 = triangle, 7 = losange, 8 = rond -> joueur 2)
                   
  grille[0][1] = 1;
  grille[0][2] = 2;
  grille[0][3] = 3;
  grille[0][4] = 4;
  grille[0][5] = 4;
  grille[0][6] = 3;
  grille[0][7] = 2;
  grille[0][8] = 1;

  grille[9][1] = 5;
  grille[9][2] = 6;
  grille[9][3] = 7;
  grille[9][4] = 8;
  grille[9][5] = 8;
  grille[9][6] = 7;
  grille[9][7] = 6;
  grille[9][8] = 5;/*
  grille[8][1] = 1;
  grille[8][2] = 2;
  grille[8][3] = 3;
  grille[8][4] = 4;
  grille[8][5] = 4;
  grille[8][6] = 3;
  grille[8][7] = 2;
  grille[0][8] = 1;

  grille[1][1] = 5;
  grille[1][2] = 6;
  grille[1][3] = 7;
  grille[1][4] = 8;
  grille[1][5] = 8;
  grille[1][6] = 7;
  grille[1][7] = 6;
  grille[9][8] = 5;*/
}

void EnleverActionPossibleGrille(int **grille)
{ // enlever l'affichage des coups possible
  for (int i = 0; i < TAILLE; i++)
  {
    for (int j = 0; j < TAILLE; j++)
    {
      if (grille[i][j] == 9)
      {
        grille[i][j] = 0;
      }
    } 
  }
}

coord saisiePion(int **grille, int joueur)
{
  coord pion; // coordonnees du pion a deplacer
  int continuer = 1; // tant que la saisie n'est pas correct
  while (continuer)
  {
    printf("Saisissez la ligne du pion a déplacer\n");
    pion.i = saisieNb();
    pion.i--;
    printf("Saisissez la Colonne du pion a déplacer\n");
    pion.j = saisieNb();
    pion.j--;
    if (joueur == 0 && (grille[pion.i][pion.j] == 1 || grille[pion.i][pion.j] == 2 || grille[pion.i][pion.j] == 3 || grille[pion.i][pion.j] == 4))
    {
      continuer = 0;
    }
    else if (joueur == 1 && (grille[pion.i][pion.j] == 5 || grille[pion.i][pion.j] == 6 || grille[pion.i][pion.j] == 7 || grille[pion.i][pion.j] == 8))
    {
      continuer = 0;
    }
    else
    {
      printf("Erreur de saisie, veuillez recommencer\n");
    }
  }
  return pion;
}

coord saisieEmplacement(int **grille)
{ // saisie d'un emplacement valide
  coord emplacement; //coordonnees de l'emplacement choisi
  int continuer = 1; // tant que la saisie n'est pas correct
  while (continuer)
  {
    printf("Saisissez la ligne de la case choisie\n");
    emplacement.i = saisieNb(); // ligne
    emplacement.i--;
    printf("Saisissez la Colonne de la case choisie\n");
    emplacement.j = saisieNb(); // colonne
    emplacement.j--;
    if (grille[emplacement.i][emplacement.j] == 9) // verifier si l emplacement est valide
    {
      continuer = 0;
    }
    else // recommencer la saisie
    {
      printf("Erreur de saisie, veuillez recommencer\n");
    }
  }
  return emplacement;
}

int saisieNb(void)
{ // Saisir un nombre correct
  int continuer = 1; // tant que la saisie n'est pas bonne, continuer
  int nb; // nombre a retourner
  int retour; // verifier la saisie
  while (continuer) 
  {
    retour = scanf("%d", &nb); // demander le nombre
    if (retour != 0 && nb >= 1 && nb <= 10) // verifier que le nombre soit correct
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

coord selectionPiece(int **grille, int joueur) // permet de changer de piece selectionner
{
  int continuer = 1;
  int choix;
  coord pion;
  while (continuer)
  {
    pion = saisiePion(grille, joueur);
    deplacementPossible(grille, pion);
    system(CLEAR);
    affGrille(grille);
    printf("Si vous voulez changer de pièce a jouer, tapez 1 sinon tapez un autre chiffre\n");
    choix = saisieNb();
    if (choix != 1)
    {
      continuer = 0;
    }
    else
    {
      system(CLEAR);
      EnleverActionPossibleGrille(grille);
      affGrille(grille);
    }
  }
  return pion;
}

void freeInt2(int** tab, int m)
{
    for (int i = 0; i < m; i++) 
    {
        free(tab[i]);
    }
    free(tab);
}