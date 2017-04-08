#include <iostream>
#include <string>

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
	void LinkedList::insertNext(Node* finder);
};

