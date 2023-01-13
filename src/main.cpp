#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "ellipse.h"
#include "mur.h"
#include "Cellule.h"
#include "Liste.h"
#include <iostream>
using namespace std;

void draw(SDL_Renderer* renderer, Liste &l)
{
    //dessiner les ellipses de la liste
    Cellule *celluleActuelle = l.premier;
    while (celluleActuelle != nullptr)
    {
        Ellipse e = celluleActuelle->ellipse;
        filledEllipseRGBA(renderer, e.x, e.y, e.rayon, e.rayon, e.r, e.g, e.b, 255);
        celluleActuelle = celluleActuelle->suivant;
    }
}

Ellipse* clickOnEllipse(Liste &l, SDL_Event &e){
    Cellule *celluleActuelle = l.premier;
    while (celluleActuelle != nullptr)
    {
        Ellipse ellipse = celluleActuelle->ellipse;
        if (ellipse.clic(e.motion.x, e.motion.y)){
            return &(celluleActuelle->ellipse);
        }
        celluleActuelle = celluleActuelle->suivant;
    }
    return nullptr;
}

bool handleEvent(Liste &l)
{
    SDL_Event e; 
    while(SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT) 
            return false; 
        if (e.type == SDL_MOUSEBUTTONDOWN){
            if (clickOnEllipse(l, e) != nullptr){
                l.supprimer(*clickOnEllipse(l, e));
            }
            else {
                Ellipse ellipse;
                ellipse.x = e.motion.x;
                ellipse.y = e.motion.y;
                ellipse.rayon = rand() % 50 + 10;
                ellipse.randomVitesse();
                ellipse.randomCouleur();
                l.ajouter(ellipse);
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    SDL_Window* gWindow;
    SDL_Renderer* renderer;
    bool is_running = true; 

    // Création de la fenêtre
    gWindow = init("Awesome Game");
    //SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);

    // Initialisation des acteurs et de la liste
    Liste liste;
    liste.premier = nullptr;
    for (int i = 0; i < 10; i++)
    {
        Ellipse e;
        e.x = rand() % SCREEN_WIDTH;
        e.y = rand() % SCREEN_HEIGHT;
        e.rayon = rand() % 50 + 10;
        e.randomVitesse();
        e.randomCouleur();
        liste.ajouter(e);
    }
    
    if (!gWindow)
    {
        SDL_Log("Failed to initialize!\n");
        exit(1);
    }

    renderer = SDL_CreateRenderer(gWindow, -1, 0); // SDL_RENDERER_PRESENTVSYNC

    /*  GAME LOOP  */
    while(true)
    {
        // INPUTS
        is_running = handleEvent(liste);
        if (!is_running)
            break;
        // GESTION ACTEURS

        //deplacement des ellipses de la liste
        Cellule *celluleActuelle = liste.premier;
        while (celluleActuelle != nullptr)
        {
            celluleActuelle->ellipse.deplacer(SCREEN_HEIGHT, SCREEN_WIDTH);
            celluleActuelle = celluleActuelle->suivant;
        }
        
        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // DESSIN FRAME
        draw(renderer, liste);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000/60); 
    }

    //Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
