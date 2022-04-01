#include "affichage.h"
/*
Renderer Flags :

    SDL_RENDERER_SOFTWARE
    SDL_RENDERER_ACCELERATED
    SDL_RENDERER_PRESENTVSYNC
    SDL_RENDERER_TARGETTEXTURE
*/

// Exit/destruction
void SDL_ExitErreur(const char* message)
{
    SDL_Log("ERREUR : %s > %s", message, SDL_GetError());
    SDL_Quit();
    exit(EXIT_FAILURE);
}

void destructionTout(SDL_Window *window, SDL_Renderer *renderer, textures texture)
{
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (texture.plateau != NULL) {
        SDL_DestroyTexture(texture.plateau);
    }
    if (texture.coupPossible != NULL) {
        SDL_DestroyTexture(texture.coupPossible);
    }
    if (texture.selection != NULL) {
        SDL_DestroyTexture(texture.selection);
    }
    if (texture.J1carre != NULL) {
        SDL_DestroyTexture(texture.J1carre);
    }
    if (texture.J1triangle != NULL) {
        SDL_DestroyTexture(texture.J1triangle);
    }
    if (texture.J1losange != NULL) {
        SDL_DestroyTexture(texture.J1losange);
    }
    if (texture.J1rond != NULL) {
        SDL_DestroyTexture(texture.J1rond);
    }
    if (texture.J2carre != NULL) {
        SDL_DestroyTexture(texture.J2carre);
    }
    if (texture.J2triangle != NULL) {
        SDL_DestroyTexture(texture.J2triangle);
    }
    if (texture.J2losange != NULL) {
        SDL_DestroyTexture(texture.J2losange);
    }
    if (texture.J2rond != NULL) {
        SDL_DestroyTexture(texture.J2rond);
    }
    if (texture.J1victoire != NULL)
    {
        SDL_DestroyTexture(texture.J1victoire);
    }
    if (texture.J2victoire != NULL)
    {
        SDL_DestroyTexture(texture.J2victoire);
    }
    if (texture.Jvictoire != NULL)
    {
        SDL_DestroyTexture(texture.Jvictoire);
    }
    if (texture.Jdefaite != NULL)
    {
        SDL_DestroyTexture(texture.Jdefaite);
    }
    if (texture.J1panel != NULL)
    {
        SDL_DestroyTexture(texture.J1panel);
    }
    if (texture.J2panel)
    {
        SDL_DestroyTexture(texture.J2panel);
    }
    if (texture.Jpanel)
    {
        SDL_DestroyTexture(texture.Jpanel);
    }
    if (texture.Ordipanel)
    {
        SDL_DestroyTexture(texture.Ordipanel);
    }

    SDL_Quit(); 
}


// Fenetre  et rendu
SDL_Window* creationFenetre (SDL_Window *window)
{
    // Init
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {    // Si init fail on ferme le prog et on log l'erreur
        SDL_ExitErreur("SDL_Init");
    }

    // Creation fenetre
    window = SDL_CreateWindow(NOM_JEU,                                          // Nom fenetre
                              SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, // Position fenetre (x, y)
                              LARGEUR, HAUTEUR,                                 // Taille fenetre (w, h)
                              MODE_FENETRE);                                    // Mode affichage fenetre

    if (window == NULL) {   // Si fenetre existe pas : on ferme et on log l'erreur
        SDL_ExitErreur("SDL_CreateWindow");
    }
    return window;
}

SDL_Renderer* creationRendu(SDL_Window *window, SDL_Renderer *renderer)
{
    renderer = SDL_CreateRenderer(window,                   // Fenetre cible
                                  -1,                       // Driver (-1 pour initialiser)
                                  SDL_RENDERER_SOFTWARE);   // Flags Rendu
    if (renderer == NULL) {
        SDL_ExitErreur("SDL_CreateRenderer");
    }
    SDL_RenderPresent(renderer); 

    return renderer;
}


// Textures
SDL_Texture* creationTexture(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, textures allTextures, char* chemin)
{
    SDL_Surface *image = NULL;

    image = IMG_Load(chemin);
    if (image == NULL) {        // Charge l'image
        destructionTout(window, renderer, allTextures);
        SDL_ExitErreur("IMG_Load");
    }
    
    texture = SDL_CreateTextureFromSurface(renderer, image);
    if (texture == NULL) {      // Transforme l'image en surface
        destructionTout(window, renderer, allTextures);
        SDL_ExitErreur("SDL_CreateTextureFromSurface");
    }
    SDL_FreeSurface(image);
    


    return texture;
}

void afficherTexture(SDL_Window *window, SDL_Renderer *renderer, SDL_Texture *texture, textures allTextures, int x, int y)
{
    SDL_Rect rectangle;

    if (SDL_QueryTexture(texture, NULL, NULL, &rectangle.w, &rectangle.h) != 0) { // Charger la texture
        destructionTout(window, renderer, allTextures);
        SDL_ExitErreur("SDL_QueryTexture");
    }

    if (x < 0) {
        rectangle.x = (LARGEUR - rectangle.w) / 2; 
    } else {
        rectangle.x = x;
    }
    if (y < 0) {
        rectangle.y = (HAUTEUR - rectangle.h) / 2;
    } else {
        rectangle.y = y;
    }

    if (SDL_RenderCopy(renderer, texture, NULL, &rectangle) != 0) {     // La mettre dans le rendu
        destructionTout(window, renderer, allTextures);
        SDL_ExitErreur("SDL_RenderCopy");
    }
}

void afficherGrille(SDL_Window *window, SDL_Renderer *renderer, textures texture, int **grille, int joueur)
{
    int i;
    int j;

    SDL_RenderClear(renderer);      // On reprend un rendu vierge
    afficherTexture(window, renderer, texture.plateau, texture, 0, -1);
    if (joueur)
    {
        afficherTexture(window, renderer, texture.J2panel, texture, 650, -1);
    }
    else
    {
        afficherTexture(window, renderer, texture.J1panel, texture, 650, -1);
    }

    for (i = 0; i < TAILLE; i++) {
        for ( j = 0; j < TAILLE; j++) {
            switch (grille[i][j])
            {
            case 0: // CAS CASE VIDE : utilise pour pouvoir detecter une erreur eventuelle sur la grille (valeur incorrecte)
                break; // et switch plus optimise car majorite des cases sont 0, donc on break des le 1er cas (pas au default qui est a la fin)
            case 1: // CAS J1
                afficherTexture(window, renderer, texture.J1carre, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 2:
                afficherTexture(window, renderer, texture.J1triangle, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 3:
                afficherTexture(window, renderer, texture.J1losange, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 4:
                afficherTexture(window, renderer, texture.J1rond, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 5: // CAS J2
                afficherTexture(window, renderer, texture.J2carre, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 6:
                afficherTexture(window, renderer, texture.J2triangle, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 7:
                afficherTexture(window, renderer, texture.J2losange, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 8:
                afficherTexture(window, renderer, texture.J2rond, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 9: // CAS COUP POSSIBLE
                afficherTexture(window, renderer, texture.coupPossible, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            default:  //
                SDL_ExitErreur("afficherGrille() : erreur logique, valeur grille incorrecte");
                break;
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void afficherGrilleIA(SDL_Window *window, SDL_Renderer *renderer, textures texture, int **grille, int joueur)
{
    int i;
    int j;

    SDL_RenderClear(renderer);      // On reprend un rendu vierge
    afficherTexture(window, renderer, texture.plateau, texture, 0, -1);

    if (joueur)
    {
        afficherTexture(window, renderer, texture.Jpanel, texture, 650, -1);
    }
    else
    {
        afficherTexture(window, renderer, texture.Ordipanel, texture, 650, -1);
    }

    for (i = 0; i < TAILLE; i++) {
        for ( j = 0; j < TAILLE; j++) {
            switch (grille[i][j])
            {
            case 0: // CAS CASE VIDE : utilise pour pouvoir detecter une erreur eventuelle sur la grille (valeur incorrecte)
                break; // et switch plus optimise car majorite des cases sont 0, donc on break des le 1er cas (pas au default qui est a la fin)
            case 1: // CAS J1
                afficherTexture(window, renderer, texture.J1carre, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 2:
                afficherTexture(window, renderer, texture.J1triangle, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 3:
                afficherTexture(window, renderer, texture.J1losange, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 4:
                afficherTexture(window, renderer, texture.J1rond, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 5: // CAS J2
                afficherTexture(window, renderer, texture.J2carre, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 6:
                afficherTexture(window, renderer, texture.J2triangle, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 7:
                afficherTexture(window, renderer, texture.J2losange, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 8:
                afficherTexture(window, renderer, texture.J2rond, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            case 9: // CAS COUP POSSIBLE
                afficherTexture(window, renderer, texture.coupPossible, texture, j*LARGEUR_PIECE, i*HAUTEUR_PIECE);
                break;
            default:  //
                SDL_ExitErreur("afficherGrille() : erreur logique, valeur grille incorrecte");
                break;
            }
        }
    }
    SDL_RenderPresent(renderer);
}

textures chargerTextures(SDL_Window *window, SDL_Renderer *renderer, textures texture)
{
    texture.plateau = creationTexture(window, renderer, texture.plateau, texture, "src/images/plateau.bmp");
    texture.coupPossible = creationTexture(window, renderer, texture.coupPossible, texture, "src/images/coup_possible.png");
    texture.selection = creationTexture(window, renderer, texture.selection, texture, "src/images/selection.png");
    texture.J1carre = creationTexture(window, renderer, texture.J1carre, texture, "src/images/J1_carre.png");
    texture.J1triangle = creationTexture(window, renderer, texture.J1triangle, texture, "src/images/J1_triangle.png");
    texture.J1losange = creationTexture(window, renderer, texture.J1losange, texture, "src/images/J1_losange.png");
    texture.J1rond = creationTexture(window, renderer, texture.J1rond, texture, "src/images/J1_rond.png");
    texture.J2carre = creationTexture(window, renderer, texture.J2carre, texture, "src/images/J2_carre.png");
    texture.J2triangle = creationTexture(window, renderer, texture.J2triangle, texture, "src/images/J2_triangle.png");
    texture.J2losange = creationTexture(window, renderer, texture.J2losange, texture, "src/images/J2_losange.png");
    texture.J2rond = creationTexture(window, renderer, texture.J2rond, texture, "src/images/J2_rond.png");
    texture.J1victoire = creationTexture(window, renderer, texture.J1victoire, texture, "src/images/fin_J1.png");
    texture.J2victoire = creationTexture(window, renderer, texture.J2victoire, texture, "src/images/fin_J2.png");
    texture.Jvictoire = creationTexture(window, renderer, texture.Jvictoire, texture, "src/images/fin_J.png");
    texture.Jdefaite = creationTexture(window, renderer, texture.Jdefaite, texture, "src/images/fin_Ordi.png");
    texture.J1panel = creationTexture(window, renderer, texture.J1panel, texture, "src/images/J1_panel.png");
    texture.J2panel = creationTexture(window, renderer, texture.J2panel, texture, "src/images/J2_panel.png");
    texture.Jpanel = creationTexture(window, renderer, texture.Jpanel, texture, "src/images/J_panel.png");
    texture.Ordipanel = creationTexture(window, renderer, texture.Ordipanel, texture, "src/images/Ordi_panel.png");

    return texture;
}


// JEU EN GRAPHIQUE -----------------------------------------------------------------------------------------