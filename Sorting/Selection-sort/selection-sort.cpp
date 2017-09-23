/**
 * File              : selection-sort.cpp
 * Author            : Yanqing Wu <meet.yanqing.wu@gmail.com>
 * Date              : 21.09.2017
 * Last Modified Date: 22.09.2017
 * Last Modified By  : Yanqing Wu <meet.yanqing.wu@gmail.com>
 */

// Sorting `n` numbers stored in array A by first finding the smallest element of A and exchanging
// it with the element in A[1]. Then, find the second smallest element of A, and exchange it with
// A[2]. Continue in this manner for the first `n-1` elements of A.
// This algorithm is known as `selection sort`
//

#include <iostream>

// Signature of functions
void swap(int &x, int &y);
int* selectionSort(int * array);
void print(int * array);

void swap(int &x, int &y) {
    int temp;
    temp = x;
    x = y;
    y = temp;

    return;
}

// Take array as input and return an int array.
int* selectionSort(int * array) {
    static unsigned int start_point = 0;    // Define a starting point
    bool isSwapped = false;                 // Define a boolean flag
    int pos = -1;                           // Define a int to store position

    int tempSmall = array[start_point];     // Define a temporary variable to store the smallest int

    // If there exists multiple occurrences of a same smallest value, then this algorithm
    // will swapped the last occurrence of the smallest value with start-point.

    std::cout << "\n start-point: " << start_point << ", value = " << array[start_point] << std::endl;
    // Start from the starting, loop to the end of the loop.
    for (int i = start_point; i < 20; i++) {
        std::cout << "\n i = " << i << "." << std::endl;

        if (tempSmall >= array[i]) {
            print(array);
            std::cout << std::endl;
            pos = i;
            tempSmall = array[i];
            isSwapped = true;
        }
    }

    if (isSwapped == true) {
        std::cout << "Now swapping array[" << pos << "] and array[" << start_point << "]" << std::endl;
        swap(array[pos], array[start_point]);
        start_point++;
        selectionSort(array);
    }

    return array;
}

void print(int * array){
    for (int i = 0; i < 20; i++) {
        std::cout << i << " | ";
    }
    std::cout << std::endl;

    for(int i = 0; i < 20; i++) {
        if (i <= 10)
            std::cout << array[i] << " | ";
        else
            std::cout << array[i] << " |  ";
    }
    std::cout << std::endl;

    return;
}

int main() {

    // TODO: allow input from console
    
    int array[20] = {3, 6, 9, 0, 1, 9, 8, 6, 0, 6, 0, 3, 2, 0, 1, 7, 0, 9, 2, 1};
    print(array);

    std::cout << "After sorting..." << std::endl;

    selectionSort(array);
    print(array);

    return 0;
}
