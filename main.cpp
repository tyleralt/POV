#include "mbed.h"
#include <vector>
#define BUFFER_ 16
#define NUMBER_OF_SLICES 360
#include "Point.h"
#include "View.h"
#include "Block.h"


//hass sensor interupt
InterruptIn hallSensor(p25);

//Set Up Timer and ticker
Timer rotationTime;
Ticker updateLeds;

//Declare global vars
double slice_time;
double rotate_time; 
int current_slice;
bool firstTime;

enum DisplayMode {lineDraw, map, eucDraw};

DisplayMode mode; 

Point pointer;
EuclidPoint eucPointer;
//the View
View display;

Block blocks [8];



//serial port for pc and bluetooth
Serial pc(USBTX, USBRX); // tx, rx
Serial bt(p9, p10);// tx, rx

void updateMap(){
    display.resetDisplay();
    display.addBlock(blocks[0]);
    display.addBlock(blocks[1]);
    display.addBlock(blocks[2]);
    display.addBlock(blocks[3]);
    display.addBlock(blocks[4]);
    display.addBlock(blocks[5]);
    display.addBlock(blocks[6]);
    display.addBlock(blocks[7]);
}

void rotate_sense(){
  if (firstTime){
    rotationTime.reset();
    rotationTime.start();
    firstTime = false;
    display.current_slice = 180;
    return;
  }
    if(display.current_slice < NUMBER_OF_SLICES / 4){
      return;
    }
    rotate_time = rotationTime.read_us();
    rotationTime.reset();    
    rotationTime.start();
    slice_time = (double) rotate_time/NUMBER_OF_SLICES;
    display.resetCount();
    updateLeds.attach_us(&display, &View::nextLedPush, slice_time);
}   
 void moveUp();
    void moveDown();
    void rotateRight();
    void rotateLeft();
    void moveIn();
    void moveOut();

void parseLineMode(char c){
    switch(c){
        case 'w': 
            pointer.moveOut();
            break;
        case 's':
            pointer.moveIn();
            break;
        case 'a':
            pointer.rotateRight();
            break;
        case 'd':
            pointer.rotateLeft();
            break;
        case 'p':
            pointer.moveUp();
            break;
        case 'l':
            pointer.moveDown();
            break;
        default: return;
    }
    display.addPoint(pointer);
}

void parseMapMode(char c){
    switch(c){
        case 'w': 
        for (int i = 0; i < 8; i ++){
            blocks[i].moveOut();
        }
        updateMap();
            break;
        case 's':
        for (int i = 0; i < 8; i ++){
            blocks[i].moveIn();
        }
        updateMap();
            break;
        case 'a':
        for (int i = 0; i < 8; i ++){
            blocks[i].moveLeft();
        }
        updateMap();
            break;
        case 'd':
        for (int i = 0; i < 8; i ++){
            blocks[i].moveRight();
        }
        updateMap();
            break;
        case 'p':
        return;
        case 'l':
        return;
        default: return;
    }
}
void parseEucMode(char c){
        switch(c){
        case 'w': 
            eucPointer.moveAway();
            break;
        case 's':
            eucPointer.moveTowards();
            break;
        case 'a':
            eucPointer.moveLeft();
            break;
        case 'd':
            eucPointer.moveRight();
            break;
        case 'p':
            eucPointer.moveUp();
            break;
        case 'l':
            eucPointer.moveDown();
            break;
        default: return;
    }
    display.addFilledEucPoint(eucPointer);
}

void parseBt(char c){
    if (c == 'm'){
        display.resetDisplay();
        switch (mode){
            case(lineDraw):{
                mode = eucDraw;
                bt.printf("we are drawing Euclidian");
                break;
                }
            case(map):{
                mode = lineDraw;
                bt.printf("we are drawing Radians");
                break;
                }
            case(eucDraw):{
                mode = map;
                bt.printf("we are on a Map");
                updateMap();
                break;
                }
            default: {
                return;
            }
        }
        return;
    }
    
    if (mode == lineDraw){
        parseLineMode(c);
    }
    if (mode == map){
        parseMapMode(c);
    }
    if (mode == eucDraw){
        parseEucMode(c);
    }
}
        


int main() {
    blocks[0] = Block( 3, 4, 0, 4,6);
    blocks[1] = Block ( -4, -4, 1 ,4, 3);
    blocks[2] = Block ( 5, -7, 2 ,5, 4);
    blocks[3] = Block (-5, 5, 0, 3, 7);
    blocks[4] = Block( 15, 8, 1, 4,6);
    blocks[5] = Block ( 15, -4, 0 ,5, 7);
    blocks[6] = Block ( 22, -7, 2 ,6, 4);
    blocks[7] = Block (21, 5, 2, 4, 4);
    
    pc.printf("started");
    bt.printf("bluetooth started");
    mode = eucDraw;
    firstTime = true;
    current_slice = 100;
    display.resetDisplay();
    
    hallSensor.fall(&rotate_sense);

    while(true) {
        if (bt.readable()){
            parseBt(bt.getc());
        }
    }
}
