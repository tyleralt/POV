#ifndef VIEW
#define VIEW

#include "mbed.h"
#include <vector>

#define BUFFER_SIZE 16
#define NUMBER_OF_SLICES 360

#include "Point.h"
#include "EuclidPoint.h"
#include "Block.h"

class View {
private:

    Timer rotationTime;
    Ticker updateLeds;
    char sliceData[360][16]; //[slice][specific led distance] (0 is closest) & with appropriate bit for each arm
    double sliceTime;
    double rotateTime;
    int currentSlice = 0;
    bool firstTime = true;

    void pushData(char [16]);

    void sensedRotation();

    bool isAtPoint(int, int, int, int);

    void nextLedPush(void);

    void resetCount(void);

    void setCurrentSlice(int);

public :

    void resetDisplay(void);

    void addPoint(Point);

    void addFilledEucPoint(EuclidPoint);

    void addEucPoint(EuclidPoint);

    void addBlock(Block);

    void drawSquare(int, int, int, int);

    void drawLine(int, int, int, int);

    void addValue(int, int, char);
};

#endif
