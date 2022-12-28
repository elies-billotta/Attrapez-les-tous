#include "Cellule.h"
#include "ellipse.h"
#include "Liste.h"

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