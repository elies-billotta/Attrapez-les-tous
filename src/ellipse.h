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

    void deplacer(int SCREEN_HEIGHT, int SCREEN_WIDTH);
};

#endif
