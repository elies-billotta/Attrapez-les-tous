#ifndef ELLIPSE_H
#define ELLIPSE_H
#include "mur.h"
#include <iostream>
#include <string>
struct Ellipse
{
    int x;
    int y;
    int vx;
    int vy;
    int rayon;
    unsigned int r;
    unsigned int g;
    unsigned int b;

    void setVitesse(int vx, int vy);

    void randomVitesse();

    void deplacer(int SCREEN_HEIGHT, int SCREEN_WIDTH, Mur mur);

    void randomCouleur();

    bool clic(int x, int y);

    void setCouleur(int r, int g, int b);

    std::string collision(Mur mur);
};

#endif
