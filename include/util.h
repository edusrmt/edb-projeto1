#ifndef UTIL
#define UTIL

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <new>
#include <math.h>
#include <chrono>
#include <limits>

namespace util {
    typedef int IterativeFunction(long int vector[], int last, long int value);
    typedef int RecursiveFunction(long int vector[], int first, int last, long int value);

    void writeHeader();
    void writeAmount(int minSize, int maxSize, int samplesAmount);
    void writeInFile(int algorithmIndex, std::string value, int lineCount);
    void writeBlank(int algorithmIndex, int minSize, int maxSize, int samplesAmount);
    void callbackFunction(long int *A, IterativeFunction *function, int minSize, int maxSize, int samplesAmount, int testsAmount, int algorithmIndex);
    void callbackFunction(long int *A, RecursiveFunction *function, int minSize, int maxSize, int samplesAmount, int testsAmount, int algorithmIndex);
}
#endif
