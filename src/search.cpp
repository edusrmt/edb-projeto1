#include "../include/search.h"

namespace search {
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
}