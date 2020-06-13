#include <iostream> 


void selection_sort(int data[], int size); 
// PRE: Array contains at least size elements. 
// POST: Data is sorted. 
// RETURNS: None. 
// COMMENTS: Selection sort is a basic sorting algorithm, probably the fastest of the N^2 
//   algorithms (it makes O(N^2) comparisons but only N swaps). 

void shaker_sort(int data[], int size); 
// PRE: Array contains at least size elements. 
// POST: Data is sorted. 
// RETURNS: None. 
// COMMENTS: Shaker sort, a/k/a cocktail sort, is a bidirectional variant on bubble sort. 
//   One round moves the largest item to the end, then a round moving the smallest to the 
//   beginning. This runs about twice as fast as an ordinary bubble sort but is still N^2. 

void stooge_sort(int data[], int lo_idx, int hi_idx); 
// PRE: Array contains data; lo_idx and hi_idx are lowest and highest indices
//    of arrays containing data 
// POST: Data is sorted using the stooge sort algorithm. 
// RETURNS: None. 
// COMMENTS: Stooge sort is horribly inefficient and should not be used 
//    for any real data or any siutation you actually care about; it's a demonstration 
//    of an awful algorithm: 
//              If the first and last items are incorrect, i.e. data[lo] > data[hi], 
//                      swap them
//              Recursively sort the first 2/3 of the array 
//              Recursively sort the last 2/3 of the array 
//              Recursively sort the first 2/3 of the array
//    Yes, it works--visualizations are available online--but its running time is worse than N^2. 

void comb_sort(int data[], int size);
// PRE: Array contains data in at least the first size locations. 
// POST: Data is sorted 
// RETURNS: None. 
// COMMENTS: A fairly simple algorithm that runs in under N^2. Defines a gap, initially about 
//    half the array, compares w/ item that far away, swap if necessary, repeat until a pass 
//    with no swaps, reduce gap size, repeat. Collapses to bubble sort but initial swaps have 
//    moved items close to where they belong. 


int main() {
    int data[100]; 
    std::cout << "Hello world!" << std::endl;
    
    for (int k = 0; k < 100; k++) {
        data[k] = std::rand();
    }
    shaker_sort(data, 100); 

    for (int k = 0; k < 100; k++)
        std::cout << data[k] << std::endl; 
    return EXIT_SUCCESS;
}


void stooge_sort(int data[], int lo_idx, int hi_idx) {
    int offset = ((hi_idx - lo_idx + 1) * 2) / 3;

    if (data[lo_idx] > data[hi_idx]) {
        std::swap(data[lo_idx], data[hi_idx]);
    }
    stooge_sort(data, lo_idx, (lo_idx + offset));
    stooge_sort(data, hi_idx - offset, hi_idx); 
    stooge_sort(data, lo_idx, (lo_idx + offset));
}

void shaker_sort(int data[], int size) {
    int first = 0, last = size - 1, current; 
    while (first < last) {
        for (current = first; current < last - 1; current++) {
            if (data[current] > data[current + 1]) {
                std::swap(data[current], data[current + 1]);
            }
        }
        last--;  // biggest item is in place here. 
        for (current = last; current > first; current--) {
            if (data[current] < data[current - 1]) {
                std::swap(data[current], data[current - 1]); 
            }
        }
        first++;
    }
}

void selection_sort(int data[], int size) {
    int first = 0, last = size - 1, current, lo_idx, hi_idx; 

    while (first < last) {
        lo_idx = hi_idx = first; 
        for (current = first + 1; current <= last; current++) {
            if (data[current] < data[lo_idx]) {
                lo_idx = current;
            }
            else if (data[current] >= data[hi_idx]) {
                hi_idx = current;
            }
        }
        std::swap(data[first], data[lo_idx]);
        std::swap(data[last], data[hi_idx]); 
        first++; 
        last--;
    }
}

void comb_sort(int data[], int size) {
    bool flips;
    int gap = (size * 6) / 11;
    while (gap > 0) {
        do {
            flips = false;
            for (int current = gap; current < size; current++) {
                if (data[current] < data[current - gap]) {
                    std::swap(data[current], data[current - gap]);
                    flips = true;
                }
            }
        } while (flips); 
        gap = (gap * 5) / 9;
    }
}
