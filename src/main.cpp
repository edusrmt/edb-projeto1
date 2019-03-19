#include "../include/search.h"
#include "../include/util.h"

using namespace search;
using namespace util;

void print_step (long int vector[], int first, int last) {
    // Prints out the original data container.
    std::cout << "Array: [ ";
    for (int i = first; i <= last; i++)
        std::cout << vector[i] << " ";    

    std::cout << "]\n";
}

int main(int argc, char *argv[]) {
    std::string select = argv[1];
    int minSize = std::stoi(argv[2]);
    int maxSize = std::stoi(argv[3]);
    int samplesAmount = std::stoi(argv[4]);
    int testsAmount = std::stoi(argv[5]);

    IterativeFunction *iterativeFunctions[] = {lsearch, bsearch, tsearch, jsearch, fsearch};
    RecursiveFunction *recursiveFunctions[] = {bsearch, tsearch};

    writeHeader();
    writeAmount(minSize, maxSize, samplesAmount);
    for(int i = 0; i < 7; ++i) {
        if(select[i] == '1') {
            if(i < 5) {
                callbackFunction(iterativeFunctions[i], minSize, maxSize, samplesAmount, testsAmount, i);
            } else {
                callbackFunction(recursiveFunctions[i-5], minSize, maxSize, samplesAmount, testsAmount, i);
            }
        } else {
            writeBlank(i, minSize, maxSize, samplesAmount);
        }
    }

    return 0;
}