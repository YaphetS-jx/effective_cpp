#include <iostream>

int main() {
    std::cout << "----------------- test -----------------" << std::endl;
    {
        /* Rules to delete: if [] in new sentence, then [] is required in delete  */
        // singleton
        int *ptr = new int(10);
        delete ptr;
        // delete [] ptr; // undefined behavior, delete[] is for array

        // array 
        int *ptrArr = new int[10];
        delete [] ptrArr;
        // delete ptrArr; // undefined behavior, delete is for single object
    }
    // Just use containers like string, vector, etc. to avoid memory management
    return 0;
}