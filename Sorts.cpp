/*
For all your sorting needs... Various algorithms, from simple to complex. Function bodies 
each accompanied by introductory discussion. 

*/
#include <iostream>  // for swap, of all things... 

//===================================== function headers ============================

void shell_sort(int data[], int size); 
/* 
PRE: Array contains data in first size elements 
POST: Data is sorted. 
RETURNS: None. 
COMMENTS: Shell's method. Performance is good, not sensitive to data ordering. Good 
  general-purpose sort. 
*/


void insertion_sort(int data[], int size);
// PRE: Array contains at least size elements. 
// POST: Data is sorted. 
// RETURNS: None. 
// COMMENTS: Insertion sort is a basic sorting algorithm, reasonably fast for an N^2 
//   algorithm. 

void q_sort(int data[], int lo_idx, int hi_idx);
// Utility function for quick_sort -- handles partitioning & recursion


void quick_sort(int data[], int size);
// this is what the user calls. 'Mostly' sorts array via partitioning, then 
// insertion-sorts the k-sorted array that's left (k = 6). 


void selection_sort(int data[], int size);
// PRE: Array contains at least size elements. 
// POST: Data is sorted. 
// RETURNS: None. 
// COMMENTS: Selection sort is a basic sorting algorithm, reasonably fast for an N^2 
//   algorithm (it makes O(N^2) comparisons but only N swaps). 

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
//    Yes, it works--visualizations are available online--but its running time is worse than
//    N^2, approaching N^3. It was developed as a homework problem for an algorithms textbook. 

void comb_sort(int data[], int size);
// PRE: Array contains data in at least the first size locations. 
// POST: Data is sorted in the first size locations
// RETURNS: None. 
// COMMENTS: A fairly simple algorithm that runs in under N^2. Defines a gap, initially  
//    4/5 the array size, compares w/ item that far away, swap if necessary, repeat until 
//    a pass with no swaps, reduce gap size, repeat. Collapses to bubble sort but initial 
//    swaps have moved items close to where they belong. 


void merge_sort(int data[], int size); 
void m_sort(int data[], int aux[], int first_idx, int last_idx); 
/*
On the one hand, N lg N performance with a relatively low constant under all conditions. 
On the other, enough extra memory to hold another copy of the data. m_sort is the function
doing most of the work. 
*/

void heap_sort(int data[], int size); 
/*
Press et al.'s recommendation for default sort. N log N behavior in all cases, worst case is 
only about 20% worse than average case, no additional storage needed. Not as fast as quicksort
or merge sort, but overall it's very good, and doesn't have the pathlogies of those methods 
(n^2 worst case for quicksort, memory demands of mergesort). 
*/
//===================================== function bodies ============================


/*
Stoogesort should not be used in any practical situation. It is literally a textbook
example (it was thought up as a homework problem for an algorithms text) of an
inefficient sort. Indeed, it's not even obvious that it works at all. Its running time
is awful (n^(lg 3 / lg 1.5) = n^2.7). Visualizations are available online, so you can 
see just how bad it is:
    If first & last elements are out of order relative to each other, swap them
    Recursively sort first 2/3 of array
    Recursively sort last 2/3 of array
    Recursively sort first 2/3 of array
*/
void stooge_sort(int data[], int lo_idx, int hi_idx) {

    if (lo_idx < hi_idx) { // at least 2 items
        if (data[lo_idx] > data[hi_idx]) { // first and last items out of order relative to each other
            std::swap(data[lo_idx], data[hi_idx]);
        }
        int offset = ((hi_idx - lo_idx + 2) / 3); // ceiling of size*2/3
        if (offset > 0) {
            stooge_sort(data, lo_idx, (lo_idx + offset));
            stooge_sort(data, hi_idx - offset, hi_idx);
            stooge_sort(data, lo_idx, (lo_idx + offset));
        }
    }
}

/*
Cocktail shaker sort is a bidirectional bubble sort. One pass is made to move the
largest item to the far right, then a pass in the other direction moves the smallest
item to the far left. Repeat until all are sorted. This runs about twice as fast as
regular bubble sort, as very small items originating on the far right are moved over
quickly. But it's still N^2, and not a very efficient N^2 at that (high constant; other 
N^2 methods such as insertion or selection will almost always run faster in practice).
*/
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

/*
Selection sort is a standard introductory sort. We loop over the array repeatedly, finding
the smallest unsorted item, and using a swap to move it to the front of the array. This
implementation also finds the largest. (Take 2 items, compare them, compare the smaller to
the smallest we've found so far & the larger to the largest we've found so far.) This reduces
the number of comparisons needed by about 25%. We make N swaps regardless. Because comparisons
are usually much faster than assignments, runtime performance is relatively good for an N^2
method.
*/
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
                if (data[hi_idx] < data[current + 1]) {
                    hi_idx = current + 1;
                }
            }
            else {
                if (data[hi_idx] < data[current]) {
                    hi_idx = current;
                }
                if (data[current + 1] < data[lo_idx]) {
                    lo_idx = current + 1;
                }
            }
            current += 2;
        }
        // I had a bug that took a stupidly-long amount of time to track down.
        // We're moving things around using std::swap().
        // For the special case where lo_idx == last or hi_idx == first, i.e. the
        // smallest item is in the last array slot, or largest item in the first, carrying
        // out one of the swaps interferes with the other, resulting in incorrect
        // ordering. This avoids that. 
        if (lo_idx != last && hi_idx != first) { // typical case
            std::swap(data[first], data[lo_idx]);
            std::swap(data[last], data[hi_idx]);
        }
        else if (lo_idx == last) {
            if (hi_idx == first) {  // they're both pointing at each others' data
                std::swap(data[first], data[last]); // so swap them 
            }
            else {    // lo_idx = last, hi_idx not at first
                temp1 = data[last];  // save smallest item
                data[last] = data[hi_idx];  // put biggest item at end
                data[hi_idx] = data[first]; // move item at front down to middle
                data[first] = temp1;  // put smallest item at beginning
            }
        }
        else {  // must be: lo_idx in middle somewhere, hi_idx = first
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

/*
Comb sort can be viewed as a generalization of the bubble sort. We choose a 'gap',
initially 4/5 the array size, and (taking care not to run off either end, of course) 
compare each item with the one that far away. It takes no longer to swap widely-
separated items than it does adjacent items. This repeats until a pass is made with no
changes; at that point we reduce the gap size & go again. (Some implementations make 1 
pass for each gap > 1, and only make repeated passes for gap == 1). This continues until 
the gap is 1 and it's a regular bubble sort, but by then every item is already close to 
where it belongs. Performance is substantially better than N^2 (but slower than Shell 
or any N log N method). This gap size & 'shrink factor' is approximately optimum based on 
empirical testing.  Time Complexity: O(n log n) for the best case (1 pass at each gap, no
swaps, i.e. already sorted). O(n^2/2^p) (p is a number of increment) for average case and 
O(n^2) for the worst case.  Space complexity: O(1).
*/
void comb_sort(int data[], int size) {
    bool flips;
    int gap = (size * 4) / 5; // approximately optimum
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
        gap = int(gap / 1.3);
        // it turns out that there are 3 possible sequences of gap sizes that reduce to 1; 
        // the one going through 11 is the only one that gets rid of all the turtles 
        // (small items near the 'big' end of the array) before the gap becomes 1. 
        // So speaks the oracle of Wikipedia; I haven't tracked down an original source for 
        // that, it might be an urban legend. But the more we do with larger stepsizes, the 
        // better. 
        if (gap == 9 || gap == 10) {
            gap = 11;
        }
    }
}

/*
Shell's method can be viewed as a generalization of the insertion sort. Similar to the
comb sort, we choose an initial 'gap.' (There are several ways of doing so, and they can
affect big-O performance. But all are at least pretty darn good.) We then insertion-sort
elements that are that far apart; reduce the gap, and go again. As with comb sort, by the
time it collapses to 'regular' insertion sort, everything is already close to where it
belongs, and the remaining time needed is linear. Unlike comb sort, Shell does not need to
deliberately make passes where nothing changes, which are by definition not productive, or 
make multiple passes dealing with adjacent items. R. Sedgwick, in his book 'Algorithms,' 
recommends Shell as the default method to use when coding your own sort--it's compact, 
pretty fast, simple enough that it's easy to remember & test, not as 'brittle' regarding 
subtle errors or special cases as some, and (with appropriate selection of gap size & 
reduction schedule) not sensitive to the initial ordering of the data. Then, if testing 
determines that the sort is a bottleneck, you can go to the trouble of a more complex 
(but faster) method. (Hint: Sorting is hardly ever the bottleneck.) Running time using 
the gaps presented here runs in maximum O(N^(3/2)), and in practice averages about 
O(N^1.27) for real-world data.
*/
void shell_sort(int data[], int size) {
    int first = 0, last = size - 1, start, current, gap;
    // Sedgwick recommends this gap sequence 
    start = 1;
    while (start < size) {
        start = (start * 3) + 1; // 1, 4, 13, 40, 121, 364, 1093.... 
    }
    gap = start / 3;
    while (gap > 0) {
        for (start = gap; start <= last; start++) {
            current = start;
            while ((current >= gap) && (data[current] < data[current - gap])) {
                std::swap(data[current], data[current - gap]);
                current -= gap;
            }
        }
        gap = (gap * 5) / 9;
    }
}

/*
The method everybody loves to hate. Under most circumstances, Quicksort is blazingly
fast, but its worst case is very slow. Thus, we have to go through multiple gyrations
to try to avoid the worst case--each of which, of course, slows down the average running
time. This implementation does pretty well; I've tried to pick the optimizations that
provide the most bang for the buck. This uses 2 pivots, partitioning the data into a
small, medium, and large partition, each of which is then sorted recursively. An extension
of the median-of-3 heuristic is used to select the pivots. This continues until a partition
contains only a few items, at which point it's left alone, and a linear-time pass of insertion
sort is done over the entire array at the very end to do any cleanup. Note that the quick_sort()
function requires the companion qsort() function to actually do the work. The next extension 
would be to introduce multithreading; since the partitions are independent, each can be dealt 
with by a separate thread of execution. 
*/
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

/*
Another basic method; starting with the second item, move each item in turn until it's in 
order relative to the items above it. The only difference between this method and gnome sort 
is that gnome sort does a full exchange to move an item up 1 position; this method copies the
item being sorted to an auxiliary variable and other items moved down. These 'half-swaps' 
require fewer operations, providing a performance edge over gnomesort. Also, note that 
if an array is k-sorted (each item within k locations of where it belongs), then no item 
needs to move more than k positions, and running time is proportional to kn, i.e. O(N). 
*/
void insertion_sort(int data[], int size) {
    int tmp, current;
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


/*
Merge sort is O(n lg n) under all conditions and isn't sensitive to the ordering of 
the data (mostly because by default it ignores it). An optimized variant, Timsort, does 
take advantage of any naturally-occuring runs in the data, which happen fairly often in 
real-world data, but this one doesn't. So why isn't this used all the time? Because it 
requires an auxiliary array equal in size to the actual data. The basic algorithm is sound
and mergesort is often the method of choice for sorting a linked list, where the extra copy 
of the entire data set can be replaced by lg n pointers to hold sub-lists. Mostly included 
for completeness. It's nice and fast, but its memory usage argues strongly against it. 
*/
void merge_sort(int data[], int size) {

    int* auxiliary = new int[size]; 
    
    m_sort(data, auxiliary, 0, size - 1); 

    delete[] auxiliary; 
    auxiliary = nullptr; 

}


void m_sort(int data[], int aux[], int first_idx, int last_idx) {
    int left, right, mid, a;
    int p = (last_idx - first_idx + 1); // number of items in this partition

    if (p > 5) {
        mid = first_idx + (p / 2);
        m_sort(data, aux, first_idx, mid); // sort left half
        m_sort(data, aux, mid + 1, last_idx); // sort right half 
        left = first_idx;           // merge sorted halves 
        right = mid + 1;
        a = first_idx;
        while (left <= mid && right <= last_idx) {
            if (data[right] < data[left]) {
                aux[a++] = data[right++];
            }
            else {
                aux[a++] = data[left++];
            }
        }
        while (left <= mid) {
            aux[a++] = data[left++];
        }
        while (right <= last_idx) {
            aux[a++] = data[right++];
        }
        for (a = first_idx; a <= last_idx; a++) {
            data[a] = aux[a];
        }
    }
    else {  // skip the overhead of recursion etc for small partitions 
        for (int start = first_idx + 1; start <= last_idx; start++) {
            int current = start;
            while (current > first_idx && data[current] < data[current - 1]) {
                std::swap(data[current], data[current - 1]);
                current--;
            }
        }
    }
}

/*
We begin by making a max heap, to easily retrieve the largest item in the array. This can
be done in linear time. We then repeatedly:
   swap the largest item into the logically-last array slot; decrement logical size of array
   But we just put a small item into the top; filter it down (at most log N swaps needed) to
       restore heap property
   Until all items are in place (logical size of array == 1)

   Heap property: 
      Children of item at index p are at indices 2p+1 and 2p+2; thus parent(p) at (p-1)/2. 
      Each item is larger than either of its children (no particular relation between siblings) 
      If an item is out of place relative to its children, we can swap it with the larger of its 
        children, and then repeat that process, letting the item percolate downward until the heap 
        property is restored 
*/

void heap_sort(int data[], int size) {
    int last = size - 1, current, start, p, left, right, big;
    bool again;
    /* heapify our array. Yes, this is linear time: 
       Define one 'step' as: Compare the children of a node, make 1 swap (if needed) 
          so the largest of the 3 items is on top. 
       n/2 items have no children and need no steps to be in a heap. 
       n/4 items have 1 set of children = 1 step 
       n/8 items need at most 2 steps (if heap property OK w.r.t. children after 1 step, we
                                       can stop)
       n/16 items need at most 3 steps 
       n/32 items need at most 4 steps
       etc. 
       1n/4 + 2n/8 + 3n/16 + 4n/32 + 5n/64 + 6n/128 + .... = sum (n* k/(2^(k+1))) 
        = n * sum(k/(2^(k+1)))
        The summation converges, approaching 1 in the limit. At most n such operations
        are needed.
    */
    for (start = size / 2; start >= 0; start--) {
        current = start;
        do {
            again = false;
            big = current;
            left = 2 * current + 1;
            right = left + 1;
            if (left < size && data[big] < data[left]) {
                big = left;
            }
            if (right < size && data[big] < data[right]) {
                big = right;
            }
            if (big != current) {
                std::swap(data[big], data[current]);
                current = big;
                again = true;
            }
        } while (again);
    }
    // Actual sorting happens here, once heap is established. 
    while (last > 0) {
        std::swap(data[0], data[last]); // move largest item into position, 
        last--;                         // make sure it stays there 
        // restore heap property 
        current = 0;
        do {
            again = false;
            big = current;
            left = 2 * current + 1;
            right = left + 1;
            if (left < size && data[big] < data[left]) {
                big = left;
            }
            if (right < size && data[big] < data[right]) {
                big = right;
            }
            if (big != current) {
                std::swap(data[current], data[big]);
                current = big;
                again = true;
            }
        } while (again);
    }
}
