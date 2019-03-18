#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <new>
#include <math.h>

void print_step (long int vector[], int first, int last) {
    // Prints out the original data container.
    std::cout << "Array: [ ";
    for (int i = first; i <= last; i++)
        std::cout << vector[i] << " ";    

    std::cout << "]\n";
}

int lsearch(long int vector[], int last, long int value, int first = 0) {
    for (int i = first; i <= last; i++) {
        if (vector[i] == value)
            return i;
    }

    return -1;
}

int bsearch_i(long int vector[], int last, long int value) {
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

int bsearch_r(long int vector[], int last, long int value, int first = 0) {
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

            return bsearch_r(vector, last, value, first);
        }
    }

    return -1;
}

int tsearch_i(long int vector[], int last, long int value) {
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

int tsearch_r(long int vector[], int last, long int value, int first = 0) {
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

            return tsearch_r(vector, last, value, first);
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
        
        return array;
    }
}

int main(std::string select, int size, int testsAmount) {
    long int *A = generateArray(size);

    for(int i = 0; i < 7; ++i) {
        switch(i) {
            case 0:
            if(select[i] == '1') {
                
            }
            break;
            case 1:
            if(select[i] == '1') //bsearch_i()
            break;
            case 2:
            if(select[i] == '1') //bsearch_r()
            break;
            case 3:
            if(select[i] == '1') //tsearch_i()
            break;
            case 4:
            if(select[i] == '1') //tsearch_r()
            break;
            case 5:
            if(select[i] == '1') //jsearch()
            break;
            case 6:
            if(select[i] == '1') //fsearch()
            break;
        }
    }

    return 0;
}