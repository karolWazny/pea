#include "StopWatch.h"

StopWatch::StopWatch() {
    QueryPerformanceFrequency(&frequency);
}

void StopWatch::start() {
    QueryPerformanceCounter(&startStamp);
}

void StopWatch::stop() {
    unsigned multiplier = 100000;
    QueryPerformanceCounter(&stopStamp);
    timeElapsedDouble = stopStamp.QuadPart - startStamp.QuadPart;
    timeElapsedPiccosec.QuadPart = stopStamp.QuadPart - startStamp.QuadPart;
    timeElapsedPiccosec.QuadPart *= multiplier;//10^6 daje czas w mikrosekundach, 10^12 to piko
    timeElapsedDouble *= multiplier;
    timeElapsedPiccosec.QuadPart /= frequency.QuadPart;
    timeElapsedDouble /= frequency.QuadPart;
}

unsigned long long StopWatch::getLastMeasurmentPiccosec() const {
    return timeElapsedPiccosec.QuadPart;
}

long double StopWatch::getLastMeasurementsFloat() const {
    return timeElapsedDouble;
}
