#include <iostream>
#include <iterator>
#include <algorithm>

int lsearch(int vector[], int first, int last, int value)
{
    while(first != last) {
        if(vector[first] == value) {
            return first;
        } else {
            first++;
        }
    }
    return -1;
}

int bsearch(int vector[], int first, int last, int value)
{
    while((last - first) > 1) {
        int sz = last - first;
        int middle = sz/2;
        int x = vector[first+middle];

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

int main()
{

}