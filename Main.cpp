#include <iostream> 
#include <ctime>



const int DATASIZE = 10;

int main() {
    int* data = new int[DATASIZE]; 
    std::cout << "Hello world!" << std::endl;

    srand(time(NULL));
    for (int k = 0; k < DATASIZE; k++) {
        data[k] = 20 - k;
    //    data[k] = std::rand();
    }
    
   // selection_sort(data, DATASIZE);

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

