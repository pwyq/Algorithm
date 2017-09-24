// linkedinlist.cpp
// Yanqing wu
//

#include <iostream>

using namespace std;

class Node
{
private:
	int element;	// list of integers
	Node *next_element;
public:
	// getter function
	int getElem() {
		return element;
	}

	Node *getNext() {
		return next_element;
	}

	void setElem(int x) {
		element = x;
	}

	void *setNext(Node *next) {
		next_element = next;
	}
};

class List
{
private:
	Node *head;
	Node *tail;
	int list_count;

	bool isEmpty(){
		return head == NULL;
	}
public:
	// a constructor that creates an empty list
	List() {
		head = NULL;	// initialize head to null
		tail = NULL;
		list_count = 0;
	}

	void insert(int data){
		Node *newNode = new Node();	// create a new Node
		newNode->setElem(data); 
		if(isEmpty()){
			newNode->setNext(NULL);
			tail = newNode;
		}
		else{
			newNode->setNext(head);
		}
		head = newNode;	// let `head` points to newNode
		list_count += 1;
	}

	void find(int data) {
		Node *temp = new Node();
		int index;
		for(index = 1, temp = head; temp->getNext() != NULL && temp->getElem() != data; temp = temp->getNext(), index++);
		if(temp->getElem() == data){
			cout << "Found " << data << " at position: " << index << endl;
		}
		else if(temp->getNext() == NULL){
			cout << "NotFound!" << endl;
		}
	}

	void print(){
		Node *temp = new Node();
		cout << "Total amount is: " << list_count << endl;
		if(!isEmpty()){
			for(temp = head; temp != NULL; temp=temp->getNext())
				cout << temp->getElem() << endl;
			cout << endl;
		}
		else{
			cout << "Error: Empty List!" << endl;
		}
	}
};

int main() {
	List list;	// initialize list

	list.insert(1);
	list.insert(2);
	list.insert(5);
	list.insert(88888);
	list.insert(234);
	list.print();

	cout << "Now try to find 88888" << endl;
	list.find(88888);

	cout << "Now try to find 234" << endl;
	list.find(234);

	cout << "Now try to find a nonexist number" << endl;
	list.find(21412);
	return 0;
}
