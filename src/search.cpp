#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <new>
#include <math.h>
#include <chrono>
#include <limits>
#include <vector>

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

            return bsearch(vector, first, last, value);
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

            return tsearch(vector, first, last, value);
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

void writeHeader() {
    std::ofstream records("../data/tempos3.txt", std::ios::in | std::ios::out | std::ios::trunc);
    std::vector<std::string> headerItems = {"# N", "ILS", "IBS", "ITS", "IJS", "IFS", "RBS", "RTS"};
    std::stringstream header;

    for(const auto &s : headerItems) {
        header << s;
        header << std::setfill(' ') << std::setw(11 - s.size()) << "";
    }

    records << header.str() << std::endl;
}

void writeAmount(int minSize, int maxSize, int samplesAmount) {
    std::ofstream records("../data/tempos3.txt", std::ios::in | std::ios::out | std::ios::binary);
    float step = (maxSize - minSize)/(samplesAmount - 1);
    float currentSize = minSize;
    
    int lineCount = 0;
    while((int) currentSize <= maxSize) {
        if(records.is_open()) {
            int lineJump = (lineCount+1) * 89;
            std::stringstream value;
            std::stringstream line;

            records.seekp(lineJump, std::ios::beg);
            
            value << std::setprecision(std::numeric_limits<double>::max_digits10) << currentSize;

            line << value.str() << std::setfill(' ') << std::setw(11 - value.str().size()) << "" << std::endl;
            records.write(line.str().c_str(), line.str().size());
        } else {
            std::cout << "Falha ao abrir arquivo" << std::endl;
        }

        currentSize += step;
        lineCount++;
    }
}

void writeInFile(int algorithmIndex, std::string value, int lineCount) {
    std::ofstream records("../data/tempos3.txt", std::ios::in | std::ios::out | std::ios::binary);
    if(records.is_open()) {
        std::stringstream line;

        int lineJump = (lineCount+1) * 89;
        int tab = 11 * (algorithmIndex+1);
        records.seekp(lineJump+tab, std::ios::beg); 
        
        line << value;
        line << std::setfill(' ') << std::setw(11 - line.str().size()) << std::endl;

        records.write(line.str().c_str(), line.str().size());
    } else {
        std::cout << "Falha ao abrir arquivo" << std::endl;
    }
}

void writeBlank(int algorithmIndex, int minSize, int maxSize, int samplesAmount) {
    std::ofstream records("../data/tempos3.txt", std::ios::in | std::ios::out | std::ios::binary);
    float step = (maxSize - minSize)/(samplesAmount - 1);
    float currentSize = minSize;
    
    int lineCount = 0;
    while((int) currentSize <= maxSize) {
        if(records.is_open()) {
            int lineJump = (lineCount+1) * 89;
            int tab = 11 * (algorithmIndex+1);
            records.seekp(lineJump+tab, std::ios::beg);
            
            std::stringstream line;

            line << std::setfill(' ') << std::setw(11) << "" << std::endl;
            records.write(line.str().c_str(), line.str().size());
        } else {
            std::cout << "Falha ao abrir arquivo" << std::endl;
        }

        currentSize += step;
        lineCount++;
    }
}

void callbackFunction(IterativeFunction *function, int minSize, int maxSize, int samplesAmount, int testsAmount, int algorithmIndex) {
    float step = (maxSize - minSize)/(samplesAmount - 1);
    float currentSize = minSize;

    int line = 0;
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

        std::stringstream value;
        std::stringstream number;

        number << std::fixed << std::setprecision(6) << avg;
        value << number.str() << std::setfill(' ') << std::setw(11 - number.str().size()) << "";
        
        writeInFile(algorithmIndex, value.str(), line);
        
        currentSize += step;
        line++;
    }
}

void callbackFunction(RecursiveFunction *function, int minSize, int maxSize, int samplesAmount, int testsAmount, int algorithmIndex) {
    float step = (maxSize - minSize)/(samplesAmount - 1);
    float currentSize = minSize;

    int line = 0;
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

        std::stringstream value;
        std::stringstream number;

        number << std::fixed << std::setprecision(6) << avg;
        value << number.str() << std::setfill(' ') << std::setw(11 - number.str().size()) << "";
        
        writeInFile(algorithmIndex, value.str(), line);
        
        currentSize += step;
        line++;
    }
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