#include "application_ui.h"
#include "SDL2_gfxPrimitives.h"
#include "ellipse.h"
#include "mur.h"
#include "Cellule.h"
#include "Liste.h"
#include <iostream>
#include<cstdlib>
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

Ellipse generateEllipse(int posX, int posY){
        Ellipse ellipse;
        ellipse.x = posX;
        ellipse.y = posY;
        ellipse.rayon = rand() % 50 + 10;
        ellipse.randomVitesse();
        ellipse.randomCouleur();
        return ellipse;
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
            else if (!m.clic(e.motion.x, e.motion.y)){
                Ellipse el = generateEllipse(e.motion.x, e.motion.y);
                while (el.dansMur(m)){
                    el = generateEllipse(e.motion.x, e.motion.y);
                }
                l.ajouter(el);
            }
        }
    }
    return true;
}

Ellipse generateRandomEllipse(Mur mur, string couleur){
    Ellipse ellipse;
    ellipse.rayon = rand() % 50 +10;
    ellipse.x = rand() % SCREEN_WIDTH + 10;
    ellipse.y = rand() % SCREEN_HEIGHT +10;
    while (ellipse.dansMur(mur) || ellipse.x + ellipse.rayon >= SCREEN_WIDTH || ellipse.y + ellipse.rayon >= SCREEN_HEIGHT || ellipse.x - ellipse.rayon <= 0 || ellipse.y - ellipse.rayon <= 0){
        ellipse.x = rand() % SCREEN_WIDTH + 10;
        ellipse.y = rand() % SCREEN_HEIGHT +10;
    }

    ellipse.randomVitesse();
        if (couleur == "rouge") ellipse.setCouleur(255, 0, 0);
        else if (couleur == "vert") ellipse.setCouleur(0, 255, 0);
        else if (couleur == "bleu") ellipse.setCouleur(0, 0, 255);
        else if (couleur == "jaune") ellipse.setCouleur(255, 255, 0);
        else if (couleur == "cyan") ellipse.setCouleur(0, 255, 255);
        else if (couleur == "magenta") ellipse.setCouleur(255, 0, 255);
        else if (couleur == "blanc") ellipse.setCouleur(255, 255, 255);
        else ellipse.randomCouleur();
    return ellipse;
}

int main(int argc, char** argv) {
    srand(time(NULL));
    SDL_Window* gWindow;
    SDL_Renderer* renderer;
    bool is_running = true; 

    // Création de la fenêtre
    gWindow = init("Awesome Game");

    // Initialisation des acteurs et de la liste
    Liste liste;
    liste.premier = nullptr;
    int nbEllipse = 10;
    Mur mur1;
    mur1.init(rand() % SCREEN_WIDTH + 10, rand() % SCREEN_HEIGHT + 10, rand() % SCREEN_WIDTH /2, rand() % SCREEN_HEIGHT /2);
    if (argc > 1){
        nbEllipse = argc;
        for (int i = 1 ; i < argc ; i++){
            liste.ajouter(generateRandomEllipse(mur1, argv[i]));
        }    
    }  
    else {
        for(int i = 0 ; i < nbEllipse ; i++){
            liste.ajouter(generateRandomEllipse(mur1, ""));
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
