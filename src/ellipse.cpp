#include "ellipse.h"
#include <iostream>
using namespace std;

bool Ellipse::checkCollisionY()
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = 0;
    rightA = 0 + 200;
    topA = 150;
    bottomA = 150 + 150;

    //Calculate the sides of rect B
    leftB = this->x - this->rayon;
    rightB = this->x + this->rayon;
    topB = this->y - this->rayon;
    bottomB = this->y + this->rayon;
     //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}



int randomNumber();

void Ellipse::setVitesse(int vx, int vy){
    if (vx == 0 && vy == 0){
        this->randomVitesse();
    }
    else{
        this->vx = vx;
        this->vy = vy;
    }
}

void Ellipse::randomVitesse(){ 
    this->vx = randomNumber();
    this->vy =  randomNumber();
}

int randomNumber(){
    int rnd = rand() % 10 - 5; 
    while (rnd == 0){
        rnd = rand() % 10 - 5;
    }
    return rnd;
}

void Ellipse::deplacer(int SCREEN_HEIGHT, int SCREEN_WIDTH){
    this->x += this->vx;
    this->y += this->vy;
    

    if (this->x + this->rayon >= SCREEN_WIDTH || this->x - this->rayon <= 0 ){
        this->vx = -this->vx;
    }
    if (this->y + this->rayon >= SCREEN_HEIGHT || this->y - this->rayon <= 0 ){
        this->vy = -this->vy;
    }

    int leftA = 0;
    int rightA = 0 + 200;
    int topA = 150;
    int bottomA = 150 + 150;

    if(checkCollisionY()){
        if(this->x > leftA + rightA  && this->y > topA + bottomA ) {
            this->vx = -this->vx;
            this->vy = -this->vy;
        }
        else if(this->x < leftA && this->y > topA + bottomA) {
            this->vx = -this->vx;
            this->vy = -this->vy;
        }
        else if(this->x > leftA + rightA && this->y < topA){
            this->vx = -this->vx;
            this->vy = -this->vy;
        }
        else if(this->x < leftA && this->y < topA) {
            this->vx = -this->vx;
            this->vy = -this->vy;
        }
        
        else if(this->x > leftA + rightA) {
            this->vx = -this->vx;
        }
        else if(this->x   < leftA) {
            this->vx = -this->vx;
        }
        else if(this->y < topA){
            this->vy = -this->vy;
        }
        else if(this->y   < topA + bottomA) {
            this->vy = -this->vy;
        }

        
    }

    
}

void Ellipse::randomCouleur(){
    this->r = rand() % 255;
    this->g = rand() % 255;
    this->b = rand() % 255;
}

bool Ellipse::clic(int x, int y){
    if (x >= this->x - this->rayon && x <= this->x + this->rayon && y >= this->y - this->rayon && y <= this->y + this->rayon){
        return true;
    }
    return false;
}

void Ellipse::setCouleur(int r, int g, int b){
    this->r = r;
    this->g = g;
    this->b = b;
}