#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <new>
#include <math.h>
#include <chrono>
#include <limits>

void print_step (long int vector[], int first, int last) {
    // Prints out the original data container.
    std::cout << "Array: [ ";
    for (int i = first; i <= last; i++)
        std::cout << vector[i] << " ";    

    std::cout << "]\n";
}

int lsearch(long int vector[], int last, long int value) {
    for (int i = 0; i <= last; i++) {
        if (vector[i] == value)
            return i;
    }

    return -1;
}

int lsearch(long int vector[], int first, int last, long int value) {
    for (int i = first; i <= last; i++) {
        if (vector[i] == value)
            return i;
    }

    return -1;
}

int bsearch(long int vector[], int last, long int value) {
    int first = 0;
    int length = last + 1;

    while (first <= last) {
        int middle = length / 2 + first;

        if (vector[middle] == value)
            return middle;
        else if (vector[middle] < value)
            first = middle + 1;
        else {
            last = middle - 1;
        }

        length = last - first + 1;
    }

    return -1;
}

int bsearch(long int vector[], int first, int last, long int value) {
    int length = last - first + 1;

    if (first <= last) {
        int middle = length / 2 + first;

        if (vector[middle] == value)
            return middle;
        else {
            if (vector[middle] < value)
                first = middle + 1;
            else
                last = middle - 1;

            return bsearch(vector, last, value, first);
        }
    }

    return -1;
}

int tsearch(long int vector[], int last, long int value) {
    int first = 0;
    int length = last + 1;

    while (first <= last) {
        int indexA = length / 3 + first;

        if (vector[indexA] == value)
            return indexA;
        else if (vector[indexA] > value)
            last = indexA - 1;
        else {
            int indexB = 2 * length / 3 + first;
            first = indexA + 1;

            if (vector[indexB] == value)
                return indexB;
            else if (vector[indexB] < value)
                first = indexB + 1;
            else
                last = indexB - 1;
        }

        length = last - first + 1;
    }
    
    return -1;
}

int tsearch(long int vector[], int first, int last, long int value) {
    int length = last - first + 1;

    if (first <= last) {
        int indexA = length / 3 + first;

        if (vector[indexA] == value)
            return indexA;
        else {
            if (vector[indexA] > value)
                last = indexA - 1;
            else {
                int indexB = 2 * length / 3 + first;
                first = indexA + 1;

                if (vector[indexB] == value)
                    return indexB;
                else if (vector[indexB] < value)
                    first = indexB + 1;
                else
                    last = indexB - 1;
            }

            return tsearch(vector, last, value, first);
        }

        length = last - first + 1;
    }
    
    return -1;
}

int jsearch(long int vector[], int last, long int value) {
    int jump = sqrt(last+1);
    int preIndex = 0;
    int curIndex = jump;

    while (curIndex <= last) {    
        if(vector[curIndex] == value)
            return curIndex;
        else if (vector[curIndex] > value)
            return lsearch(vector, curIndex, value, preIndex);
        else {
            preIndex = curIndex;
            curIndex += jump;
        }
    }

    return -1;
}

int fsearch(long int vector[], int last, long int value) {
    int first = 0;

    while(first <= last) {
        int a = 1;
        int b = 1;

        while(last - first + 1 > b){
            int c = a;
            a = b;
            b += c;
        }

        int split = b - a + first;

        if (vector[split] == value)
            return vector[split];
        else if (vector[split] < value)
            first = split + 1;
        else 
            last = split - 1;
               
    }

    return -1;
}

long int * generateArray(int size) {
    long int *array = new (std::nothrow) long int[size];
    if(array == nullptr) 
        std::cout << "Failed to create array" << std::endl;
    else {
        for(int i = 0; i < size; ++i) {
            array[i] = i;
        }
    }
    return array;
}

typedef int IterativeFunction(long int vector[], int last, long int value);
typedef int RecursiveFunction(long int vector[], int first, int last, long int value);

void callbackFunction(IterativeFunction *function, int minSize, int maxSize, int samplesAmount, int testsAmount) {
    float step = (maxSize - minSize)/(samplesAmount - 1);
    float currentSize = minSize;
    while((int) currentSize <= maxSize) {
        long int *A = generateArray((int) currentSize);    
        
        double sum = 0;
        for(int i = 0; i < testsAmount; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            int result = (*function)(A, ((int) currentSize) - 1, maxSize); 
            auto end = std::chrono::high_resolution_clock::now();

            double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            sum += duration;
        }
        
        double avg = (sum/testsAmount) * 1e-6;

        std::cout.precision(std::numeric_limits<double>::max_digits10);
        std::cout << "Current size: " << currentSize << " -> T: " << avg << std::endl;
        currentSize += step;
    }

    std::cout << std::endl;
}

void callbackFunction(RecursiveFunction *function, int minSize, int maxSize, int samplesAmount, int testsAmount) {
    float step = (maxSize - minSize)/(samplesAmount - 1);
    float currentSize = minSize;
    while((int) currentSize <= maxSize) {
        long int *A = generateArray((int) currentSize);    
        
        double sum = 0;
        for(int i = 0; i < testsAmount; i++) {
            auto start = std::chrono::high_resolution_clock::now();
            int result = (*function)(A, ((int) currentSize) - 1, maxSize, 0); 
            auto end = std::chrono::high_resolution_clock::now();

            double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

            sum += duration;
        }
        
        double avg = (sum/testsAmount) * 1e-6;

        std::cout.precision(std::numeric_limits<double>::max_digits10);
        std::cout << "Current size: " << currentSize << " -> T: " << avg << std::endl;
        currentSize += step;
    }

    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    std::string select = argv[1];
    int minSize = std::stoi(argv[2]);
    int maxSize = std::stoi(argv[3]);
    int samplesAmount = std::stoi(argv[4]);
    int testsAmount = std::stoi(argv[5]);

    IterativeFunction *iterativeFunctions[] = {lsearch, bsearch, tsearch, jsearch, fsearch};
    RecursiveFunction *recursiveFunctions[] = {bsearch, tsearch};

    for(int i = 0; i < 7; ++i) {
        if(select[i] == '1') {
            if(i < 5) 
                callbackFunction(iterativeFunctions[i], minSize, maxSize, samplesAmount, testsAmount);
            else 
                callbackFunction(recursiveFunctions[i-4], minSize, maxSize, samplesAmount, testsAmount);
        }
    }

    return 0;
}