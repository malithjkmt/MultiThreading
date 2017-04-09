#include <iostream>
#include <iostream>
#include <math.h>
#include "Serial.h"
#include "Mutex.h"
#include "RandomSequence.h"
#include "ReadWrite.h"

using namespace std;

int getNumberOftrials() {
	// TODO:
	return 1;
}

float getMean(float data[], int length) {
	float sum = 0.0;

	for (int i = 0; i < length; i++)
	{
		sum += data[i];
	}
	return sum / length;
}

float getSampleStandardDeviation(float data[], int length, float mean)
{
	float var = 0.0;

	for (int i = 0; i < length; i++) {
		var += pow(data[i] - mean, 2);
	}
	return sqrt(var/(length-1));
}

int getNummerOfSamplesToRun(float s, float x) {
	double var = pow((100*1.96*s)/(5*x), 2);
	return (int)(ceil(var));
}

void printCaseDetails(int caseNo, float percentageMems, float percentageIns, float percentageDels) {
	cout << endl << "Case " << caseNo << " : member = " << percentageMems * 100 << "% \t insert = " << percentageDels * 100 << "% \t delete = " << percentageDels * 100 << "%" << endl;
}

void messureTimeSerial(int numberOfValues, int numberOfOperations, char *mapList) {
	int sampleSize = 10;
	float *runTimes = new float[sampleSize];
	for (int i = 0; i < sampleSize; i++)
	{
		runTimes[i] = performSerial(numberOfValues, numberOfOperations, mapList);
	}
	float mean = getMean(runTimes, sampleSize);
	float std = getSampleStandardDeviation(runTimes, sampleSize, mean);
	int n = getNummerOfSamplesToRun(std, mean);
	//cout << "n is " << n << endl;

	// if the default sample size is not enough for 5% accuracy and 95% confidence level
	if (n > sampleSize) {
		//cout << "sample size is not enough, need " << n << endl;
		float *runTimes = new float[n];
		for (int i = 0; i < n; i++)
		{
			runTimes[i] = performSerial(numberOfValues, numberOfOperations, mapList);
		}
		mean = getMean(runTimes, n);
		std = getSampleStandardDeviation(runTimes, n, mean);
	}

	cout << "Serial : ";
	cout << "Mean: " << mean << "s, ";
	cout << "Std: " << std << "s" << endl;	
}


void messureTimeMutex(int numberOfValues, int numberOfOperations, char *mapList, int noOfThreads) {
	int sampleSize = 10;
	float *runTimes = new float[sampleSize];
	for (int i = 0; i < sampleSize; i++)
	{
		runTimes[i] = performMutex(numberOfValues, numberOfOperations, mapList, noOfThreads);
	}

	float mean = getMean(runTimes, sampleSize);
	float std = getSampleStandardDeviation(runTimes, sampleSize, mean);
	int n = getNummerOfSamplesToRun(std, mean);
	//cout << "n is " << n << endl;

	// if the default sample size is not enough for 5% accuracy and 95% confidence level
	if (n > sampleSize) {
		//cout << "sample size is not enough, need " << n << endl;
		float *runTimes = new float[n];
		for (int i = 0; i < n; i++)
		{
			runTimes[i] = performMutex(numberOfValues, numberOfOperations, mapList, noOfThreads);
		}

		mean = getMean(runTimes, n);
		std = getSampleStandardDeviation(runTimes, n, mean);
	}
	cout << "Mutex "<< noOfThreads<< ": ";
	cout << "Mean: " << mean << "s, ";
	cout << "Std: " << std << "s" << endl;
}


void messureTimeReadWrite(int numberOfValues, int numberOfOperations, char *mapList, int noOfThreads) {
	int sampleSize = 10;
	float *runTimes = new float[sampleSize];
	for (int i = 0; i < sampleSize; i++)
	{
		runTimes[i] = performReadWrite(numberOfValues, numberOfOperations, mapList, noOfThreads);
	}

	float mean = getMean(runTimes, sampleSize);
	float std = getSampleStandardDeviation(runTimes, sampleSize, mean);
	int n = getNummerOfSamplesToRun(std, mean);
	//cout << "n is " << n << endl;

	// if the default sample size is not enough for 5% accuracy and 95% confidence level
	if (n > sampleSize) {
		//cout << "sample size is not enough, need " << n << endl;
		float *runTimes = new float[n];
		for (int i = 0; i < n; i++)
		{
			runTimes[i] = performReadWrite(numberOfValues, numberOfOperations, mapList, noOfThreads);
		}

		mean = getMean(runTimes, n);
		std = getSampleStandardDeviation(runTimes, n, mean);
	}
	cout << "RW " << noOfThreads << "   : ";
	cout << "Mean: " << mean << "s, ";
	cout << "Std: " << std << "s" << endl;
}


int main() {
	int numberOfTrials = getNumberOftrials(); // TODO:

	int numberOfValues = 1000;
	int numberOfOperations = 10000;

	// case 1
	float percentageMems = 0.99f;
	float percentageIns = 0.005f;
	float percentageDels = 0.005f;
	printCaseDetails(1, percentageMems, percentageIns, percentageDels);

	//get mapList
	char *mapList = generateSequence(numberOfOperations, percentageMems, percentageIns, percentageDels);

	messureTimeSerial(numberOfValues, numberOfOperations, mapList);

	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 1);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 2);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 4);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 8);

	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 1);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 2);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 4);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 8);
	
	// case 2
	percentageMems = 0.90f;
	percentageIns = 0.05f;
	percentageDels = 0.05f;
	printCaseDetails(2, percentageMems, percentageIns, percentageDels);

	//get mapList
	mapList = generateSequence(numberOfOperations, percentageMems, percentageIns, percentageDels);
	
	messureTimeSerial(numberOfValues, numberOfOperations, mapList);

	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 1);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 2);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 4);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 8);

	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 1);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 2);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 4);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 8);

	// case 3
	percentageMems = 0.50f;
	percentageIns = 0.25f;
	percentageDels = 0.25f;
	printCaseDetails(3, percentageMems, percentageIns, percentageDels);

	//get mapList
	mapList = generateSequence(numberOfOperations, percentageMems, percentageIns, percentageDels);
	
	messureTimeSerial(numberOfValues, numberOfOperations, mapList);

	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 1);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 2);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 4);
	messureTimeMutex(numberOfValues, numberOfOperations, mapList, 8);

	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 1);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 2);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 4);
	messureTimeReadWrite(numberOfValues, numberOfOperations, mapList, 8);

	//hold the program
	cout << endl;
	int k;
	cout << "Enter a int: ";
	cin >> k;
	return 0;
}