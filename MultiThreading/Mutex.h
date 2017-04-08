#include <iostream>
#include <string>
#include <pthread.h>
#include <time.h>
#include <chrono>
#include "LinkedList.h"


bool locked_Member(int value);
void locked_Insert(int value);
Node* locked_Delete(int value);
void *kernelFunction(void* type);
void performMutex(int numberOfValues, int numberOfOperations, char *mapList);
