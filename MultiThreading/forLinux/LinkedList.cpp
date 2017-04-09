#include "LinkedList.h"

using namespace std;

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
	while (finder != NULL && finder->getValue() < value) {
		finder = finder->getNext();
	}

	if (finder == NULL) {
		return 0;
	}

	if (finder->getValue() == value) {
		return 1;
	}
	return 0;
}

Node* LinkedList::search(E value) {
	Node *finder = head;
	while (finder != NULL && finder->getValue() < value) {
		finder = finder->getNext();
	}

	if (finder == NULL) {
		return 0;
	}

	if (finder->getValue() == value) {
		return finder;
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
	while (finder != NULL && finder->getValue() < value) {
		previous = finder;
		finder = finder->getNext();
	}

	if (finder == NULL) {
		return NULL;
	}

	if (finder->getValue() == value) {
		previous->setNext(finder->getNext());
		finder->setNext(NULL);
		length--;
		return finder;
	}
	return NULL;
}

void LinkedList::insert(E value) {
	Node *newNode = new Node;
	newNode->setValue(value);
	if (head == NULL) {
		head = newNode;
		newNode->setNext(NULL);
		length++;
		return;
	}
	Node* finder = head->getNext();
	Node* previous = head;

	//if head is largerthan value
	if (head->getValue() > value) {
		newNode->setNext(head);
		head = newNode;
		length++;
		return;
	}

	//if head is equal to value;
	if (head->getValue() == value) {
		newNode->setValue(value - 1);
		newNode->setNext(head);
		head = newNode;
		length++;
		return;
	}

	while (finder != NULL && finder->getValue() < value) {
		previous = finder;
		finder = finder->getNext();
	}

	if (finder == NULL) {
		previous = newNode;
		newNode->setNext(NULL);
		length++;
		return;
	}

	if (finder->getValue() != value) {
		previous->setNext(newNode);
		newNode->setNext(finder);
		length++;
		return;
	}
	else {
		/*
		if value already exist we insert
		incremented value to suitable place
		*/
		insertNext(finder);
		length++;
	}
}

void LinkedList::insertNext(Node* finder) {
	Node* previous = finder;
	finder = finder->getNext();
	int value = previous->getValue() + 1;
	while (finder!= NULL && finder->getValue() == value) {
		previous = finder;
		finder = finder->getNext();
		value++;
	}
	Node* newNode = new Node;
	newNode->setValue(value);
	newNode->setNext(finder);
	previous->setNext(newNode);
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
		cout << "qwe";
		cout << "value no:" << i << "- " << finder->getValue() << "\t";
		finder = finder->getNext();
		i++;
	}
	cout << "Lngth is: " << length << endl;
}
