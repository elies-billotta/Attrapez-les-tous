#include "Cellule.h"
#include "ellipse.h"
#include "Liste.h"
#include "SDL2_gfxPrimitives.h"
#include <iostream>
using namespace std;

void Liste::ajouter(Ellipse e){
    Cellule *nouvelleCellule = new Cellule;
    nouvelleCellule->ellipse = e;
    nouvelleCellule->suivant = nullptr;
    if (premier != nullptr)
    {
        Cellule *celluleActuelle = premier;
        while (celluleActuelle->suivant != nullptr)
        {
            celluleActuelle = celluleActuelle->suivant;
        }
        celluleActuelle->suivant = nouvelleCellule;
    }
    else
    {
        premier = nouvelleCellule;
    }
}


void Liste::supprimer(Ellipse e){
    Cellule *celluleActuelle = premier;
    Cellule *cellulePrecedente = nullptr;
    while (celluleActuelle != nullptr)
    {
        if (celluleActuelle->ellipse.x == e.x && celluleActuelle->ellipse.y == e.y)
        {
            if (cellulePrecedente != nullptr) cellulePrecedente->suivant = celluleActuelle->suivant;
            else premier = celluleActuelle->suivant;
            delete celluleActuelle;
            break;
        }
        cellulePrecedente = celluleActuelle;
        celluleActuelle = celluleActuelle->suivant;
    }
}

void Liste::draw(SDL_Renderer* renderer)
{
    Cellule *celluleActuelle = premier;
    while (celluleActuelle != nullptr)
    {
        Ellipse e = celluleActuelle->ellipse;
        filledEllipseRGBA(renderer, e.x, e.y, e.rayon, e.rayon, e.r, e.g, e.b, 255);
        celluleActuelle = celluleActuelle->suivant;
    }

}

