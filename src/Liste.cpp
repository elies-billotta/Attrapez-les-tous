#include "Cellule.h"
#include "ellipse.h"
#include "Liste.h"
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
            if (cellulePrecedente != nullptr)
            {
                cellulePrecedente->suivant = celluleActuelle->suivant;
            }
            else
            {
                premier = celluleActuelle->suivant;
            }
            delete celluleActuelle;
            break;
        }
        cellulePrecedente = celluleActuelle;
        celluleActuelle = celluleActuelle->suivant;
    }
}

//print list
void Liste::printList(){
    Cellule *celluleActuelle = premier;
    while (celluleActuelle != nullptr)
    {
        cout << celluleActuelle->ellipse.x << " " << celluleActuelle->ellipse.y << endl;
        celluleActuelle = celluleActuelle->suivant;
    }
}

