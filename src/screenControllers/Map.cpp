#include "Map.h"
#include "View.h"
#include "ScreenController.h"

Map::Map(View inputView, Serial inputSerial) : ScreenController(viewI) {
    blocks[0] = Block(3, 4, 0, 4, 6);
    blocks[1] = Block(-4, -4, 1, 4, 3);
    blocks[2] = Block(5, -7, 2, 5, 4);
    blocks[3] = Block(-5, 5, 0, 3, 7);
    blocks[4] = Block(15, 8, 1, 4, 6);
    blocks[5] = Block(15, -4, 0, 5, 7);
    blocks[6] = Block(22, -7, 2, 6, 4);
    blocks[7] = Block(21, 5, 2, 4, 4);
    ScreenController(inputView, inputSerial);
}

void Map::serialInterupt() {
    handleKeyPress(serial.getc());
}

void Map::activate() {
    view.resetDisplay();
    serial.attach(&Map::serialInterupt);
}

void Map::deactivate() {
    view.resetDisplay();
    serial.attach(0);
}

void Map::updateMap() {
    view.resetDisplay();
    view.addBlock(blocks[0]);
    view.addBlock(blocks[1]);
    view.addBlock(blocks[2]);
    view.addBlock(blocks[3]);
    view.addBlock(blocks[4]);
    view.addBlock(blocks[5]);
    view.addBlock(blocks[6]);
    view.addBlock(blocks[7]);
}

void Map::handleKeyPress(char c) {
    switch (c) {
        case 'w':
            for (int i = 0; i < 8; i++) {
                blocks[i].moveOut();
            }
            updateMap();
            break;
        case 's':
            for (int i = 0; i < 8; i++) {
                blocks[i].moveIn();
            }
            updateMap();
            break;
        case 'a':
            for (int i = 0; i < 8; i++) {
                blocks[i].moveLeft();
            }
            updateMap();
            break;
        case 'd':
            for (int i = 0; i < 8; i++) {
                blocks[i].moveRight();
            }
            updateMap();
            break;
        default:
            return;
    }
}

