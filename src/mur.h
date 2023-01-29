#include "ellipse.h"
#include "point.h"
#include "application_ui.h"

#ifndef MUR_H
#define MUR_H

struct Mur{
    int x;
    int y;
    int w;
    int h;
    SDL_Rect rect;

    void init(int x, int y, int w, int h);

    void draw(SDL_Renderer* renderer);

    bool clic(int x, int y);
    

};
#endif