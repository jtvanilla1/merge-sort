//Program 4 by Josiah Manning for Theory of Algorithms
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

bool isSorted(double *ptrX, int sizeOfX); //isSorted prototype; checks to see if the series is in ascending order

bool mergeTwoSortedSeries (double * ptrA, int sizeOfA, double * ptrB, int sizeOfB, double * ptrC){ //merge the two sorted vectors
	bool isInService = true;
	int countA = 0, countB = 0, countC = 0;

	isSorted(ptrA, sizeOfA);
	isSorted(ptrB, sizeOfB);

	if (sizeOfA == 0 && sizeOfB == 0)
		return true;
	if (sizeOfA == 0 || sizeOfB == 0) //skips the comparison if one is zero
		goto ZeroSkip;

	if (sizeOfA < 0 || sizeOfB < 0) //if negative, return false
		return false;


	if (isSorted(ptrA, sizeOfA) && isSorted(ptrB, sizeOfB)){
		do{
			if (ptrA[countA] <= ptrB[countB]){ //if A is smaller or equal, add A first
				ptrC[countC] = ptrA[countA];
				countA++;
			}
			else if (ptrA[countA] > ptrB[countB]){ //if A is larger, add B
				ptrC[countC] = ptrB[countB];
				countB++;
			}
			countC++;

			if (countB >= sizeOfB || countA >= sizeOfA) //continues until all of one is merged in
				isInService = false;

		} while (isInService);

	ZeroSkip:
		if (countA >= sizeOfA || sizeOfA == 0){ //if A is done, add remaining B values
			for (countB; countB <= sizeOfB - 1; countB++){ //picks up where countB left off
				ptrC[countC] = ptrB[countB];
				countC++;
			}
		}

		if (countB >= sizeOfB || sizeOfB == 0){ // if B is done, add remaining A values
			for (countA; countA <= sizeOfA - 1; countA++){
				ptrC[countC] = ptrA[countA];
				countC++;
			}
		}
		return true;
	}
	else
		return false;
}



bool isSorted(double *ptrX, int sizeOfX){ //return true if vector is sorted
	if (sizeOfX == 1 || sizeOfX == 0)// if vector is 1 or 0
		return true;
	else if (sizeOfX == 2){ //if vector is 2, check if in order
		if (ptrX[0] > ptrX[1]) //if out of order, false
			return false;
		else
			return true;
	}
	else if (sizeOfX > 2){ //if larger than 2, check each element to see if its in order
		for (int n = 1; n <= sizeOfX; n++){
			if (ptrX[n] < ptrX[n - 1]){ //if any are out of order, false
				return false;
			}
			else
				return true;
		}
	}
}


void mergeSort(double * ptrSeriesToSort, int sizeOfSeries){ //mergesort core function
	double temp;

	//preconditions
	if (sizeOfSeries < 0 || sizeOfSeries == 1)
		return;
	
	if (sizeOfSeries == 2){
		if (ptrSeriesToSort[0] > ptrSeriesToSort[1]){ //if out of order, swap
			temp = ptrSeriesToSort[1];
			ptrSeriesToSort[1] = ptrSeriesToSort[0];
			ptrSeriesToSort[0] = temp;
		}
		return;
	}
	else if (sizeOfSeries > 2){
		//new series
		double *ptrSeries1 = nullptr;
		double *ptrSeries2 = nullptr;

		ptrSeries1 = new double[sizeOfSeries / 2];
		

		//tempCount continues to iterate through both for loops
		for (int n = 0; n <= (sizeOfSeries / 2) - 1; n++)//puts the first half rounded down into series1
			ptrSeries1[n] = ptrSeriesToSort[n];

		ptrSeries2 = new double[sizeOfSeries - (sizeOfSeries / 2)];

		for (int n = 0; n <= sizeOfSeries - (sizeOfSeries / 2) - 1; n++) //puts the remainder into series2
			ptrSeries2[n] = ptrSeriesToSort[n + (sizeOfSeries / 2)];

		//recursively sorts the two subseries
		mergeSort(ptrSeries1, (sizeOfSeries / 2));
		mergeSort(ptrSeries2, (sizeOfSeries - (sizeOfSeries / 2)));

		//when the subseries are successfully sorted, merge them back together
		mergeTwoSortedSeries(ptrSeries1, sizeOfSeries / 2, ptrSeries2, sizeOfSeries - sizeOfSeries / 2, ptrSeriesToSort);

		//free up allocated memory
		delete[] ptrSeries1;
		delete[] ptrSeries2;

		return;
	}
	else
		return;
}


int main(){
Start:
	int n1, n2;
	bool isInService = true;
	char key;
	double *ptrA = nullptr, *ptrB = nullptr, *ptrC = nullptr;
	const string filename = "sortme.txt";
	vector<int> numsTemp;
	int temp;
	

	
	cout << "Program1 for CSCI 400 Theory of Algorithms" << endl
		<< "Fall 2018" << endl
		<< "by Josiah Manning" << endl << endl << endl


		<< "Press any key and a return to perform mergesort algorithm on contents of lomutodata.txt: ";

	cin >> key;

	cout << "Opening file sortme.txt..." << endl;
	ifstream fin(filename);

	cout << "Reading file to memory..." << endl;

	while (fin >> temp) //read all numbers from txt file
		numsTemp.push_back(temp); //add to temporary vector
	
	cout << "Allocating space for mergesort..." << endl << endl;

	n1 = numsTemp.size() / 2;
	n2 = numsTemp.size() - n1;
	ptrA = new double[n1];
	ptrB = new double[n2];
	ptrC = new double[n1 + n2];

	cout << "Splitting vector in half and assigning to pointer arrays...";
	for (int i = 0; i < n1; i++) {
		cout << endl << "ptrA[" << i << "]: " << numsTemp[i];
		ptrA[i] = numsTemp[i];
	}
	cout << endl;

	for (int i = 0; i < n2; i++) {
		cout << endl << "ptrB[" << i << "]: " << numsTemp[i + n1];
		ptrB[i] = numsTemp[i + n1];
	}

	cout << endl << endl << "Sorting series...";

	//sort each series
	mergeSort(ptrA, n1);
	mergeSort(ptrB, n2);

	for (int i = 0; i < n1; i++) {
		cout << endl << "ptrA[" << i << "]: " << ptrA[i];
	}
	cout << endl;

	for (int i = 0; i < n2; i++) {
		cout << endl << "ptrB[" << i << "]: " << ptrB[i];
	}

	cout << endl << endl << "Merging the two sorted series into new array ptrC[]..." << endl
		;
	//merge the two sorted series
	mergeTwoSortedSeries(ptrA, n1, ptrB, n2, ptrC);

	cout << endl << "Final Sorted Array:";
	if (mergeTwoSortedSeries(ptrA, n1, ptrB, n2, ptrC)) {
		for (int i = 0; i < n1 + n2; i++)
			cout << endl << "ptrC[" << i << "]: " << ptrC[i];
	}
	else
		cout << "Series were not properly sorted." << endl;


	delete[] ptrA;
	delete[] ptrB;
	delete[] ptrC;

	
	cout << endl << endl << endl << "Press 'A' and a return to restart, or any other key to exit." << endl;

	cin >> key;

	if (key == 'a' || key == 'A') //restart option
		goto Start;
	else
		return 0;

}
