#include "ellipse.h"
#include <iostream>
using namespace std;

void Ellipse::deplacer(int SCREEN_HEIGHT, int SCREEN_WIDTH){
    this->x += this->vx;
    this->y += this->vy;

    if (this->x + this->rayon >= SCREEN_WIDTH || this->x - this->rayon <= 0){
        this->vx = -this->vx;
    }
    if (this->y + this->rayon >= SCREEN_HEIGHT || this->y - this->rayon <= 0){
        this->vy = -this->vy;
    }
}