
#include "Cellule.h"
#include "ellipse.h"

#ifndef LISTE_CPP
#define LISTE_CPP

struct Liste{
    Cellule *premier;

    void ajouter(Ellipse e);
};

#endif