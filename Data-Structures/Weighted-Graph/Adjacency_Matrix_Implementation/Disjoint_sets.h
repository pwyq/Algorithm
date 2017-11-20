/**
 * File              : Disjoint_sets.h
 * Author            : Yanqing Wu <meet.yanqing.wu@gmail.com>
 * Date              : 18.11.2017
 * Last Modified Date: 18.11.2017
 * Last Modified By  : Yanqing Wu <meet.yanqing.wu@gmail.com>
 */

#ifndef DISJOINT_SET_H
#define DISJOINT_SET_H

#ifndef nullptr
#define nullptr 0
#endif

#include <iostream>
#include <limits>
#include "Exception.h"

using namespace std;

struct ll_entry; // represents each element of the linked list
struct set_info; // keeps track of the information (pointers to head and tail and the size of the set) of each set
//could we delete the above two lines?


struct ll_entry{ 
	int content;
	set_info* ptr_to_info; // ptr to the info entry of the corresponding set
	ll_entry* next;
	
};

struct set_info { 
	ll_entry* head;
	ll_entry* tail;
	int size;
};

class Disjoint_set {

private:
	ll_entry** nodes;   // An array of pointers that keeps a ptr to each node entry in the linked list
	set_info** sets;    // An array of pointers that keeps the info for each set
                            // including, the ptr to head and tail of the set; size (int) of the set
	int set_counter;    // used to save the current number of sets
	int initial_num_sets;   // used to save the initial number of sets
public:
	Disjoint_set(int);
	~Disjoint_set();
	int find_set(int) const;
	int num_sets() const;
	void union_sets(int, int);
};

Disjoint_set::Disjoint_set(int n) : nodes(new ll_entry*[n]), 
sets (new set_info*[n]), 
set_counter(n),
initial_num_sets(n) {
	// initialize the sets	
    for (int i = 0; i < n; ++i) {
        nodes[i] = new ll_entry;
        nodes[i]->content = i;
        nodes[i]->next = nullptr;

        sets[i] = new set_info;
        sets[i]->head = nodes[i];
        sets[i]->tail = nodes[i];
        sets[i]->size = 1;

        nodes[i]->ptr_to_info = sets[i];
    }
}

Disjoint_set::~Disjoint_set() {
	// deallocate memory
    for (int i = 0; i < initial_num_sets; ++i) {
        // cout << "delete nodes[" << i << "]: " << nodes[i] << endl;
        // cout << "delete sets[" << i << "]: " << sets[i] << endl;
        delete nodes[i];
        delete sets[i];
    }
    delete [] nodes;
    delete [] sets;
}
int Disjoint_set::find_set(int item) const{
	// should it be? return nodes[item]->ptr_to_info->head->content 

    // Definition of FIND_SET(): Returns a representitive or ptr to the representative of the (unique) set containing `item`
	return nodes[item]->ptr_to_info->head->content;
}

int Disjoint_set::num_sets() const {
	return set_counter;
}

void Disjoint_set::union_sets(int node_index1, int node_index2) {
	
	if (node_index1 == node_index2)
		return;
	
	set_info* si1 = nodes[node_index1]->ptr_to_info;
	set_info* si2 = nodes[node_index2]->ptr_to_info;

    // when node1 and node2 in the same set
    if (find_set(node_index1) == find_set(node_index2)) {
        // cout << "\ntest-1: " << find_set(node_index1) << endl;
        // cout << "\ntest-2: " << find_set(node_index2) << endl;
        return ;
    }

	// ni1: the index of the larger set, ni2: the index of the smaller set
	int ni1 = si1->size >= si2->size ? node_index1 : node_index2; 
	int ni2 = si1->size < si2->size ? node_index1 : node_index2;


    si1 = nodes[ni1]->ptr_to_info;   // update si1 to be the larger set
    si2 = nodes[ni2]->ptr_to_info;   // update si2 to be the smaller set

    ll_entry *tempNode = si2->head; // declare a temp pointer of the LL in the smaller set
	// iterate through the shorter list and modify the pointers
	while (tempNode != nullptr) {
       tempNode->ptr_to_info = si1;
       // cout << "\nsi2->head ptr-to-info: " << tempNode->ptr_to_info << endl;
       tempNode = tempNode->next;
	}

	// do we need to modify anything else?
	
    // link the tail of the larger LL with the head of the smaller LL
    si1->tail->next = si2->head;
    // move the tail of ni1 to the end of ni2
    si1->tail = si2->tail;
    si1->size += si2->size;

	// delete the set_info entry that no longer exists
	si2->head = nullptr;
    si2->tail = nullptr;
    si2->size = 0;
    si2 = nullptr;
    set_counter--;
}

#endif