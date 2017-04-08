#include <iostream>
#include <string>
#include <time.h>

char *generateSequence(int numberOfOperations, float pecentageMems, float pecentageIns, float pecentageDels) {
	/*
	crate a char array
	member = 'm'
	insert = 'i'
	delete = 'd'
	*/
	char *mapList = new char[numberOfOperations];

	int mems, ins, dels;
	//add 0.5 because of we want round rather than truncate
	mems = (int)(numberOfOperations * pecentageMems + 0.5);
	ins = (int)(numberOfOperations * pecentageIns + 0.5);
	dels = (int)(numberOfOperations * pecentageDels + 0.5);

	/* initialize random seed: */
	srand(time(NULL));

	for (int i = 0; i < numberOfOperations; i++) {
		int j = rand() % 3;
		if (mems != 0 && j == 0) {
			*(mapList + i) = 'm';
			mems--;
		}
		else if (ins != 0 && j == 1) {
			*(mapList + i) = 'i';
			ins--;
		}
		else if (dels != 0 && j == 2) {
			*(mapList + i) = 'd';
			dels--;
		}
		else {
			i--;
		}

	}
	return mapList;
}