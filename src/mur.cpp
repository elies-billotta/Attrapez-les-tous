#include "mur.h"
#include "application_ui.h"
#include "ellipse.h"
#include <iostream>
using namespace std;

void Mur::init(int x, int y, int w, int h)
{
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    rect = {x, y, w, h};
}

void Mur::draw(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &rect);
}