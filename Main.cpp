#include <iostream> 

void quick_sort(int data[], int lo_idx, int hi_idx);
// N.B. Testing indicates a logic bug somewhere (a large, but not the highest, value at 
// the right end). Don't use until I've tracked it down. 

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
// PRE: Array contains data; lo_idx and hi_idx are lowest and highest indices of array
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
//    It was developed as a homework problem for an algorithms textbook. 

void comb_sort(int data[], int size);
// PRE: Array contains data in at least the first size locations. 
// POST: Data is sorted in the first size locations
// RETURNS: None. 
// COMMENTS: A fairly simple algorithm that runs in under N^2. Defines a gap, initially about 
//    half the array, compares w/ item that far away, swap if necessary, repeat until a pass 
//    with no swaps, reduce gap size, repeat. Collapses to bubble sort but initial swaps have 
//    moved items close to where they belong. 

int data[4000];

int main() {
    std::cout << "Hello world!" << std::endl;

    for (int k = 0; k < 4000; k++) {
        data[k] = std::rand();
    }
    quick_sort(data, 0, 3999);

    for (int k = 0; k < 4000; k++)
        std::cout << data[k] << std::endl;
    return EXIT_SUCCESS;
}


void stooge_sort(int data[], int lo_idx, int hi_idx) {
    
    if (lo_idx < hi_idx) { // at least 2 items
        if (data[lo_idx] > data[hi_idx]) {
            std::swap(data[lo_idx], data[hi_idx]);
        }
        int offset = ((hi_idx - lo_idx) * 2) / 3;
        if (offset > 0) {
            stooge_sort(data, lo_idx, (lo_idx + offset));
            stooge_sort(data, hi_idx - offset, hi_idx);
            stooge_sort(data, lo_idx, (lo_idx + offset));
        }
    }
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

void quick_sort(int data[], int lo_idx, int hi_idx) {

    if (hi_idx - lo_idx < 30) {   // shell sort for small portion 
        int gap = ((hi_idx - lo_idx + 1) * 2) / 3;
        while (gap > 0) {
            int lo_bound = lo_idx + gap;
            for (int start = lo_bound; start <= hi_idx; start++) {
                int current = start;
                while ((current >= lo_bound) && (data[current] < data[current - gap])) {
                    std::swap(data[current], data[current - gap]);
                    current -= gap;
                }
            }
            gap = (gap * 5) / 9;
        }
    }
    else {   // larger portion - 2-pivot partitioning 
        int small, large; 
        int indices[5];

        indices[0] = lo_idx; 
        indices[1] = hi_idx;
        indices[2] = (indices[0] + indices[1]) / 2;  // midpoint
        indices[3] = (indices[0] + indices[2]) / 2;  // (lo, mid) midpoint
        indices[4] = (indices[1] + indices[2]) / 2;  // (mid, hi) midpoint

        // brute-force sort into order (only 5 items, algorithm doesn't matter) 
        // so they're arranged by value of data at each index 

        for (int range = 4; range > 0; range--) {
            for (int j = 0; j < range; j++) {
                if (data[indices[j+1]] < data[indices[j]]) {
                    std::swap(indices[j], indices[j + 1]);
                }
            }
        }

        std::swap(data[indices[1]], data[lo_idx]);
        std::swap(data[indices[3]], data[hi_idx]); 
        small = lo_idx;  // leftmost small item 
        large = hi_idx;  // rightmost large item 
        
        for (int current = small + 1; current < large; current++) {
            if (data[current] < data[lo_idx]) {  // less than piv1 
                std::swap(data[current], data[++small]);
            }
            else if (data[hi_idx] < data[current]) {  // greater than piv2 
                std::swap(data[current], data[--large]);
                // Note: With small, we shifted over an item we've already looked at. But in this case, 
                // this item may be very small & need to be on the left; or it may need to be 
                // shifted right back into the larger portion. In short, we need to make it the next 
                // item examined. 
                current--;  // so back up one slot. 
            }
        }
    
        std::swap(data[lo_idx], data[small]); // move piv1 to rightmost position in small portion
        std::swap(data[hi_idx], data[large]); // move piv2 to leftmost position in large portion 
        quick_sort(data, lo_idx, small - 1);  // sort left partition 
        quick_sort(data, large + 1, hi_idx);  // sort right partition 

        // If our pivot items are the same, everything between them is duplicate & doesn't 
        // need to be touched. Otherwise, sort middle portion 
        if (data[small] < data[large]) {
            quick_sort(data, small + 1, large - 1); 
        }
    }
}