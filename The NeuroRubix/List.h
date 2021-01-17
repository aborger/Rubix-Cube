#pragma once
#include <iostream>

using namespace std;
// Doubly linked list so sort is faster
// Creates a template so the list can be used again
template <typename ItemType>
class List
{
private:
	struct Node 
	{
		ItemType data;
		Node *next;
		Node *prev;
	};
	// declares a head and tail of list (beginning and end)
	Node *head, *tail;
	Node *current;
public:
	// Constructor sets head and tail to NULL
	List<ItemType>() {
		head = NULL;
		tail = NULL;
	}

	// Creates a new node at the end of the list and fills it with "newData"
	void newNodeTail(ItemType newData) {
		Node *testNode = new Node;
		testNode->data = newData;
		testNode->next = NULL;
		testNode->prev = NULL;
		if (head == NULL) { // if head is empty put as head and tail
			head = testNode;
			tail = testNode;
			testNode = NULL; // deletes pointer, because "delete newNode" causes error
		}
		else { // if not, old tail next = newNode, and tail now = newNode
			tail->next = testNode;
			testNode->prev = tail;
			tail = testNode;
		}
	}

	void newNodeHead(ItemType newData) {
		Node *newNode = new Node;
		newNode->data = newData;
		newNode->next = NULL;
		newNode->prev = NULL;
		if (head == NULL) { // if head is empty put as head and tail
			head = newNode;
			tail = newNode;
			newNode = NULL;
		}
		else { // if not, old tail next = newNode, and tail now = newNode
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
	}
	// Puts Nodes in order as they are created
	void newSortedNode(ItemType newData) {
		Node *newNode = new Node;
		newNode->data = newData;
		newNode->next = head; // puts new node "behind" head
		if (head == NULL) { // if head is empty put as head and tail
			head = newNode;
			tail = newNode;
			newNode->next = NULL;
			newNode->prev = NULL;
			newNode = NULL;
		}
		else {
			if (newData <= head->data) { // if newData is less than head, make newData head and point to old head
				newNode->next = head;
				head->prev = newNode;
				head = newNode;
			}
			else {
				if (newNode->next->next == NULL) { // only head and new node in list
					head->next = newNode;
					newNode->prev = head;
					newNode->next = NULL;
					tail = newNode;
				}
				else {
					newNode->next = head->next; //move newNode to the right of head
					head->next->prev = newNode;
					head->next = newNode;
					newNode->prev = head;

					bool breakLoop = false;
					do {
						if (newData <= newNode->next->data) {
							// newNode is in the right spot
							breakLoop = true;
						}
						else {
							// moves newNode to the right of newNode->next, but instead of changing its nexts and previouses it swaps the data
							ItemType temp = newNode->data;
							newNode->data = newNode->next->data;
							newNode->next->data = temp;
							newNode = newNode->next;
						}
					} while (newNode->next != NULL && breakLoop == false);
				}
			}
		}
	}

	int getListSize() {
		int size = 0;
		Node *nextNode = head;
		while (nextNode != NULL) {
			nextNode = nextNode->next;
			size++;
		}
		return size;
	}

	void setAt(int element, ItemType newData) {
		Node *temp = head;
		for (int a = 0; a < element; a++) {
			temp = temp->next;
		}
		if (temp == NULL) {
			cout << "Element was empty" << endl;
		}
		temp->data = newData;
	}

	ItemType getAt(int element) {
		Node *temp = head;
		for (int a = 0; a < element; a++) {
			temp = temp->next;
		}
		if (temp == NULL) {
			cout << "Element was empty" << endl;
		}
		return temp->data;
	}

	ItemType getBack() {
		return tail->data;
	}

	void deleteAt(int element) {
		if (head != NULL) { 
			Node *temp = head;
			for (int a = 0; a < element; a++) {
				temp = temp->next;
			}
			if (head == tail) { // delete only element
				head = NULL;
				delete temp;
			}
			else if (temp->next == NULL) {// delete last element in list
				temp->prev->next = NULL;
				tail = temp->prev;
				delete temp;
			}
			else {
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
			}
		}
	}

	// If searchTerm is in list, returns the items element, if not returns -1
	int contains(ItemType search) {
		Node *temp = head;
		int currentElement = 0;
		while (temp != NULL) {
			if (temp->data == search) { // check if searchTem has been found
				return currentElement;
			}
			else { // go to next element
				temp = temp->next;
				currentElement++;
			}
		}
		// not in list
		delete temp;
		return -1;
	}

	/*ItemType returnThrough() {  makes it faster

	}*/

	void setCurrent(ItemType newData) {
		current->data = newData;
	}


	ItemType getCurrent() {
		return current->data;
	}


	void nextCurrent() {
		current = current->next;
	}


	void tailCurrent() {
		current = tail;
	}

	void prevCurrent() {
		current = current->prev;
	}


	void resetCurrent() {
		current = head;
	}


	~List<ItemType>() {
	}



};

