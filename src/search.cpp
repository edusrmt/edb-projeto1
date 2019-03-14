#include <iostream>
#include <iterator>
#include <algorithm>
#include <math.h>

int lsearch(long int vector[], int last, long int value) {
    int first = 0;
    while(first != last) {
        if(vector[first] == value) {
            return first;
        } else {
            first++;
        }
    }
    return -1;
}

int bsearch(long int vector[], int last, long int value) {
    int first = 0;
    while((last - first) > 1) {
        int sz = last - first;
        int middle = sz/2;
        long int x = vector[first+middle];

        if(x == value) {
            return first+middle;
        } else if(x < value) {
            first += middle;
        } else if(x > value) {
            last -= middle;
        }

        if((last - first) == 1) {
            if(value == vector[first]) {
                return first;
            } else if(value == vector[last]) {
                return last;
            }
        }

    }
    return -1;
}

int bsearch(long int vector[], int first, int last, long int value) {
    if((last - first) > 1) {
        int sz = last - first;
        int middle = sz/2;
        long int x = vector[first+middle];

        if(x == value) {
            return first+middle;
        } else if(x < value) {
            first += middle;
        } else if(x > value) {
            last -= middle;
        }
        return bsearch(vector, first, last, value);

        if((last - first) == 1) {
            if(value == vector[first]) {
                return first;
            } else if(value == vector[last]) {
                return last;
            }
        }
    } else {
        return -1;
    }
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
    long int targets[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 , -4, 20 }; // Target values for testing.

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
        int result = jsearch(A, 9, e);

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