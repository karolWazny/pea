#ifndef SDIZO_1_STOPWATCH_H
#define SDIZO_1_STOPWATCH_H

#include <windows.h>

class StopWatch {
public:
    StopWatch();
    void start();
    void stop();
    [[nodiscard]] unsigned long long getLastMeasurmentPiccosec() const;
    [[nodiscard]] long double getLastMeasurementsFloat() const;
private:
    LARGE_INTEGER startStamp;
    LARGE_INTEGER stopStamp;
    LARGE_INTEGER frequency;
    LARGE_INTEGER timeElapsedPiccosec;
    long double timeElapsedDouble;
};


#endif //SDIZO_1_STOPWATCH_H
