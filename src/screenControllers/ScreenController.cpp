#include "ScreenController.h"
#include "View.h"

ScreenController::ScreenController(View& inputView, Serial& inputSerial){
    view = inputView;
    serial = inputSerial;
}
