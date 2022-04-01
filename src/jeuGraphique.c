#include "jeuGraphique.h"

void jeuGraphique(void)
{ // jeu graphique
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  textures texture;
  texture.plateau = NULL;
  texture.coupPossible = NULL;
  texture.selection = NULL;
  texture.J1carre = NULL;
  texture.J1triangle = NULL;
  texture.J1losange = NULL;
  texture.J1rond = NULL;
  texture.J2carre = NULL;
  texture.J2triangle = NULL;
  texture.J2losange = NULL;
  texture.J2rond = NULL;
  texture.J1victoire = NULL;
  texture.J2victoire = NULL;
  texture.Jvictoire = NULL;
  texture.Jdefaite = NULL;
  texture.J1panel = NULL;
  texture.J2panel = NULL;
  texture.Jpanel = NULL;
  texture.Ordipanel = NULL;
  int continuer = 1; // variable d'arret du jeu
  int joueur = 0; // numero du joueur
  int tour = 1; // numero du tour
  int demiTour = 0;
	int **grille = creationGrille(); // grille de jeu*
  victoire res;

  initialiserGrille(grille);
  window = creationFenetre(window);
  renderer = creationRendu(window, renderer);
  texture = chargerTextures(window, renderer, texture);
  while (continuer)
  {
    tourJoueurGraphique(grille, joueur, window, renderer, texture); // tour du joueur
    res = conditionVictoire(grille, tour, joueur);
    continuer = res.continuer; 
    joueur = (joueur+1)%2;
    demiTour++;
    if (demiTour == 2)
    {
      demiTour = 0;
      tour++;
    }
  }
  afficherGrille(window, renderer, texture, grille, joueur);
  switch (res.gagner)
  {
  case 1:   // VERIF 0 et -1
    afficherTexture(window, renderer, texture.J1victoire, texture, 0, -1); // On affiche la victoire de j1
    SDL_RenderPresent(renderer);
    break;

  case 2:   // VERIF
    afficherTexture(window, renderer, texture.J2victoire, texture, 0, -1); // On affiche la victoire de j2
    SDL_RenderPresent(renderer);
    break;

  default:
    exit(EXIT_FAILURE);
    break;
  }
  SDL_Delay(3000);
  destructionTout(window, renderer, texture);
  freeInt2(grille, TAILLE);
}

void tourJoueurGraphique(int **grille, int joueur, SDL_Window *window, SDL_Renderer *renderer, textures texture)
{ // tour du joueur (graphique)
  empla coup; // coup + emplacement ou jouer
	afficherGrille(window, renderer, texture, grille, joueur);
  coup = saisieEmplacementGraphique(grille, joueur, window, renderer, texture); // saisie du pion et de l emplacement a jouer
  deplacerPieceGraphique(grille, coup); // deplacer les pion
  EnleverActionPossibleGrille(grille);
}

empla saisieEmplacementGraphique(int **grille, int joueur, SDL_Window *window, SDL_Renderer *renderer, textures texture)
{ // verifier si l emplacement est correct
  empla coup; //coordonnees de l'emplacement choisi
  int continuer = 1; // tant que la saisie n'est pas correct
  while (continuer)
  {
    coup.emplacement = recupererClick();
    if (coup.emplacement.i == -1)  // Si on clique sur la croix on ferme le programme
    {
      printf("Vous avez choisi de quitter le programme\n"); // a mettre en affichage graphique avec un delai
      destructionTout(window, renderer, texture);
      freeInt2(grille, TAILLE);
      exit(EXIT_SUCCESS);
    }
    if (grille[coup.emplacement.i][coup.emplacement.j] == 9)
    {
      continuer = 0;
    }
    else if (joueur == 0 && (grille[coup.emplacement.i][coup.emplacement.j] == 1 || grille[coup.emplacement.i][coup.emplacement.j] == 2 || grille[coup.emplacement.i][coup.emplacement.j] == 3 || grille[coup.emplacement.i][coup.emplacement.j] == 4))
    {
      EnleverActionPossibleGrille(grille);
      deplacementPossible(grille, coup.emplacement);
      afficherGrille(window, renderer, texture, grille, joueur);
      coup.pion = coup.emplacement;
    }
    else if (joueur == 1 && (grille[coup.emplacement.i][coup.emplacement.j] == 5 || grille[coup.emplacement.i][coup.emplacement.j] == 6 || grille[coup.emplacement.i][coup.emplacement.j] == 7 || grille[coup.emplacement.i][coup.emplacement.j] == 8))
    {
      EnleverActionPossibleGrille(grille);
      deplacementPossible(grille, coup.emplacement);
      afficherGrille(window, renderer, texture, grille, joueur);
      coup.pion = coup.emplacement;
    }
  }
  return coup;
}

coord recupererClick(void)
{ // recuperer un clique sur la fenetre graphique
  coord coordPion;
  int continuer = 1;
  while (continuer)
  {
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_MOUSEBUTTONDOWN:
      coordPion.i = event.button.y/HAUTEUR_PIECE;
      coordPion.j = event.button.x/LARGEUR_PIECE;
      continuer = 0;
      break;
    
    case SDL_QUIT:
      coordPion.i = -1;
      continuer = 0;
      break;

    default:
      break;
    }
  }
  return coordPion;
}

void jeuGraphiqueIA1(void)
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  textures texture;
  texture.plateau = NULL;
  texture.coupPossible = NULL;
  texture.selection = NULL;
  texture.J1carre = NULL;
  texture.J1triangle = NULL;
  texture.J1losange = NULL;
  texture.J1rond = NULL;
  texture.J2carre = NULL;
  texture.J2triangle = NULL;
  texture.J2losange = NULL;
  texture.J2rond = NULL;
  texture.J1victoire = NULL;
  texture.J2victoire = NULL;
  texture.Jvictoire = NULL;
  texture.Jdefaite = NULL;
  texture.J1panel = NULL;
  texture.J2panel = NULL;
  texture.Jpanel = NULL;
  texture.Ordipanel = NULL;
  int continuer = 1; // variable d'arret du jeu
  int joueur = rand()%2; // numero du joueur
  int tour = 1; // numero du tour
  int demiTour = 0;
	int **grille = creationGrille(); // grille de jeu*
  victoire res;

  initialiserGrille(grille);
  window = creationFenetre(window);
  renderer = creationRendu(window, renderer);
  texture = chargerTextures(window, renderer, texture);
  while (continuer)
  {
    if (joueur == 1)
    {
      tourJoueurGraphique(grille, joueur, window, renderer, texture); // tour du joueur
    }
    else
    {
      //tourIAFacile(grille);
    }
    res = conditionVictoire(grille, tour, joueur);
    continuer = res.continuer;
    joueur = (joueur+1)%2;
    demiTour++;
    if (demiTour == 2)
    {
      demiTour = 0;
      tour++;
    }
  }
  afficherGrille(window, renderer, texture, grille, joueur);
  switch (res.gagner)
  {
  case 1:   // VERIF 0 et -1
    afficherTexture(window, renderer, texture.J1victoire, texture, 0, -1); // On affiche la victoire de j1
    SDL_RenderPresent(renderer);
    break;

  case 2:   // VERIF
    afficherTexture(window, renderer, texture.J2victoire, texture, 0, -1); // On affiche la victoire de j2
    SDL_RenderPresent(renderer);
    break;

  default:
    exit(EXIT_FAILURE);
    break;
  }
  SDL_Delay(3000);
  destructionTout(window, renderer, texture);
  freeInt2(grille, TAILLE);
}

void jeuGraphiqueIA2(void)
{
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  textures texture;
  texture.plateau = NULL;
  texture.coupPossible = NULL;
  texture.selection = NULL;
  texture.J1carre = NULL;
  texture.J1triangle = NULL;
  texture.J1losange = NULL;
  texture.J1rond = NULL;
  texture.J2carre = NULL;
  texture.J2triangle = NULL;
  texture.J2losange = NULL;
  texture.J2rond = NULL;
  texture.J1victoire = NULL;
  texture.J2victoire = NULL;
  texture.Jvictoire = NULL;
  texture.Jdefaite = NULL;
  texture.J1panel = NULL;
  texture.J2panel = NULL;
  texture.Jpanel = NULL;
  texture.Ordipanel = NULL;
  int continuer = 1; // variable d'arret du jeu
  int joueur = rand()%2; // numero du joueur
  int tour = 1; // numero du tour
  int demiTour = 0;
	int **grille = creationGrille(); // grille de jeu*
  victoire res;

  initialiserGrille(grille);
  window = creationFenetre(window);
  renderer = creationRendu(window, renderer);
  texture = chargerTextures(window, renderer, texture);
  while (continuer)
  {
    if (joueur == 1)
    {
      tourJoueurGraphique(grille, joueur, window, renderer, texture); // tour du joueur
    }
    else
    {
      //tourIAFacile(grille);
    }
    res = conditionVictoire(grille, tour, joueur);
    continuer = res.continuer;
    joueur = (joueur+1)%2;
    demiTour++;
    if (demiTour == 2)
    {
      demiTour = 0;
      tour++;
    }
  }
  afficherGrille(window, renderer, texture, grille, joueur);
  switch (res.gagner)
  {
  case 1:   // VERIF 0 et -1
    afficherTexture(window, renderer, texture.J1victoire, texture, 0, -1); // On affiche la victoire de j1
    SDL_RenderPresent(renderer);
    break;

  case 2:   // VERIF
    afficherTexture(window, renderer, texture.J2victoire, texture, 0, -1); // On affiche la victoire de j2
    SDL_RenderPresent(renderer);
    break;

  default:
    exit(EXIT_FAILURE);
    break;
  }
  SDL_Delay(3000);
  destructionTout(window, renderer, texture);
  freeInt2(grille, TAILLE);
}