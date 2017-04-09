#pragma once
#include <iostream>
#include <string>
#include <pthread.h>
#include <time.h>
#include <chrono>

bool locked_MemberRW(int value);
void locked_InsertRW(int value);
void locked_DeleteRW(int value);
void *kernelFunctionRW(void* type);
float performReadWrite(int numberOfValues, int numOfOperations, char *map, int noOfThreads);
