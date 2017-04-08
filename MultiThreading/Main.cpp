#include <iostream>
#include <string>
#include <time.h>
#include "RandomSequence.h"
#include "LinkedList.h"

using namespace std;

int main() {
	//create Linked List
	LinkedList linkedList;
	linkedList.init_list();

	/* initialize random seed: */
	srand(time(NULL));

	for (int i = 0; i < 1000; i++) {
		linkedList.insert(rand());
	}
	linkedList.printList();
	system("pause");

	int numberOfOperations = 1000;
	//get mapList
	char *mapList = generateSequence(numberOfOperations, 0.50, 0.25, 0.25);

	/* initialize random seed: */
	srand(time(NULL));
	for (int i = 0; i < numberOfOperations; i++) {
		if (*(mapList + i) == 'm') {
			cout << i << "th one: m\n";
			linkedList.member(rand());
		}
		else if (*(mapList + i) == 'i') {
			cout << i << "th one: i\n";
			linkedList.insert(rand());
		}
		else {
			cout << i << "th one: d\n";
			linkedList.deleteNode(rand());
		}
	}
	cout << "\nFinal Length is: " << linkedList.list_length() << endl;

	//hold the program
	system("pause");
	return 0;
}