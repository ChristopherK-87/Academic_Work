/*
PROGRAMMING ASSIGNMENT #1


AUTHOR: CHRISTOPHER KOEPKE
CLASS:  CS 3010.02


This program is designed to solve a system of equations using
Gaussian elimination with Scaled Partial Pivoting.

The user will first input the number of equations and than the values
of each of the three coeffients and the results for each equation, either 
manully through the console or with a file input.
*/

#include <iostream>
#include <fstream>
#include <istream>
#include <iomanip>
using namespace std;
int numberOfEquations();
int menuChoice();
void displayMatrix(float[][3], float[], int);
void manualInput(float[][3], float[], int[], int);
bool fileInput(float[][3], float[], int[], int);
void scRatio(float[][3], float[], int[], int, int);
void equationMultiplier(float[][3], float[], int[], int, int, int);
int findPivot(float[], int, int);
void calculateIntermediateMatrix(float[][3], float[], float[], int, int, int);
void rowSwitch(float[][3], float[], int[], int, int, int);
void backSubstitution(float[][3], float[]);


int main() {
	// LOCAL VARIABLES
	int const MAXARRAYSIZE = 10;
	int const NUMOFVARIABLES = 3;
	int numOfEquations = 0;
	int choice = 99;
	int idxStart = 0;
	int pivot = 0;
	// ARRAY INITIALIZATIONS 
	float coefficientMatrix[MAXARRAYSIZE][NUMOFVARIABLES] = { 0 };
	float equationResults[MAXARRAYSIZE] = { 0 };	
	float scaledRatio[MAXARRAYSIZE] = { 0 };
	float multiplier[MAXARRAYSIZE] = { 0 };
	int indexVector[MAXARRAYSIZE] = { 0 };

	// FUNCTION CALLS FOR NUMBER OF EQUATIONS AND INPUT METHOD CHOICE
	numOfEquations = numberOfEquations();
	choice = menuChoice();

	// FUNCTION CALL FOR MANUAL INPUT
	if (choice == 0)
		manualInput(coefficientMatrix, equationResults, indexVector, numOfEquations);

	// FUNCTION CALL FOR FILE INPUT. IF INPUT IS BAD, EXIT_FAILURE
	if (choice == 1) {
		bool badInput = fileInput(coefficientMatrix, equationResults, indexVector, numOfEquations);	
		if (badInput) {
			cout << "INVALID FILE. PROGRAM EXITING.";
			return EXIT_FAILURE;
		}
	}

	// DISPLAY INPUT MATRIX
	cout << "\nORIGINAL MATRIX" << endl;
	displayMatrix(coefficientMatrix, equationResults, numOfEquations);

	// FIND MAX VALUE PER COLUMN AND CALCULATE SCALED RATIO
	scRatio(coefficientMatrix, scaledRatio, indexVector, numOfEquations, idxStart);

	// DISPLAY INDEX VECTOR
	cout << "\nINDEX VECTOR = | ";
	for (int index = 0; index < numOfEquations; index++) {
		cout << setw(3) << indexVector[index]+1;
		if (index < numOfEquations - 1)
			cout << ", ";
		if (index == numOfEquations - 1)
			cout << " |" << endl;
	}	

	// FIND THE PIVOT
	pivot = findPivot(scaledRatio, numOfEquations, idxStart);
	
	// CALCULATE MULTIPLIER
	equationMultiplier(coefficientMatrix, multiplier, indexVector, numOfEquations, pivot, idxStart);

	// CALCULATE INTERMEDIATE MATRIX
	calculateIntermediateMatrix(coefficientMatrix, multiplier, equationResults, pivot, numOfEquations, idxStart);

	// SWITCH PIVOT ROW WITH FIRST ROW OF THE INTERATION
	rowSwitch(coefficientMatrix, equationResults, indexVector, pivot, numOfEquations, idxStart);	
	
	// DISPLAY INTERMEDIATE MATRIX
	cout << "PIVOT ROW: " << pivot + 1 << endl;
	cout << "\nMATRIX AFTER PARTIAL PIVOT" << endl;
	displayMatrix(coefficientMatrix, equationResults, numOfEquations);
	
	// DISPLAY NEW INDEX VECTOR
	cout << "\nNEW INDEX VECTOR = | ";
	for (int index = 0; index < numOfEquations; index++) {
		cout << setw(3) << indexVector[index] + 1;
		if (index < numOfEquations - 1)
			cout << ", ";
		if (index == numOfEquations - 1)
			cout << " |" << endl;
	}
	
	// FIND NEXT MAX VALUE PER COLUMN AND CALCULATE THE NEXT SCALED RATIO
	scRatio(coefficientMatrix, scaledRatio, indexVector, numOfEquations, idxStart + 1);
	
	// FIND THE NEXT PIVOT
	pivot = findPivot(scaledRatio, numOfEquations, idxStart+1);

	// CALCULATE NEW MULTIPLIER
	equationMultiplier(coefficientMatrix, multiplier, indexVector, numOfEquations, pivot, idxStart + 1);
	
	// CALCULATE NEW INTERMEDIATE MATRIX
	calculateIntermediateMatrix(coefficientMatrix, multiplier, equationResults, pivot, numOfEquations, idxStart + 1);
	
	// DISPLAY NEW INTERMEDIATE MATRIX
	cout << "PIVOT ROW: " << pivot + 1 << endl;
	cout << "\nMATRIX AFTER PARTIAL PIVOT" << endl;
	displayMatrix(coefficientMatrix, equationResults, numOfEquations);

	// DISPLAY NEW INDEX VECTOR
	cout << "\nNEW INDEX VECTOR = | ";
	for (int index = 0; index < numOfEquations; index++) {
		cout << setw(3) << indexVector[index] + 1;
		if (index < numOfEquations - 1)
			cout << ", ";
		if (index == numOfEquations - 1)
			cout << " |" << endl;
	}
	
	// CALCULATE AND DISPLAY SOLUTIONS TO VARIABLES
	backSubstitution(coefficientMatrix, equationResults);

	cout << "PLEASE PRESS \'ENTER\' TO EXIT THE PROGRAM.";
	cin.clear();
	cin.ignore();
	cin.get();
	return 0;
}// ** END OF MAIN **
//////////////////////////////////////////////////////////////////////////////////////////////////////


// ASKING USER TO THE NUMBER OF EQUATIONS TO SOLVE. INVALID INPUT ENDS PROGRAM //
int numberOfEquations(){	
	int num;
	cout << "Please enter the number of equations you would like to solve (up to 10 equations): ";
	cin >> num;
	if (num < 1 || num > 10 || cin.fail()) {
		cout << "INVALID INPUT. EXITING PROGRAM";
		cin.clear();
		exit(0);
	}
	return num;
} //END OF numberOfEquations()


// ASKING USER FOR EITHER MANUAL INPUT OR INPUT FROM A FILE. INVALID INPUT ENDS PROGRAM //
int menuChoice() {
	int num;
	cout << "To load equations from a file please enter 1, for manual input please enter 0: ";
	cin >> num;
	if ( num < 0 || num > 1 || cin.fail()) {
		cout << "INVALID INPUT. EXITING PROGRAM";
		cin.clear();
		exit(0);
	}
	return num;
} //END OF menuChoice()


// FUNCTION TO DISPLAY MATRIX ARRAY
void displayMatrix(float arr[][3], float eqrArr[], int numOfEq) {
	int const NUMOFVARIABLES = 3;
	
	for (int index = 0; index < numOfEq; index++) {
		for (int idx = 0; idx < NUMOFVARIABLES; idx++) {
			if (idx == 0) {
				cout << "| ";
				printf("%6.3F", arr[index][idx]);
				cout << " ";
			}
			else {
				printf("%6.3F", arr[index][idx]);
				cout << " ";
			}
		}
		cout << " | ";
		printf("%6.3F", eqrArr[index]);
		cout << " |" << endl;
	}
}// END OF displayMatrix()


// FUNCTION TO GENERATE MATRIX VALUES USING MANUAL INPUT
void manualInput(float arr[][3], float eqr[], int idxVector[], int numOfEq) {
	int const NUMOFVARIABLES = 3;
	char arrayVariables[] = { 'x', 'y', 'z' };
	for (int index = 0; index < numOfEq; index++) {
		for (int idx = 0; idx < NUMOFVARIABLES; idx++) {
			cout << "Please enter the coefficients for row " << index + 1 << " and variable " << arrayVariables[idx] << ". Please include Zero values:  ";
			cin >> arr[index][idx];
			cin.clear();
		}
		cout << "Please enter the equation's resulting value: ";
		cin >> eqr[index];
		idxVector[index] = index;
		cin.clear();

	}
	cin.clear();
}// END OF manualInput()


// FUNCTION TO GENERATE MATRIX VALUES USING FILE INPUT. RETURN false IF FILE EXISTS, ELSE true
bool fileInput(float arr[][3], float eqr[], int idxVector[], int numOfEq) {
	string inputLine;
	string fileLocation;
	ifstream inFile;
	int const NUMOFVARIABLES = 3;
	
	while (fileLocation.empty()) {
		cout << "Please enter the file name: ";
		cin >> fileLocation;
	}
	inFile.open(fileLocation.c_str());
	cin.clear();
	if (inFile.is_open()) {
		for (int index = 0; index < numOfEq; index++) {
			for (int idx = 0; idx < NUMOFVARIABLES; idx++) {
				inFile >> arr[index][idx];
			}
			inFile >> eqr[index];
			idxVector[index] = index;
		}
		inFile.close();
		return false;
	}
	else {
		inFile.close();
		return true;
	}	
}// END OF fileInput()


// CALCULATE THE SCALED RATIO
void scRatio(float arr[][3], float scRatio[], int idxVector[], int numOfEq, int start) {
	float columnMax = 0;
	int const NUMOFVARIABLES = 3;
	
	for (int index = start; index < numOfEq; index++) {
		for (int idx = start; idx < NUMOFVARIABLES; idx++) {
			if (columnMax < arr[index][idx]) {
				columnMax = arr[index][idx];				
			}
		}
		scRatio[index] = abs(float(arr[index][start]) / float(columnMax));
		columnMax = 0;
	}
}// END OF scRatio()


// FUNCTION TO CALCULATE MULTIPLIERS FOR EACH INTERATION
void equationMultiplier(float arr[][3], float multiArr[], int idxVector[], int numOfEq, int pivot, int start) {	
	for (int index = 0; index < numOfEq; index++)
		multiArr[index] = 0;


	for (int index = start; index < numOfEq; index++) {
		if (index != pivot) {
			multiArr[index] = float(arr[index][start]) / float(arr[pivot][start]);
		}
		if (index == pivot) {
			int currentIndex = index;
			idxVector[index] = idxVector[start];
			idxVector[start] = currentIndex;
		}
		if (index == start) {
			cout << "MULTIPLIER: ";
			printf("%04.3F", multiArr[index]);
		}
		else {
			cout << ", ";
			printf("%04.3F", multiArr[index]);
		}

	}
	cout << endl;
}// END OF equationMultiplier()


// FUNCTION TO FIND THE PIVOT AT EACH INTERATION
int findPivot(float scRatio[], int numOfEq, int start) {
	int pivot = 0;
	float temp = 0;

	cout << "SCALED RATIOS = | ";
	for (int index = start; index < numOfEq; index++) {
		printf("%04.3F", scRatio[index]);
		if (index < numOfEq - 1)
			cout << ", ";
		if (temp < scRatio[index]) {
			temp = scRatio[index];
			pivot = index;
		}
		if (index == numOfEq - 1)
			cout << " |" << endl;
	}
	return pivot;
}// END OF findPivot()


// FUNCTION TO CALCULATE INTERMEDIATE EQUATION VALUES AND POPULATE ANOTHER ARRAY
void calculateIntermediateMatrix(float arr[][3], float multiArr[], float eqrArr[], int pivot, int numOfEq, int start) {
	int const NUMOFVARIABLES = 3;
	float tempArr[10][10] = { 0 };
	for (int index = start; index < numOfEq; index++) {
		for (int idx = start; idx < NUMOFVARIABLES; idx++) {
			if (index != pivot) {
				tempArr[index][idx] = (arr[index][idx] - (multiArr[index] * arr[pivot][idx]));
				arr[index][idx] = tempArr[index][idx];
			}
				//interArr[index][idx] = (arr[index][idx] - (multiArr[index] * arr[pivot][idx]));

			/*if (index == pivot) 			
				interArr[index][idx] = arr[index][idx];
			*/
		}
		if (index != pivot)
			eqrArr[index] = eqrArr[index] - float(multiArr[index] * eqrArr[pivot]);
	}
}// END OF calculateIntermediateMatrix()

// FUNCTION TO SWITCH PIVOT ROW WITH THE FIRST ROW IN EACH INTERATION
void rowSwitch(float arr[][3], float eqrArr[], int idxVector[], int pivot, int numOfEq, int start) {
	int const NUMOFVARIABLES = 3;
	float tempArr[10];
	float temp;
	int idxVectorTemp;

	for (int index = start; index < start+1; index++) {
		for (int idx = start; idx < NUMOFVARIABLES; idx++) {
			tempArr[idx] = arr[index][idx];
			arr[index][idx] = arr[pivot][idx];
			arr[pivot][idx] = tempArr[idx];
		}
		temp = eqrArr[index];
		eqrArr[index] = eqrArr[pivot];
		eqrArr[pivot] = temp;
		if (index == pivot) {
			idxVectorTemp = idxVector[index];
			idxVector[index] = idxVector[pivot];
			idxVector[pivot] = idxVectorTemp;
		}
	}
}// END OF rowSwitch()

void backSubstitution(float arr[][3], float eqrArr[]) {
	float varValue[3] = { 0 };
	varValue[2] = eqrArr[2] / arr[2][2];	
	varValue[1] = (eqrArr[1] - (arr[1][2] * varValue[2])) / arr[1][1];
	varValue[0] = (eqrArr[0] - (arr[0][2] * varValue[2] + arr[0][1] * varValue[1])) / arr[0][0];

	char arrayVariables[] = { 'X', 'Y', 'Z' };
	cout << "\n** Solution **" << endl;
	for (int index = 0; index < 3; index++) {
		cout << arrayVariables[index] << " = " << varValue[index] << endl;
	}
}// END OF backSubstituion()