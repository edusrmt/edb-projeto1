#include "../include/search.h"
#include "../include/util.h"

using namespace search;
using namespace util;

int main(int argc, char *argv[]) {
    std::string select = argv[1];
    int minSize = std::stoi(argv[2]);
    int maxSize = std::stoi(argv[3]);
    int samplesAmount = std::stoi(argv[4]);
    int testsAmount = std::stoi(argv[5]);

    long int *array = new (std::nothrow) long int[maxSize];
    if(array == nullptr) 
        std::cout << "Failed to create array" << std::endl;
    else {
        for(int i = 0; i < maxSize; ++i)
            array[i] = i;
    }

    IterativeFunction *iterativeFunctions[] = {lsearch, bsearch, tsearch, jsearch, fsearch};
    RecursiveFunction *recursiveFunctions[] = {bsearch, tsearch};
    
    writeHeader();
    writeAmount(minSize, maxSize, samplesAmount);
    for(int i = 0; i < 7; ++i) {
        if(select[i] == '1') {
            if(i < 5) {
                callbackFunction(array, iterativeFunctions[i], minSize, maxSize, samplesAmount, testsAmount, i);
            } else {
                callbackFunction(array, recursiveFunctions[i-5], minSize, maxSize, samplesAmount, testsAmount, i);
            }
        } else {
            writeBlank(i, minSize, maxSize, samplesAmount);
        }
    }

    delete[] array;
    return 0;
}