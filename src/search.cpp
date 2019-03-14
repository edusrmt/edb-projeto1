#include <iostream>
#include <iterator>
#include <algorithm>
#include <math.h>

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
    while (last - first > 2) {
        int sz = last - first;
        int indexA = first + sz;
        int indexB = indexA + sz;

        if (vector[indexA] == value) {
            return indexA;
        } else if (vector[indexA] < value) {
            first = indexA;

            if (vector[indexB] == value) {
                return indexB;
            } else if (vector[indexB] < value) {
                first = indexB;
            } else if (vector[indexB] > value) {
                last = indexB;
            }
        } else if (vector[indexA] > value) {
            last = indexA;
        }
    }

    if (last - first == 2) {

    }
    
    return -1;
}

int jsearch(long int vector[], int last, long int value) {
    int jump = sqrt(last+1);
    int k = 1;
    int first = 0;

    while(k*jump <= last) {    
        if(vector[k*jump] == value) {
            return k*jump;
        } else if(vector[k*jump] > value){
            return lsearch(vector, k*jump, value);
        } else {
            first = k*jump;
            ++k;
        }
    }

    return -1;
}

int main() {
    long int A[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 }; // Data container.
    long int targets[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -4, 20}; // Target values for testing.

    // Prints out the original data container.
    std::cout << "Array: [ ";
    for (const auto & x : A)
        std::cout << x << " ";
    //std::copy( std::begin(A), std::end(A), std::ostream_iterator<value_type>( std::cout , " " ) );
    std::cout << "]\n";

    // Executes several searchs in the data container.
    for (long int &e : targets)
    {
        // Look for target in the entire range.
        //auto result = const_cast<value_type *>(lsearch(std::begin(A), std::end(A), e));
        int result = bsearch_r(A, 9, e);

        // Process the result
        if(result != -1)
        {
            std::cout << ">>> Found \"" << e << "\" at position " << result << ".\n";
        }
        else
        {
            std::cout << ">>> Value \"" << e << "\" was not found in the array!\n";
        }
    }

    return 0;
}