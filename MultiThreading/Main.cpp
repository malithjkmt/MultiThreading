#include <iostream>
#include <iostream>
#include "Serial.h"
#include "Mutex.h"
#include "RandomSequence.h"

using namespace std;

int getNumberOftrials() {
	// TODO:
	return 1;
}

void printCaseDetails(int caseNo, float percentageMems, float percentageIns, float percentageDels) {
	cout << "Case " << caseNo << " : member = " << percentageMems * 100 << "% \t insert = " << percentageDels*100 << "% \t delete = " <<percentageDels*100 <<"%" << endl;
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
	
	performSerial(numberOfValues,numberOfOperations, mapList);
	performMutex(numberOfValues,numberOfOperations, mapList);

	// case 2
	percentageMems = 0.90f;
	percentageIns = 0.05f;
	percentageDels = 0.05f;
	printCaseDetails(2, percentageMems, percentageIns, percentageDels);

	//get mapList
	mapList = generateSequence(numberOfOperations, percentageMems, percentageIns, percentageDels);
	
	performSerial(numberOfValues, numberOfOperations, mapList);
	performMutex(numberOfValues, numberOfOperations, mapList);

	// case 3
	percentageMems = 0.50f;
	percentageIns = 0.25f;
	percentageDels = 0.25f;
	printCaseDetails(3, percentageMems, percentageIns, percentageDels);

	//get mapList
	mapList = generateSequence(numberOfOperations, percentageMems, percentageIns, percentageDels);
	
	performSerial(numberOfValues, numberOfOperations, mapList);
	performMutex(numberOfValues, numberOfOperations, mapList);

	//hold the program
	system("pause");
	return 0;
}