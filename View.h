#include "mbed.h"
#include <vector>
#define BUFFER_SIZE 16
#define NUMBER_OF_SLICES 360
#include "Point.h"
#include "EuclidPoint.h"
#include "Block.h"

class View {   

    
//Declare global vars
    char slice_data [360][16]; //[slice][specific led distance] (0 is closest) & with approppriate bit for each arm 
     
     void pushData(char [16]);
    public :
    int current_slice;
    View();
    bool isAtPoint(int, int, int, int);
    void nextLedPush(void);
    void resetCount(void);
    void resetDisplay(void);
    void setCurrentSlice(int);
    void addPoint(Point);
    void addFilledEucPoint(EuclidPoint);
    void addEucPoint(EuclidPoint);
    void addBlock(Block);
    void drawSquare (int, int, int, int);
    void drawLine(int, int, int, int);
    void addValue(int, int, char);
};