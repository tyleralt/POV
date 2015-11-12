#include "mbed.h"
#include <vector>
#define BUFFER_ 16
#define NUMBER_OF_SLICES 360
#include "View.h"
#include "screenControllers/ScreenController.h"

//the View
View display;

int currentScreenController;
//serial port for pc and bluetooth
Serial pc(USBTX, USBRX); // tx, rx
Serial bt(p9, p10);// tx, rx
Serial masterSerialCopy(p9, p10);
vector<ScreenController> screenControllers;


void parseBt(){
    char c = masterSerialCopy.getc();
    if (c == 'm'){
      changeDisplayMode();
    }
}

void changeDisplayMode(){
    screenControllers[currentScreenController].deactivate();
    currentScreenController = (currentScreenController + 1) % currentScreenController.size();
    currentScreenController[currentScreenController].activate();
}

void initializeDisplayModes(){
    screenControllers.insert(new Map(display, bt));
}

int main() {

    pc.printf("comptuer connection up");
    bt.printf("bluetooth connection up");

    initializeDisplayModes();

    display = new View();
    masterSerialCopy.attach(&parseBt);

}
