#include "mbed.h"
#include <vector>

#define BUFFER_s 16
#define NUMBER_OF_SLICES 360
#define SLICES_TILL_HALL_AVAILABLE 180

#include "View.h"
#include "Point.h"
#include "EuclidPoint.h"
#include <math.h>
#include "Block.h"

//Class to deal with the physical view

DigitalOut pushRegister(p24);
DigitalOut pushBit(p23);

DigitalOut dataArmOne(p15);
DigitalOut dataArmTwo(p16);
DigitalOut dataArmThree(p17);
DigitalOut dataArmFour(p18);
DigitalOut dataArmFive(p19);
DigitalOut dataArmSix(p20);
DigitalOut dataArmSeven(p21);
DigitalOut dataArmEight(p22);

InterruptIn hallSensor(p25);

View::View() {
    hallSensor.fall(this, &View::sensedRotation);
    firtTime = true;
    currentSlice = 0;
}

void View::sensedRotation() {
    if (firstTime) {
        rotationTime.reset();
        rotationTime.start();
        firstTime = false;
        currentSlice = 180;
        return;
    }
    //ensures hall sensor jitter doesn't affect timer
    if (currentSlice < SLICES_TILL_HALL_AVAILABLE) {
        return;
    }
    rotateTime = rotationTime.read_us();
    rotationTime.reset();
    rotationTime.start();
    sliceTime = (double) rotateTime / NUMBER_OF_SLICES;
    currentSlice = 0;
}

void View::pushData(char bits[16]) {
    for (int i = 8; i < 16; i++) {
        dataArmOne = bits[i] & 0x01;
        dataArmTwo = bits[i] & 0x02;
        dataArmThree = bits[i] & 0x04;
        dataArmFour = bits[i] & 0x08;
        dataArmFive = bits[i] & 0x10;
        dataArmSix = bits[i] & 0x20;
        dataArmSeven = bits[i] & 0x40;
        dataArmEight = bits[i] & 0x80;

        pushBit = 1;
        pushBit = 0;
    }
    for (int i = 7; i >= 0; i--) {
        dataArmOne = bits[i] & 0x01;
        dataArmTwo = bits[i] & 0x02;
        dataArmThree = bits[i] & 0x04;
        dataArmFour = bits[i] & 0x08;
        dataArmFive = bits[i] & 0x10;
        dataArmSix = bits[i] & 0x20;
        dataArmSeven = bits[i] & 0x40;
        dataArmEight = bits[i] & 0x80;

        pushBit = 1;
        pushBit = 0;
    }

    pushRegister = 1;
    pushRegister = 0;
}

void View::nextLedPush() {
    if (current_slice < NUMBER_OF_SLICES) {
        pushData(slice_data[current_slice]);
        current_slice++;
    }
}

void View::resetCount(void) {
    current_slice = 0;
}

void View::resetDisplay(void) {
    for (int i = 0; i < 360; i++) {
        for (int j = 0; j < 16; j++) {
            slice_data[i][j] = 0x00;
        }
    }
}

void View::addPoint(Point pointer) {
    int arrSlice = pointer.getArraySlice();
    char c = pointer.getIdentifyingChar();
    int distance = pointer.getPositionDistance();
    addValue(arrSlice, distance, c);
}

void View::addValue(int arrSlice, int distance, char c) {
    if (distance >= 0 && distance < 16 && arrSlice < 360 && arrSlice >= 0) {
        slice_data[arrSlice][distance] |= c;
    }
}

void View::addFilledEucPoint(EuclidPoint euc) {
    int x = euc.x;
    int y = euc.y;
    Point pointer = euc.getPoint();
    int arrSlice = pointer.getArraySlice();
    char c = pointer.getIdentifyingChar();
    int distance = pointer.getPositionDistance();

    addValue(arrSlice, distance, c);

    int orgDegree = pointer.getDegree();
    int degree = orgDegree;
    int counter = 0;
    while (isAtPoint(distance + 2, degree, x, y) && counter < 15) {
        int newSlice = (arrSlice + counter) % 360;
        addValue(newSlice, distance, c);
        degree++;
        counter++;
    }
    degree = pointer.getDegree();
    while (isAtPoint(distance + 2, degree, x, y) && counter > -15) {
        int newSlice = (arrSlice + counter) % 360;
        addValue(newSlice, distance, c);
        degree--;
        counter--;
    }
}

void View::addEucPoint(EuclidPoint euc) {
    int x = euc.x;
    int y = euc.y;
    Point pointer = euc.getPoint();
    int arrSlice = pointer.getArraySlice();
    char c = pointer.getIdentifyingChar();
    int distance = pointer.getPositionDistance();
    addValue(arrSlice, distance, c);
}

bool View::isAtPoint(int radius, int degree, int x, int y) {
    return (y == rint((double) radius * sin(degree / 57.2957)) && x == rint((double) radius * cos(degree / 57.2957)));
}

void View::drawSquare(int x, int y, int z, int size) {
    for (int i = 0; i < size; i++) {
        addEucPoint(EuclidPoint(x + i, y, z));
        addEucPoint(EuclidPoint(x, y + i, z));
        addEucPoint(EuclidPoint(x + size, y + i, z));
        addEucPoint(EuclidPoint(x + i, y + size, z));
    }
}

void View::drawLine(int x, int y, int z, int size) {
    for (int i = 0; i < size; i++) {
        addEucPoint(EuclidPoint(x, y, z + i));
    }
}

void View::addBlock(Block block) {
    drawSquare(block.x, block.y, block.z, block.size);
    drawSquare(block.x, block.y, block.z + block.height, block.size);
    drawLine(block.x, block.y, block.z, block.height);
    drawLine(block.x + block.size, block.y, block.z, block.height);
    drawLine(block.x, block.y + block.size, block.z, block.height);
    drawLine(block.x + block.size, block.y + block.size, block.z, block.height);
}







