/**
 * File              : Dynamic_stack.h
 * Author            : Yanqing Wu <meet.yanqing.wu@gmail.com>
 * Date              : 28.09.2017
 * Last Modified Date: 28.09.2017
 * Last Modified By  : Yanqing Wu <meet.yanqing.wu@gmail.com>
 */

#ifndef DYNAMIC_STACK_H
#define DYNAMIC_STACK_H

#ifndef nullptr
#define nullptr 0
#endif

#include "Exception.h"
#include <iostream>
using namespace std;

class Dynamic_stack {

	private:
		int *array;
		int count;		
		int array_size;
		int initial_size;
	
	public:
		Dynamic_stack(int = 10);
		~Dynamic_stack();

		int top() const;
		int size() const;
		bool empty() const;
		int capacity() const;
			
		void push( int const & );
		int pop();
		void clear();		
};

Dynamic_stack::Dynamic_stack( int n ):
count( 0 ),
array_size( n ),
initial_size(n)
{
	array = new int[array_size];
}


Dynamic_stack::~Dynamic_stack() {
    // Description:
    //      The destructor deletes the memory allocated for the array.
    delete [] array;
}


int Dynamic_stack::top() const {
    // Description:
    //      Return the integer at the top of the stack in O(1).
    //      It may throw an underflow exception.
    if (empty() == false) {
        return array[count - 1];
    }
    else {
        throw underflow();
    }
}


int Dynamic_stack::size() const {
    // Description:
    //      Return the number of elements currently stored in the stack in O(1)
	return  count;
}


bool Dynamic_stack::empty() const {
    // Description:
    //      Return true if stack is empty false otherwise in O(1)
	return (count == 0);  
}


int Dynamic_stack::capacity() const {
    // Description:
    //      Return the capacity of stack in O(1)
	return array_size;
}


void Dynamic_stack::push( int const &obj ) {   
    // if the array is full, create a new array with size 2n
    // and copy the elements from the current array to the new array in O(n)

    if (size() == capacity()) {
        std::cout << "Reaches current limit capacity, will double capacity right now." << std::endl;
        int * newArray = new int[capacity()];    // create a temporary array for copying

        for (int i = 0; i < capacity(); i++) {
            newArray[i] = array[i];
        }
        delete [] array;

        array = new int[2*capacity()];
        for (int i = 0; i < capacity(); i++) {
            array[i] = newArray[i];
        }
        delete [] newArray;
        
        array_size *= 2;
    }

    array[count] = obj;
    count++;
}


int Dynamic_stack::pop() {
    if (empty() == false) {
        int topEntry = array[count - 1];    // Store the first entry that will be removed.

        array[count - 1] = 0;

        count--;
        return topEntry;
    }
    else {
        throw underflow();
    }
}

void Dynamic_stack::clear() {
    // if current array size does not equal the initial size, delete the array
    // and create a new array equal to the initial size
    
    // Re-initialize the counter
    count = 0;
    if (array_size != initial_size) {
        array_size = 10;
    }

    // Free memory
    delete [] array;
    
}
#endif
