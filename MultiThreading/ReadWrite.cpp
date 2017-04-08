#include "ReadWrite.h"
#include "LinkedList.h"

using namespace std;
using namespace std::chrono;

pthread_rwlock_t rwlock;
LinkedList linkedListRW;

bool locked_MemberRW(int value) {
	pthread_rwlock_rdlock(&rwlock);
	bool result = linkedListRW.member(value);
	pthread_rwlock_unlock(&rwlock);
	return (void*)result;
}

void locked_InsertRW(int value) {
	pthread_rwlock_wrlock(&rwlock);
	linkedListRW.insert(value);
	pthread_rwlock_unlock(&rwlock);
}

void locked_DeleteRW(int value) {
	pthread_rwlock_wrlock(&rwlock);
	Node* result = linkedListRW.deleteNode(value);
	pthread_rwlock_unlock(&rwlock);
}


void *kernelFunctionRW(void* type) {
	char operationType = (char)type;
	int i = rand();
	if (operationType == 'm') {
		locked_MemberRW(i);
	}
	else if (operationType == 'i') {
		locked_InsertRW(i);
	}
	else {
		locked_DeleteRW(i);
	}
	return NULL;
}

void performReadWrite(int numberOfValues, int numberOfOperations, char *mapList) {
	pthread_t* threadHandles;

	//initialize the rwlock
	pthread_rwlock_init(&rwlock, NULL);

	/* initialize random seed: */
	srand(time(NULL));

	//initialize the LinkedList
	linkedListRW.init_list();

	//populate linked list with 'numberOfValues' elemsts
	for (int i = 0; i < numberOfValues; i++) {
		linkedListRW.insert(rand());
	}

	/* initialize random seed: */
	srand(time(NULL));

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	//initialize pthread
	threadHandles = new pthread_t[numberOfOperations];

	for (int thread = 0; thread < numberOfOperations; thread++) {
		pthread_create((threadHandles + thread), NULL, kernelFunctionRW, (void*)*(mapList + thread));
	}

	for (int thread = 0; thread < numberOfOperations; thread++) {
		pthread_join(*(threadHandles + thread), NULL);
	}

	pthread_rwlock_destroy(&rwlock);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "RW: " << duration / 1000000.0 << " s";
	cout << "\nFinal Length: " << linkedListRW.list_length() << endl << endl;
}