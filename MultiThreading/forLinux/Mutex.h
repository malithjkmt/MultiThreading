#pragma once
#include <string>
#include <pthread.h>
#include <time.h>
#include <chrono>

bool locked_Member(int value);
void locked_Insert(int value);
void locked_Delete(int value);
void *kernelFunctionM(void* rank);
float performMutex(int numberOfValues, int numOfOperations, char *map, int noOfThreads);
