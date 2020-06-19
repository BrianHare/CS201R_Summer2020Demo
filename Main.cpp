#include <iostream> 
#include <ctime>

const int DATASIZE = 100;




int main() {
    bool oops = false; 
    int* data = new int[DATASIZE]; 
    std::cout << "Hello world!" << std::endl;

    srand(time(NULL));
    for (int k = 0; k < DATASIZE; k++) {
        data[k] = std::rand();
    }
    
    // call to sort method goes here 

    for (int k = 1; k < DATASIZE; k++) {
        if (data[k] < data[k - 1]) {
            oops = true; 
            std::cout << "Error at index: " << k << ". Data[" << k << "] = " << data[k]
                << ", Data[" << k - 1 << "] = " << data[k - 1] << '\n';
        }
    }
    if (!oops) {
        std::cout << "Data is sorted, all is well.... \n";
    }

    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }


    return EXIT_SUCCESS;
}

