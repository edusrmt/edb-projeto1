#ifndef SEARCH
#define SEARCH

#include <iostream>
#include <string>
#include <math.h>

namespace search {
    int lsearch(long int vector[], int last, long int value);
    int lsearch(long int vector[], int first, int last, long int value);
    int bsearch(long int vector[], int last, long int value);
    int bsearch(long int vector[], int first, int last, long int value);
    int tsearch(long int vector[], int last, long int value);
    int tsearch(long int vector[], int first, int last, long int value);
    int jsearch(long int vector[], int last, long int value);
    int fsearch(long int vector[], int last, long int value);
}
#endif
