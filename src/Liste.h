
#include "Cellule.h"
#include "ellipse.h"

#ifndef LISTE_CPP
#define LISTE_CPP

struct Liste{
    Cellule *premier;

    void ajouter(Ellipse e);

    void supprimer(Ellipse e);

    void draw(SDL_Renderer *renderer);
};

#endif