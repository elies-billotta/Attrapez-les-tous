#ifndef ELLIPSE_H
#define ELLIPSE_H

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

    void deplacer(int SCREEN_HEIGHT, int SCREEN_WIDTH);

    void randomCouleur();

    bool clic(int x, int y);


};

#endif
