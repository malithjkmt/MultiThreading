#include "Serial.h"
#include "LinkedList.h"

using namespace std;
using namespace std::chrono;

void performSerial(int numberOfValues, int numberOfOperations, char *mapList){
	//create Linked List
	LinkedList linkedList;
	linkedList.init_list();

	/* initialize random seed: */
	srand(time(NULL));

	/*populate Linked list with n random, but unique values.*/
	for (int i = 0; i < numberOfValues; i++) {
		linkedList.insert(rand());
	}
	//linkedList.printList();

	/* initialize random seed: */
	srand(time(NULL));

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	/*perform random Member, Insert, and Delete operations simultaneously*/
	for (int i = 0; i < numberOfOperations; i++) {
		if (*(mapList + i) == 'm') {
			//cout << i << "th one: m\n";
			linkedList.member(rand());
		}
		else if (*(mapList + i) == 'i') {
			//cout << i << "th one: i\n";
			linkedList.insert(rand());
		}
		else {
			//cout << i << "th one: d\n";
			linkedList.deleteNode(rand());
		}
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Serial: " << duration/1000000.0 <<" s";
	cout << "\nFinal Length: " << linkedList.list_length() << endl << endl;

}