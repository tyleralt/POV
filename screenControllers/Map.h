#ifndef MAP
#define MAP

#include "ScreenController.h"
#include "Block.h"
#include "View.h"


class Map : public ScreenController {
private:
    Block blocks[8];

    void updateMap();
    void handleKeyPress();
    void serialInterupt();
public:
    Map (View, Serial);
};
#endif
