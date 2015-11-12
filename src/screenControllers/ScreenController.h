#ifndef SCREEN_CONTROLLER
#define SCREEN_CONTROLLER
#include "View.h"
class ScreenController{
    public :
    ScreenController(View, Serial);
    void activate() = 0;
    void deactivate() = 0;

    protected :
    View view;
    Serial serial;
};
#endif
