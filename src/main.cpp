#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "ellipse.h"
#include "mur.h"
#include "Cellule.h"
#include "Liste.h"
#include <iostream>
using namespace std;

void draw(SDL_Renderer* renderer, Liste l)
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

bool handleEvent()
{
    /* Remplissez cette fonction pour gérer les inputs utilisateurs */
    SDL_Event e; 
    while (SDL_PollEvent(&e)){ 
        if (e.type == SDL_QUIT) 
            return false; 
    }
    return true;
}


int main(int argc, char** argv) {
    SDL_Window* gWindow;
    SDL_Renderer* renderer;
    bool is_running = true; 

    // Creation de la fenetre
    gWindow = init("Awesome Game");

    // Initialisation d'un acteur 'Ellipse'

    Ellipse e;
    e.x = rand() % SCREEN_WIDTH;
    e.y = rand() % SCREEN_HEIGHT;
    e.rayon = 20;
    e.r = rand() % 255;
    e.g = rand() % 255;
    e.b = rand() % 255;

    Ellipse e2;
    e2.x = rand() % SCREEN_WIDTH;
    e2.y = rand() % SCREEN_HEIGHT;
    e2.rayon = 20;
    e2.r = rand() % 255;
    e2.g = rand() % 255;

    //vitesse aléatoire entre -5 et 5
    e.vx = rand() % 10 - 5;
    e.vy = rand() % 10 - 5;
    e2.vx = rand() % 10 - 5;
    e2.vy = rand() % 10 - 5;



 //créér une liste d'ellipses
    Liste liste;
    liste.premier = nullptr;
    liste.ajouter(e);
    liste.ajouter(e2);

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
        is_running = handleEvent();
        if (!is_running)
            break;
        // GESTION ACTEURS

        //deplacement

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
