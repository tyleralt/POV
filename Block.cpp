
#include "Block.h"
//*********************point class************************//

Block :: Block (int xi, int yi, int zi, int sizei, int heighti){
    x = xi;
    y = yi;
    z = zi;
    size = sizei;
    height = heighti;
}
Block :: Block (){
    x = 0;
    y = 0;
    z = 0;
    size = 0;
    height = 0;
}


void Block :: moveRight(){
    x = (x + 1);
}
void Block :: moveLeft(){
    x = (x - 1);
}
void Block :: moveIn(){
    y--;
}
void Block :: moveOut(){
    y++;
}