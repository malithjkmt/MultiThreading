#include <iostream>
#include <string>
using namespace std;

typedef int E;
class Node {
private:
	E value;
	Node *next;

public:
	E Node::getValue();
	void Node::setValue(E val);
	Node* Node::getNext();
	void Node::setNext(Node *newNode);
};

E Node::getValue() {
	return value;
}

void Node::setValue(E val) {
	value = val;
}

Node* Node::getNext() {
	return next;
}

void Node::setNext(Node *newNode) {
	next = newNode;
}

class LinkedList {
private:
	Node *head;
	int length;

public:
	void LinkedList::init_list();
	bool LinkedList::is_list_empty();
	Node* LinkedList::search(E value);
	bool LinkedList::member(E value);
	Node* LinkedList::deleteNode(E value);
	void LinkedList::insert(E value);
	int LinkedList::list_length();
	void LinkedList::printList();
};

void LinkedList::init_list() {
	head = NULL;
	length = 0;
}

bool LinkedList::is_list_empty() {
	if (length == 0) {
		return true;
	}
	return false;
}

bool LinkedList::member(E value) {
	Node *finder = head;
	while (finder) {
		if (finder->getValue() == value) {
			return 1;
		}
		finder = (finder->getNext());
	}
	return 0;
}

Node* LinkedList::search(E value) {
	Node *finder = head;
	while (finder) {
		if (finder->getValue() == value) {
			return finder;
		}
		finder = (finder->getNext());
	}
	return NULL;
}

Node* LinkedList::deleteNode(E value) {
	if (head == NULL) {
		return NULL;
	}

	//if not NULL
	Node *finder = head->getNext();
	Node *previous = head;

	//if head has the value;
	if (head->getValue() == value) {
		finder = head;
		head = (head->getNext());
		length--;
		return finder;
	}

	//if head is not equal to the value
	while (finder) {
		if (finder->getValue() == value) {
			previous->setNext(finder->getNext());
			finder->setNext(NULL);
			length--;
			return finder;
		}
		previous = finder;
		finder = finder->getNext();
	}
	return NULL;
}

void LinkedList::insert(E value) {
	Node *newNode = new Node;
	newNode->setValue(value);
	newNode->setNext(head);
	head = newNode;
	length++;
}

int LinkedList::list_length() {
	return length;
}

void LinkedList::printList() {
	if (head == NULL) {
		cout << "Empty List";
	}
	Node* finder = head;
	int i = 1;
	while (finder != NULL) {
		//cout << "qwe ";
		cout << "value no:" << i << "- " << finder->getValue() << "\n";
		finder = finder->getNext();
		i++;
	}
	cout << "Lngth is: " << length << endl;
}
