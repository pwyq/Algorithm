/**
 * File              : binary-search-sorted.cpp
 * Author            : Yanqing Wu <meet.yanqing.wu@gmail.com>
 * Date              : 23.09.2017
 * Last Modified Date: 23.09.2017
 * Last Modified By  : Yanqing Wu <meet.yanqing.wu@gmail.com>
 */

// Assume given sorted array

#include <iostream>

int BinarySearch(int * array, int low, int high, int key) {
    while (low <= high) {
        int mid = (low+high)/2;

        std::cout << "low = " << low << ", high = " << high << ", mid = " << mid << std::endl;

        if (key > array[mid]) {
            low = mid+1;    // repeat search in top half
        }
        else if (key < array[mid]) {
            high = mid-1;   // repeat search in bottom half
        }
        else
            return mid;     // found key, return position
    }

    return -1;  // Failed to find key
}

int main() {
    
    int sortArray[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 12, 19, 20, 23, 29, 80, 109, 222};

    int pos = BinarySearch(sortArray, 3, 18, 19);

    std::cout << "pos = " << pos << std::endl;

    return 0;
}
