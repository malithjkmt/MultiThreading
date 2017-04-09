#include "Mutex.h"
#include "LinkedList.h"

using namespace std;
using namespace std::chrono;

pthread_mutex_t mutexLock;
LinkedList linkedList;
int threadCount;
char *mapListM;
int numberOfOperations;

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

void locked_Delete(int value) {
	pthread_mutex_lock(&mutexLock);
	Node* result = linkedList.deleteNode(value);
	pthread_mutex_unlock(&mutexLock);
}


void *kernelFunctionM(void* rank) {
	int myRank = (int)rank;
	int current = myRank*(numberOfOperations / threadCount);
	int end = current + (numberOfOperations / threadCount);
	char operationType;
	for (; current < end; current++) {
		int i = rand();
		operationType = *(mapListM + current);
		if (operationType == 'm') {
			locked_Member(i);
		}
		else if (operationType == 'i') {
			locked_Insert(i);
		}
		else {
			locked_Delete(i);
		}
	}
	return NULL;
}


float performMutex(int numberOfValues, int numOfOperations, char *map, int noOfThreads) {

	numberOfOperations = numOfOperations;
	mapListM = map;
	threadCount = noOfThreads;

	pthread_t* threadHandles;

	//initialize the mutex
	pthread_mutex_init(&mutexLock, NULL);

	/* initialize random seed: */
	srand(time(NULL));

	//initialize the LinkedList
	linkedList.init_list();

	//populate linked list with 1000 elemsts
	for (int i = 0; i < 1000; i++) {
		linkedList.insert(rand());
	}

	high_resolution_clock::time_point t1 = high_resolution_clock::now();

	//initialize pthread
	threadHandles = new pthread_t[threadCount];

	int rc;
	for (int thread = 0; thread < threadCount; thread++) {
		rc = pthread_create(&threadHandles[thread], NULL, kernelFunctionM, (void*)thread);
		if (rc) {
			cout<<"ERROR; return code from pthread_create() is " << rc<< endl;
			exit(-1);
		}
	}

	for (int thread = 0; thread < threadCount; thread++) {
		rc = pthread_join(threadHandles[thread], NULL);
		if (rc) {
			cout << "ERROR; return code from pthread_join() is " << rc<< endl;
			exit(-1);
		}
	}

	pthread_mutex_destroy(&mutexLock);

	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(t2 - t1).count();
	return duration / 1000000.0;
	//cout << "\nFinal Length: " << linkedList.list_length() << endl << endl;
}