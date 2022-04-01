#ifndef IA_H
#define IA_H
#include "lib/sdl/SDL.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/sdl_image/SDL_image.h"

#include "jeuGraphique.h"
#include "deplacement.h"
#include "jeuTerminal.h"
#include "affichage.h"
#include "conditionVictoire.h"

#define INFINI 100000

/*!
* \fn struct coord
* \brief structure qui définit une variable contenant les coordonnees d'une case
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
*/
#ifndef STRUCT_COORD
#define STRUCT_COORD
typedef struct coord
{
  int i;
  int j;
}coord;
#endif // STRUCT_COORD


/*!
* \fn struct victory
* \brief structure qui contient deux booleens permettant de savoir si la partie est finie et qui a gagne
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
*/
#ifndef STRUCT_VICTORY
#define STRUCT_VICTORY
typedef struct victory
{
  int continuer; // 1 = continuer, 0 = arret
  int gagner; // 1 = le joueur 1 a gagner, 2 = le joueur 2  a gagner, 0 egalite
}victoire;
#endif


/*!
* \fn struct coupEtEval
* \brief structure qui définit une variable contenant les coordonnees d'une case ainsi que le score lie a cette case
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
*/
typedef struct coupEtEval
{
    coord coup;
    int scoreCoup;
} coupEtEval;


/*!
* \fn struct NoeudEvalCoup
* \brief structure qui definit une liste d'element coupEtEval (coord+score) 
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
*/
typedef struct NoeudEvalCoup {
  coupEtEval evalCoup;
  struct NoeudEvalCoup* suivant;
}NoeudEvalCoup;


/*!
* \fn struct NoeudEvalCoup*
* \brief structure qui definit la tete de la liste EvalCoup
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
*/
typedef struct NoeudEvalCoup* teteEvalCoup ;


/* ************************** */


/*!
* \fn void copieGrille(int **grille)
* \brief copie la grille passee en parametres dans une grille temporaire
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
*/
void copieGrille(int **grille);


/*!
* \fn NoeudEvalCoup* creerElementEvalCoup(coupEtEval elt)
* \brief fonction qui creer un element de type coupEtEval dans la liste NoeudEvalCoup
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
* \param coupEtEval elt : element a creer dans la liste
* \return la liste avec l'element creer
*/
NoeudEvalCoup *creerElementEvalCoup(coupEtEval elt);



void ajouterElementEvalCoup(teteEvalCoup *tetedeliste, coupEtEval elt);

/*!
* \fn int alphaBeta(int **grilleTemp, int profondeur, int alpha, int beta, victoire etatPartie, int IAJoue)
* \brief fonction qui creer un element de type coupEtEval dans la liste NoeudEvalCoup
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
* \param int **grilleTemp : grille de jeu temporaire, int profondeur : nombre de tours simules, int alpha, int beta : permet de limiter le nombre de
*        simulation de coup, victoire etatPartie : permet de savoir si la partie est terminee et qui a gagne, int IAJoue : 1 si l'ia joue, 0 sinon
* \return le meilleur score de la grille (permet de savoir quel est le meilleur coup a faire)
*/
int alphaBeta(int **grilleTemp, int profondeur, int alpha, int beta, victoire etatPartie, int IAJoue);


/*!
* \fn int evaluation(int **grilleTemp)
* \brief fonction qui calcule le score du plateau
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
* \param int **grilleTemp : grille de jeu temporaire
* \return le score de la grille
*/
int evaluation(int **grilleTemp);


/*!
* \fn coord jouer(int **grilleTemp, int profondeur, int alpha, int beta, victoire etatPartie, int IAJoue)
* \brief fonction qui teste les scores de tous les coups pour choisir le meilleur coup
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
* \param int **grilleTemp : grille de jeu temporaire
* \return le meilleur coup a jouer
*/
coord jouer(int **grille);


/*!
* \fn coord coupMax(teteEvalCoup *tetedeliste)
* \brief fonction qui trouve le coup ayant le meilleur score
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
* \param teteEvalCoup *tetedeliste : liste des coups avec leurs scores
* \return le coup au score le plus eleve
*/
coord coupMax(teteEvalCoup *tetedeliste);


/*!
* \fn int max(int alpha, int score)
* \brief fonction qui compare les deux entiers passes en parametres et retourne le plus grand
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
* \param int alpha : permet de limiter les simulations de coups, int score : le score du coup en cours
* \return le score le plus eleve
*/
int max(int alpha, int score);


/*!
* \fn int min(int beta, int score)
* \brief fonction qui compare les deux entiers passes en parametres et retourne le plus petit
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
* \param int beta : permet de limiter les simulations de coups, int score : le score du coup en cours
* \return le score le plus petit
*/
int min(int beta, int score);


/*!
* \fn int **deplacerPieceIA(int **grille, coord pion, coord emplacement)
* \brief fonction qui deplace une piece a l'emplacement passe en parametre
* \author Clement Bertails, Maxime Longuet, Pierrick Maurer
* \date 2 mai 2020
* \param int ** grille : plateau de jeu, coord pion : pion a deplacer, coord emplacement : position ou l'on vetu jouer
* \return la nouvelle grille
*/
int** deplacerPieceIA(int **grille, coord pion, coord emplacement);

#endif // IA_H