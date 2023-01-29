#include "ellipse.h"
#include <iostream>
#include <string>
#include "mur.h"
using namespace std;

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

void Ellipse::deplacer(int SCREEN_HEIGHT, int SCREEN_WIDTH, Mur mur){
    this->x += this->vx;
    this->y += this->vy;
    if (this->x + this->rayon >= SCREEN_WIDTH || this->x - this->rayon <= 0 ){
        this->vx = -this->vx;
    }
    if (this->y + this->rayon >= SCREEN_HEIGHT || this->y - this->rayon <= 0 ){
        this->vy = -this->vy;
    }
    
    if (collision(mur) != ""){
        cout << collision(mur) << endl;
        if (collision(mur) == "gauche" || collision(mur) == "droite"){
            this->vx = -this->vx;
        }
        if (collision(mur) == "haut" || collision(mur) == "bas"){
            this->vy = -this->vy;
        }
        if (collision(mur) == "coin"){
            this->vx = -this->vx;
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

std::string Ellipse::collision(Mur mur){
    if (this->x + this->rayon >= mur.x && this->x - this->rayon <= mur.x + mur.w && this->y + this->rayon >= mur.y && this->y - this->rayon <= mur.y + mur.h){
        if (this->x + this->rayon >= mur.x && this->x - this->rayon <= mur.x + mur.w /2){
            if (this->y + this->rayon >= mur.y && this->y - this->rayon <= mur.y + mur.h / 2){
                return "haut";
            }
            else{
                return "bas";
            }
        }
        else{
            if (this->x + this->rayon >= mur.x && this->x - this->rayon <= mur.x + mur.w / 2){
                return "gauche";
            }
            else{
                return "droite";
            }
        }
        if (this->x + this->rayon == mur.x && this->y + this->rayon == mur.y || this->x + this->rayon == mur.x && this->y - this->rayon == mur.y + mur.h || this->x - this->rayon == mur.x + mur.w && this->y + this->rayon == mur.y || this->x - this->rayon == mur.x + mur.w && this->y - this->rayon == mur.y + mur.h){ 
            return "coin";
        }
    }
    return "";
}
