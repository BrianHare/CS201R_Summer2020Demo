#include <iostream> 

void insertion_sort(int data[], int size);


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

const int DATASIZE = 4000;
int data[DATASIZE];

int main() {
    std::cout << "Hello world!" << std::endl;

    srand(10);
    for (int k = 0; k < DATASIZE; k++) {
        data[k] = std::rand();
    }
   quick_sort(data, 0, DATASIZE-1);

    std::cout << "Checking...." << std::endl; 
    for (int k = 1; k < DATASIZE; k++) {
        if (data[k] < data[k - 1]) {
            std::cerr << "Error in sort at index:" << k << '\n' 
                << "Data[" << k << "] = " << data[k] << "; Data[" << k-1 
                << "] = " << data[k-1] << std::endl;
        }
    }

    //for (int k = 0; k < DATASIZE; k++)
    //    std::cout << data[k] << std::endl;

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
        for (current = first; current < last; current++) {
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
    int first = 0, last = size - 1, current, lo_idx; 

    while (first < last) {
        lo_idx = first;
        for (current = first; current <= last; current++) {
            if (data[current] < data[lo_idx]) {
                lo_idx = current;
            }
        }
        std::swap(data[lo_idx], data[first]);
        first++;
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
        int gap = ((hi_idx - lo_idx) * 2) / 3;
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
        int small, large, current; 
        int indices[5];

        indices[0] = lo_idx; 
        indices[1] = hi_idx;
        indices[2] = (lo_idx + hi_idx) / 2;      // midpoint
        indices[3] = (lo_idx + indices[2]) / 2;  // (lo, mid) midpoint
        indices[4] = (hi_idx + indices[2]) / 2;  // (mid, hi) midpoint

        // brute-force sort into order (only 5 items, algorithm doesn't matter) 
        // so they're arranged by value of data at each index 

        for (int round = 0; round < 4; round++) {
            for (int j = 0; j < 4; j++) {
                if (data[indices[j]] > data[indices[j + 1]]) {
                    std::swap(indices[j], indices[j + 1]);
                }
            }
        }
                
  //      std::swap(data[indices[3]], data[hi_idx]);
        std::swap(data[indices[1]], data[lo_idx]);
   
        small = lo_idx;  // leftmost small item 
        large = hi_idx;  // rightmost large item 
        
        current = small;
        while (current <= large) {
            if (data[current] < data[lo_idx]) {
                std::swap(data[current], data[++small]);
            }
            //else if (data[hi_idx] < data[current]) {
            //    std::swap(data[current], data[--large]);
            //    // this item is unknown, may be small, may need to be swapped back to large 
            //    // so offset the increase in current that's about to happen 
            //    current--;
            //}
            current++;
        }

        std::swap(data[lo_idx], data[small]); // move piv1 to rightmost position in small portion
        //std::swap(data[hi_idx], data[large]); // move piv2 to leftmost position in large portion 
        quick_sort(data, lo_idx, small);  // sort left partition 
        quick_sort(data, small+1, hi_idx);  // sort right partition 

        //// If our pivot items are the same, everything between them is duplicate & doesn't 
        //// need to be touched. Otherwise, sort middle portion 
        //if (data[small] < data[large]) {
        //    quick_sort(data, small, large); 
        //}
    }
}

void insertion_sort(int data[], int size) {
    int tmp, current; 
    for (int start = 1; start < size; start++) {
        current = start; 
        tmp = data[start];
        while (current > 0 && tmp < data[current-1]) {
            data[current] = data[current - 1];
            current--;
        }
        if (current != start) { // we have in fact moved some things around 
            data[current] = tmp; // so complete the exchange 
        }
    }
}