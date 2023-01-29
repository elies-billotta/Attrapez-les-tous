#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "ellipse.h"
#include "mur.h"
#include "Cellule.h"
#include "Liste.h"
#include <iostream>
using namespace std;

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

void generateEllipse(Liste &l, int posX, int posY, string couleur){
        Ellipse ellipse;
        ellipse.x = posX;
        ellipse.y = posY;
        ellipse.rayon = rand() % 50 + 10;
        ellipse.randomVitesse();
        if (couleur == "rouge") ellipse.setCouleur(255, 0, 0);
        else if (couleur == "vert") ellipse.setCouleur(0, 255, 0);
        else if (couleur == "bleu") ellipse.setCouleur(0, 0, 255);
        else if (couleur == "jaune") ellipse.setCouleur(255, 255, 0);
        else if (couleur == "cyan") ellipse.setCouleur(0, 255, 255);
        else if (couleur == "magenta") ellipse.setCouleur(255, 0, 255);
        else if (couleur == "blanc") ellipse.setCouleur(255, 255, 255);
        else ellipse.randomCouleur();
        l.ajouter(ellipse);
}

bool handleEvent(Liste &l, Mur m)
{
    SDL_Event e; 
    while(SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT) 
            return false; 
        if (e.type == SDL_MOUSEBUTTONDOWN){
            if (clickOnEllipse(l, e) != nullptr){
                l.supprimer(*clickOnEllipse(l, e));
            }
            //sinon si la souris ne clique pas sur le mur, on ajoute une ellipse
            else if (!m.clic(e.motion.x, e.motion.y)){
                generateEllipse(l, e.motion.x, e.motion.y, "");
            }
        }
    }
    return true;
}

int main(int argc, char** argv) {
    SDL_Window* gWindow;
    SDL_Renderer* renderer;
    bool is_running = true; 
    Mur mur1;
    mur1.init(200, 200, 200, 150);

    // Création de la fenêtre
    gWindow = init("Awesome Game");

    // Initialisation des acteurs et de la liste
    Liste liste;
    liste.premier = nullptr;
    int nbEllipse = 10;
    if (argc > 1){
        nbEllipse = argc;
        for (int i = 1 ; i < argc ; i++){
            generateEllipse(liste, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, argv[i]);
        }    
    }  
    else {
        for(int i = 0 ; i < nbEllipse ; i++){
            generateEllipse(liste, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, "");
        }
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
        is_running = handleEvent(liste, mur1);
        if (!is_running)
            break;
        // GESTION ACTEURS

        //deplacement des ellipses de la liste
        Cellule *celluleActuelle = liste.premier;
        while (celluleActuelle != nullptr)
        {
            celluleActuelle->ellipse.deplacer(SCREEN_HEIGHT, SCREEN_WIDTH, mur1);
            celluleActuelle = celluleActuelle->suivant;
        }
        
        // EFFACAGE FRAME
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        
        // DESSIN FRAME
        mur1.draw(renderer);
        liste.draw(renderer);

        // VALIDATION FRAME
        SDL_RenderPresent(renderer);

        // PAUSE en ms
        SDL_Delay(1000/60); 
    }

    //Free resources and close SDL
    close(gWindow, renderer);

    return 0;
}
