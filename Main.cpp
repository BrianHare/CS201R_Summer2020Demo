#include <iostream> 
#include <ctime>

void insertion_sort(int data[], int size);


void q_sort(int data[], int lo_idx, int hi_idx);
// N.B. Testing indicates a logic bug somewhere (a large, but not the highest, value at 
// the right end). Don't use until I've tracked it down. 

void quick_sort(int data[], int size); 
// this is what the user calls. 'Mostly' sorts array via partitioning, then 
// insertion-sorts the k-sorted array that's left (k = 5). 


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

const int DATASIZE = 10;

int main() {
    int* data = new int[DATASIZE]; 
    std::cout << "Hello world!" << std::endl;

    srand(time(NULL));
    for (int k = 0; k < DATASIZE; k++) {
        data[k] = 20 - k;
    //    data[k] = std::rand();
    }
    
   selection_sort(data, DATASIZE);

    std::cout << "Checking...." << std::endl; 
    for (int k = 1; k < DATASIZE; k++) {
        if (data[k] < data[k - 1]) {
            std::cerr << "Error in sort at index: " << k << '\n' 
                << "Data[" << k << "] = " << data[k] << "; Data[" << k-1 
                << "] = " << data[k-1] << std::endl;
        }
    }
    //for (int k = 0; k < DATASIZE; k++)
    //    std::cout << data[k] << std::endl;

    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }


    return EXIT_SUCCESS;
}


void stooge_sort(int data[], int lo_idx, int hi_idx) {
    
    if (lo_idx < hi_idx) { // at least 2 items
        if (data[lo_idx] > data[hi_idx]) { // first and last items out of order relative to each other 
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
    int first = 0, last = size - 1, current, lo_idx, hi_idx;
    int temp1; 

    while (last - first > 1) {  // more than 2 items
        lo_idx = hi_idx = last;
        current = first;
        while (current < last) {
            if (data[current] < data[current + 1]) {
                if (data[current] < data[lo_idx]) {
                    lo_idx = current;
                }
                if (data[hi_idx] < data[current+1]) {
                    hi_idx = current+1;
                }
            }
            else {
                if (data[current] > data[hi_idx]) {
                    hi_idx = current;
                }
                if (data[current+1] < data[lo_idx]) {
                    lo_idx = current+1;
                }
            }
            current += 2; 
        }
        // I had a bug that took a stupidly-long amount of time to track down. 
        // We're moving things around using std::swap(). 
        // For the special case where lo_idx == last or hi_idx == first, carrying 
        // out one of the swaps interferes with the other, resulting in incorrect
        // ordering. This avoids that... 
        if (lo_idx != last && hi_idx != first) { // typical case 
            std::swap(data[first], data[lo_idx]); 
            std::swap(data[last], data[hi_idx]);
        }
        else if (lo_idx == last && hi_idx == first) { // they're both pointing at each others' data
            std::swap(data[first], data[last]); 
        }
        else if (lo_idx == last) {  // lo_idx = last, hi_idx not at first
            temp1 = data[last];  // save smallest item 
            data[last] = data[hi_idx];  // put biggest item at end 
            data[hi_idx] = data[first]; // move item at front down to middle
            data[first] = temp1;  // put smallest item at beginning 
        }
        else {  // must be: hi_idx = first, lo_idx in middle somewhere 
            temp1 = data[first]; // save largest item 
            data[first] = data[lo_idx]; // put smallest at front 
            data[lo_idx] = data[last]; // move item from back to middle
            data[last] = temp1;  // put largest item at end. 
        }
        first++;
        last--;
    }
    if (first <= last) {  // 1 or exactly 2 items left 
        // if 2 & they're out of order, swap them; if only 1, test fails, do nothing 
        if (data[last] < data[first]) {
            std::swap(data[first], data[last]);
        }
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

void quick_sort(int data[], int size) {
    int tmp, current;

    // Use 2-pivot partitioning until partition size is 6 or less. 
    // Then clean up with insertion sort (for k-sorted arrays, insertion
    // sort is linear time).
    q_sort(data, 0, size - 1);
    for (int start = 1; start < size; start++) {
        current = start;
        tmp = data[start];
        while (current > 0 && tmp < data[current - 1]) {
            data[current] = data[current - 1];
            current--;
        }
        if (current != start) { // we have in fact moved some things around 
            data[current] = tmp; // so complete the exchange 
        }
    }
}


void q_sort(int data[], int lo_idx, int hi_idx) {
    /* code note: This sprawling monstrosity is crying out to be refactored. 
     For a start, break out the identification of the pivots into its own function;
     then move the partitioning into a function. 

     True Confessions: There's an off-by-one error lurking somewhere in the 
     partitioning code or the recursive calls; I keep finding pairs of swapped 
     items scattered throughout the array. BUT since they're never more than 1 
     position away from where they belong anyway, and we're using insertion sort 
     to clean up small partitions, they can be swept up into that. Yes, it's 
     cheesy, and probably worth tracking down the error. But the payoff is likely to be 
     small, given that 2-pivot Qsort with alternative sorts on small partitions is 
     already one of the fastest algorithms known (of the n log n i.e. comparison-based 
     methods). 
    */
    int small, large, current;
    int indices[5];

    if (hi_idx - lo_idx >= 5) {
        indices[0] = lo_idx;
        indices[1] = hi_idx;
        indices[2] = (lo_idx + hi_idx) / 2;      // midpoint
        indices[3] = (lo_idx + indices[2]) / 2;  // (lo, mid) midpoint
        indices[4] = (hi_idx + indices[2]) / 2;  // (mid, hi) midpoint

        // brute-force sort into order (only 5 items, algorithm doesn't matter) 
        // so they're arranged by value of data at each index 

        for (int round = 0; round < 5; round++) {
            for (int j = 0; j < 4; j++) {
                if (data[indices[j]] > data[indices[j + 1]]) {
                    std::swap(indices[j], indices[j + 1]);
                }
            }
        }
        // move pivots to endpoints 
        std::swap(data[indices[3]], data[hi_idx]);
        std::swap(data[indices[1]], data[lo_idx]);

        small = lo_idx;  // leftmost small item 
        large = hi_idx;  // rightmost large item 

        current = small;
        while (current <= hi_idx) {
            if (data[current] < data[lo_idx]) {
                small++;
                std::swap(data[current], data[small]);
            }
            current++;
        }

        std::swap(data[lo_idx], data[small]); // move piv1 to rightmost position in small portion

        // from lo_idx to small is now the smaller items. Now do same thing for large items. 
        current = hi_idx;
        while (current > small) {
            if (data[hi_idx] < data[current]) { // this item is greater than pivot
                large--;
                std::swap(data[current], data[large]);
            }
            current--;
        }
        q_sort(data, lo_idx, small - 1);  // sort left partition 
        q_sort(data, large + 1, hi_idx);  // sort right partition 
        // if data[large] and data[small] are the same, then everything between them is identical
        // and doesn't need to be sorted. Otherwise... 
        if (data[large] != data[small]) {
            q_sort(data, small + 1, large - 1); // sort middle portion
        }
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