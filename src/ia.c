#include "ia.h"

void copieGrille(int **grille)
{
    int **grilleTemp = creationGrille();

    for (int i = 0; i < TAILLE; i++)
    {
        for (int j = 0; j < TAILLE; j++)
        {
            grilleTemp[i][j] = grille[i][j];
        }
    }
}


NoeudEvalCoup *creerElementEvalCoup(coupEtEval elt) //cree un element de type coupEtEval contenant le coup a jouer et son score
{
  NoeudEvalCoup *nouveau = malloc(sizeof(NoeudEvalCoup));
  nouveau->evalCoup = elt;
  nouveau->suivant = NULL;
  return nouveau;
}


void ajouterElementEvalCoup(teteEvalCoup *tetedeliste, coupEtEval elt) //ajoute un element a la liste des coups couples a leurs scores
{
  NoeudEvalCoup *nouveau = creerElementEvalCoup(elt);
  nouveau->suivant = *tetedeliste;
  *tetedeliste = nouveau;
}


int alphaBeta(int **grilleTemp, int profondeur, int alpha, int beta, victoire etatPartieTemp, int IAJoue)
{
  coord pion;

    if (etatPartieTemp.continuer == 0 || profondeur == 0) //fin de partie ou bas de l'arbre
    {
        return evaluation(grilleTemp);
    } else {
      if (IAJoue) {
        alpha = -INFINI;
        //pour tous les coups possible
        for (int i = 0; i < TAILLE; i++) {
          for (int j = 0; j < TAILLE; j++) {
            if (grilleTemp[i][j] <= 4 && grilleTemp[i][j] > 0) {
              pion.i = i;
              pion.j = j;
              deplacementPossible(grilleTemp, pion);
              for (int i2 = 0; i2 < TAILLE; i2++) {
                for (int j2 = 0; j2 < TAILLE; j2++) {
                  //calcul de alpha en appelant alphaBeta pour le coup du joueur (descend dans l'arbre)
                  //alpha = max(alpha, /* alphaBeta(deplacerPiece(grille[i2][j2], noeud), profondeur-1, alpha, beta, etatPartieTemp, 0 */);
                }
              }
              EnleverActionPossibleGrille(grilleTemp); //supprime les 9 de la grille (coups possibles)
              if (alpha >= beta) {
                return alpha; //on est arrivé au score maximum
              }
            }
          }
        }
        //fin pour tous les coups
        return alpha;  

        } else {
          beta = +INFINI;
          //pour tous les coups possible
          for (int i = 0; i < TAILLE; i++) {
            for (int j = 0; j < TAILLE; j++) {
              if (grilleTemp[i][j] > 4 && grilleTemp[i][j] < 9) {
                pion.i = i;
                pion.j = j;
                deplacementPossible(grilleTemp, pion);
                for (int i2 = 0; i2 < TAILLE; i2++) {
                  for (int j2 = 0; j2 < TAILLE; j2++) {
                    //calcul de beta en appelant alphaBeta pour le coup de l'IA (descend dans l'arbre)
                    //beta = min(beta, alphaBeta(deplacerPieceIA(grille[i2][j2], noeud), profondeur-1, alpha, beta, etatPartieTemp, 1));
                  }
                }
                EnleverActionPossibleGrille(grilleTemp); //supprime les 9 de la grille (coups possibles)
                if (beta <= alpha) {
                  return beta; //on est arrive au score maximum
                }
              }
            }
          }
        //fin pour tous les coups possibles
        return beta;
      }
    }
}




int evaluation(int **grilleTemp)
{
    int score = 0;
    for (int i = 0; i < TAILLE; i++)
    {
        if (grilleTemp[0][i] == 1 || grilleTemp[0][i] == 2 || grilleTemp[0][i] == 3 || grilleTemp[0][i] == 4) //si le depart n'est pas libere, enleve des points
        {
            score -= 1000;
        }
        
        for (int j = 0; j < TAILLE; j++)
        {
            if (grilleTemp[i][j] == 1 || grilleTemp[i][j] == 2 || grilleTemp[i][j] == 3 || grilleTemp[i][j] == 4)
            {
              score += (10*i) / 8; //evalue l'avancee des pions de l'IA
            }
            if (grilleTemp[i][j] == 5 || grilleTemp[i][j] == 6 || grilleTemp[i][j] == 7 || grilleTemp[i][j] == 8)
            {
              score -= (10*(9-i)) / 8; //evalue l'avancee des pions de l'adversaire
            }
        }
    }
    return score;
}


coord coupMax(teteEvalCoup *tetedeliste)
{
  teteEvalCoup temp = *tetedeliste;
  int max = temp -> evalCoup.scoreCoup;
  coord coupMaximum = temp -> evalCoup.coup;

  while (temp -> suivant != NULL) {
    temp = temp -> suivant;
    if (temp -> evalCoup.scoreCoup > max && temp != NULL) {
      max = temp -> evalCoup.scoreCoup;
      coupMaximum = temp -> evalCoup.coup;
    }
  }
  return coupMaximum;
}


int max(int alpha, int score)
{
  if (alpha < score)
  {
    alpha = score;
  }
  return alpha;
}


int min(int beta, int score)
{
  if (beta > score)
  {
    beta = score;
  }
  return beta;
}


int** deplacerPieceIA(int **grille, coord pion, coord emplacement)
{
  grille[emplacement.i][emplacement.j] = grille[pion.i][pion.j];
  grille[pion.i][pion.j] = 0;
  return grille;
}