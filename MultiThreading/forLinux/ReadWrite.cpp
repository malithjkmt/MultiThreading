#include "ReadWrite.h"
#include "LinkedList.h"

using namespace std;
using namespace std::chrono;

pthread_rwlock_t rwlock;
LinkedList linkedListRW;
int threadCountRW;
char *mapListRW;
int numberOfOperationsRW;

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

void *kernelFunctionRW(void* rank) {
	int myRank = (int)rank;
	int current = myRank*(numberOfOperationsRW / threadCountRW);
	int end = current + (numberOfOperationsRW / threadCountRW);
	char operationType;
	for (; current < end; current++) {
		int i = rand();
		operationType = *(mapListRW + current);
		if (operationType == 'm') {
			locked_MemberRW(i);
		}
		else if (operationType == 'i') {
			locked_InsertRW(i);
		}
		else {
			locked_DeleteRW(i);
		}
	}
	return NULL;
}

float performReadWrite(int numberOfValues, int numOfOperations, char *map, int noOfThreads) {
	numberOfOperationsRW = numOfOperations;
	mapListRW = map;
	threadCountRW = noOfThreads;

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
	threadHandles = new pthread_t[threadCountRW];

	int rc;
	for (int thread = 0; thread < threadCountRW; thread++) {
		rc = pthread_create(&threadHandles[thread], NULL, kernelFunctionRW, (void*)thread);
		if (rc) {
			cout << "ERROR; return code from pthread_create() is " << rc << endl;
			exit(-1);
		}
	}

	for (int thread = 0; thread < threadCountRW; thread++) {
		rc = pthread_join(threadHandles[thread], NULL);
		if (rc) {
			cout << "ERROR; return code from pthread_join() is " << rc << endl;
			exit(-1);
		}
	}


	pthread_rwlock_destroy(&rwlock);
	//pthread_exit(NULL);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	return duration / 1000000.0;
	//cout << "\nFinal Length: " << linkedListRW.list_length() << endl << endl;
}