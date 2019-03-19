#include "../include/util.h"

namespace util {
    typedef int IterativeFunction(long int vector[], int last, long int value);
    typedef int RecursiveFunction(long int vector[], int first, int last, long int value);

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


    void writeHeader() {
        std::ofstream records("data/tempos.txt", std::ios::in | std::ios::out | std::ios::trunc);
        std::string headerItems[] = {"# N", "ILS", "IBS", "ITS", "IJS", "IFS", "RBS", "RTS"};
        std::stringstream header;

        for(const auto &s : headerItems) {
            header << s;
            header << std::setfill(' ') << std::setw(15 - s.size()) << "";
        }

        records << header.str() << std::endl;
    }

    void writeAmount(int minSize, int maxSize, int samplesAmount) {
        std::ofstream records("data/tempos.txt", std::ios::in | std::ios::out | std::ios::binary);
        float step = (maxSize - minSize)/(samplesAmount - 1);
        float currentSize = minSize;
        
        int lineCount = 0;
        while((int) currentSize <= maxSize) {
            if(records.is_open()) {
                int lineJump = (lineCount+1) * 121;
                std::stringstream value;
                std::stringstream line;

                records.seekp(lineJump, std::ios::beg);
                
                value << std::setprecision(std::numeric_limits<double>::max_digits10) << currentSize;

                line << value.str() << std::setfill(' ') << std::setw(15 - value.str().size()) << "" << std::endl;
                records.write(line.str().c_str(), line.str().size());
            } else {
                std::cout << "Falha ao abrir arquivo" << std::endl;
            }

            currentSize += step;
            lineCount++;
        }
    }

    void writeInFile(int algorithmIndex, std::string value, int lineCount) {
        std::ofstream records("data/tempos.txt", std::ios::in | std::ios::out | std::ios::binary);
        if(records.is_open()) {
            std::stringstream line;

            int lineJump = (lineCount+1) * 121;
            int tab = 15 * (algorithmIndex+1);
            records.seekp(lineJump+tab, std::ios::beg); 
            
            line << value;
            line << std::setfill(' ') << std::setw(15 - line.str().size()) << std::endl;

            records.write(line.str().c_str(), line.str().size());
        } else {
            std::cout << "Falha ao abrir arquivo" << std::endl;
        }
    }

    void writeBlank(int algorithmIndex, int minSize, int maxSize, int samplesAmount) {
        std::ofstream records("data/tempos.txt", std::ios::in | std::ios::out | std::ios::binary);
        float step = (maxSize - minSize)/(samplesAmount - 1);
        float currentSize = minSize;
        
        int lineCount = 0;
        while((int) currentSize <= maxSize) {
            if(records.is_open()) {
                int lineJump = (lineCount+1) * 121;
                int tab = 15 * (algorithmIndex+1);
                records.seekp(lineJump+tab, std::ios::beg);
                
                std::stringstream line;

                line << std::setfill(' ') << std::setw(15) << "" << std::endl;
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
                (*function)(A, ((int) currentSize) - 1, maxSize); 
                auto end = std::chrono::high_resolution_clock::now();

                double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                sum += duration;
            }
            
            double avg = (sum/testsAmount) * 1e-6;

            std::stringstream value;
            std::stringstream number;

            number << std::fixed << std::setprecision(6) << avg;
            value << number.str() << std::setfill(' ') << std::setw(15 - number.str().size()) << "";
            
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
                (*function)(A, ((int) currentSize) - 1, maxSize, 0); 
                auto end = std::chrono::high_resolution_clock::now();

                double duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

                sum += duration;
            }
            
            double avg = (sum/testsAmount) * 1e-6;

            std::stringstream value;
            std::stringstream number;

            number << std::fixed << std::setprecision(6) << avg;
            value << number.str() << std::setfill(' ') << std::setw(15 - number.str().size()) << "";
            
            writeInFile(algorithmIndex, value.str(), line);
            
            currentSize += step;
            line++;
        }
    }
}