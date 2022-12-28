#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "ellipse.h"
#include <iostream>
using namespace std;

void draw(SDL_Renderer* renderer, Ellipse e)
{
    /* Remplissez cette fonction pour faire l'affichage du jeu */
    filledEllipseRGBA(renderer, e.x, e.y, e.rayon, e.rayon, e.r, e.g, e.b, 255); 
    
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
    Ellipse e = {100, 100, 0, 0, 50, 255, 0, 0};

    //vitesse aléatoire entre -5 et 5
    e.vx = rand() % 10 - 5;
    e.vy = rand() % 10 - 5;

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
        e.x += e.vx;
        e.y += e.vy;

        //rebond sur les bords
        if (e.x + e.rayon >= SCREEN_WIDTH || e.x - e.rayon <= 0)
            e.vx = -e.vx;
        if (e.y + e.rayon >= SCREEN_HEIGHT || e.y - e.rayon <= 0)
            e.vy = -e.vy;
        // ...
        
        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // DESSIN
        draw(renderer, e);


        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000/60); 
    }

    //Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
