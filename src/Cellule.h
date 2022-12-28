#ifndef CELLULE_H
#define CELLULE_H

#include "ellipse.h"

struct Cellule {
    Ellipse ellipse;
    Cellule *suivant;
};


#endif

