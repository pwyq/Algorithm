#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H


/****************************************
 * UW User ID:  y433wu
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2017
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 ****************************************/

#include "Exception.h"
#include "ece250.h"

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
	private:
		int count;          // The number of elements currently in the hash table
		int power;          // Related to the capacity of the hash table (array_size = 2^power)
		int array_size;     // The capacity of the hash table
		T *array;           // An array of objects of type `T`. This array will contain the values places in the hash table
		state *array_state; // An array of objects of type `state` - to store the status of the bin
                            // The state of a bin is one of three possible values: EMPTY, OCCUPIED,
                            // DELETED

		int h1( T const & ) const; // first hash function
		int h2( T const & ) const; // second hash function

	public:
		DoubleHashTable( int = 5 );
		~DoubleHashTable();
		int size() const;
		int capacity() const;		
		bool empty() const;
		bool member( T const & ) const;
		T bin( int ) const;

		void print() const;

		void insert( T const & );
		bool remove( T const & );
		void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
array_state( new state[array_size] ) {
    // TODO: need to allocate and initialize two arrays
    //          one for storing the values in the hash table
    //          one for storing the status of the bins
   
	for (int i = 0; i < array_size; i++) {
		array_state[i] = EMPTY;
        array[i] = 0;
	}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
	// TODO: deletes the memory allocated for the hash table (the two arrays)

    delete [] array;
    delete [] array_state;
}

template<typename T >
int DoubleHashTable<T >::size() const {
    // Description:
    //  return the number of elements currently stored in the hash table. O(1)
	return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    // Description:
    //  return the number of bins in the hash table. O(1)
	return array_size;
}


template<typename T >
bool DoubleHashTable<T >::empty() const {
    // Description:
    //  return true if the hash table is empty, falsh otherwise. O(1)
	return (count == 0);
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
	// Description:
    // primary hash function (determine the bin)
    //  - (i % M)
    //  - M is the capacity (here, array_size) of the hash table
    //  - adding M if the value is negative.

    int probe = (static_cast<int> (obj)) % capacity();
    while (probe < 0) {
        probe += capacity();
    }

    // std::cout << "input obj: " << obj << ", returning probe: " << probe << std::endl;

	return probe;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
	// Description:
    // secondary (odd) hash function (determine the jump size)
    //  - ((i/M) % M)
    //  - adding M if the value is negative.
    //  - if result is even, make it odd by adding 1.

    int offset = h1(static_cast<int>(obj)/array_size);
    while (offset < 0) {
        offset += capacity();
    }

    if (offset % 2 == 0) {
        return (offset + 1);
    }

	return offset;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
	// Description:
    //  return true if object `obj` is in the hash table and false otherwise. O(1)
	
    int probe = h1(obj);
    int offset = h2(obj);
    int counter = 0;
    // std::cout << "array[probe]: " << array[probe] << ", obj: " << obj << std::endl;  // for debugging
    
    while (array[probe] != obj && array_state[probe] != EMPTY) {
        if (counter == capacity()) {
            return false;
        }
        probe = (probe + offset) % capacity();
        counter++;
    }

    if (array[probe] == obj && array_state[probe] == OCCUPIED) {
        return true;
    }

	return false;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    // Description:
    //  return the entry in bin `n`.
    //  If the bin is not filled, this function is not defined.
    //  This will only be used to test the class with the expected locations. O(1)

    if (n < 0 || n >= capacity()) {
        throw ArrayBoundsException();
    }

    if (array_state[n] == OCCUPIED) {
        return array[n];
    }
                
	return T();
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
	// Description:
    //     Insert the new object into the hash table by the two hash functions and the rules of
    //     double hashing.
    //     If the talbe is full, throw an overflow exception. O(1)
    if (size() >= capacity()) {
        throw overflow();
    }

    int probe = h1(obj);
    int offset = h2(obj);
    while(array_state[probe] == OCCUPIED) {
        probe = ((probe + offset) % capacity());
    }

    array[probe] = obj;
    array_state[probe] = OCCUPIED;
    count++;
    return ; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
	// Description:
    //     remove the object from the hash table if it is in the hash table (false otherwise) by
    //     setting the corresponding flag of the bin to deleted. O(1)

    // If the entire Table is empty, we have nothing to remove (and we can save search time in this
    // case). Thus, immediately return false in this case.
    if (empty() == true) {
        return false;
    }

    int probe = h1(obj);
    int offset = h2(obj);
    int counter = 0;        // declare a counter to record iteration time
    while(array[probe] != obj && array_state[probe] != EMPTY) {
        if (counter == capacity()) {
            return false;
        }
        probe = (probe + offset) % capacity();
        counter++;
    }

    // After finding the `obj` that need to be delete
    if (array[probe] == obj && array_state[probe] == OCCUPIED) {
        array[probe] = 0;
        array_state[probe] = DELETED;
        count--;
        return true;
    }
    // If not finding the key, return false
    return false;
}

template<typename T >
void DoubleHashTable<T >::clear() {
	// Description:
    //     remove all the elements in the hash table. O(M)
    for (int i = 0; i < capacity(); i++) {
        array_state[i] = EMPTY;
        array[i] = 0;
    }
    count = 0;
    return ; 
}

template<typename T >
void DoubleHashTable<T >::print() const {
    // Description:
    //    This is used to print the class in the testing environment.
    //    (This function will not be tested.)
    for (int i = 0; i < capacity(); i++) {
        std::cout << i << " " << bin(i) << std::endl;
    }
	return;
}

#endif
