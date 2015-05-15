
#include "Point.h"
//*********************point class************************//

Point :: Point (void){
    positionRadian = 90;
    positionHeight = 4;
    positionDistance = 8;
    offAngles[0] = -6;
    offAngles[1] = 174;
    offAngles[2] = 44;
    offAngles[3] = 228;
    offAngles[4] = 92;
    offAngles[5] = 275;
    offAngles[6] = 145;
    offAngles[7] = 323;
    //Point(90, 4, 8);
}

Point :: Point (int posRadian, int posHeight, int posDistance){
    positionRadian = posRadian;
    positionHeight = posHeight;
    positionDistance = posDistance;
    offAngles[0] = -6;
    offAngles[1] = 174;
    offAngles[2] = 44;
    offAngles[3] = 228;
    offAngles[4] = 92;
    offAngles[5] = 275;
    offAngles[6] = 145;
    offAngles[7] = 323;
}    

int Point :: getArraySlice (void){
    return ((positionRadian + offAngles[positionHeight])%360);
}
int Point :: getDegree (void){
    return positionRadian % 360;
}
char Point :: getIdentifyingChar(void){
    return 0x01 << positionHeight;
}
int Point :: getPositionDistance(void){
    return positionDistance;
}
void Point :: moveUp(){
    if (positionHeight < 7){
        positionHeight ++;
    }
}
void Point :: moveDown(){
    if(positionHeight > 0){
        positionHeight --;
    }
}        
void Point :: rotateRight(){
    positionRadian = (positionRadian + 1) % 360;
}
void Point :: rotateLeft(){
    positionRadian = (positionRadian - 1) % 360;
}
void Point :: moveIn(){
    if (positionDistance > 0){
        positionDistance --;
    }
}
void Point :: moveOut(){
    if (positionDistance < 15){
        positionDistance ++;
    }
}