#include "Mutex.h"

using namespace std;
using namespace std::chrono;

pthread_mutex_t mutexLock;
LinkedList linkedList;

bool locked_Member(int value) {
	pthread_mutex_lock(&mutexLock);
	bool result = linkedList.member(value);
	pthread_mutex_unlock(&mutexLock);
	return (void*)result;
}

void locked_Insert(int value) {
	pthread_mutex_lock(&mutexLock);
	linkedList.insert(value);
	pthread_mutex_unlock(&mutexLock);
}

Node* locked_Delete(int value) {
	pthread_mutex_lock(&mutexLock);
	Node* result = linkedList.deleteNode(value);
	pthread_mutex_unlock(&mutexLock);
	return result;
}


void *kernelFunction(void* type) {
	char operationType = (char)type;
	int i = rand();
	if (operationType == 'm') {
		locked_Member(i);
	}
	else if (operationType == 'i') {
		locked_Insert(i);
	}
	else {
		locked_Delete(i);
	}
	return NULL;
}

void performMutex(int numberOfValues, int numberOfOperations, char *mapList){
	pthread_t* threadHandles;

	//initialize the mutex
	pthread_mutex_init(&mutexLock, NULL);

	/* initialize random seed: */
	srand(time(NULL));

	//initialize the LinkedList
	linkedList.init_list();

	//populate linked list with 'numberOfValues' elemsts
	for (int i = 0; i < numberOfValues; i++) {
		linkedList.insert(rand());
	}

	/* initialize random seed: */
	srand(time(NULL));

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	//initialize pthread
	threadHandles = new pthread_t[numberOfOperations];

	for (int thread = 0; thread < numberOfOperations; thread++) {
		pthread_create((threadHandles + thread), NULL, kernelFunction, (void*)*(mapList + thread));
	}

	for (int thread = 0; thread < numberOfOperations; thread++) {
		pthread_join(*(threadHandles + thread), NULL);
	}

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	cout << "Mutex: " << duration / 1000000.0 << " s";
	cout << "\nFinal Length: " << linkedList.list_length() << endl <<endl;
}