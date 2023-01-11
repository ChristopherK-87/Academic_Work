/*
PROGRAMMING ASSIGNMENT #2


AUTHOR: CHRISTOPHER KOEPKE
CLASS:  CS 3010.02


This program is designed to solve a system of equations using
Gaussian elimination with Scaled Partial Pivoting.

The user will first input the number of equations and than the values
of each of the three coeffients and the results for each equation, either
manully through the console or with a file input.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <istream>
#include <cmath>
#include <limits>
using namespace std;

int numberOfEquations();
int menuChoice();
double userMaxError();
void manualInput(double[10][10], double[10], int);
bool fileInput(double[10][10], double[10], int);
void startingSolution(double[10], int);
void jacobiMethod(double[10][10], double[10], double[10], double, int);
void gaussSeidelMethod(double[10][10], double[10], double[10], double, int);


// START OF MAIN
int main() {
	double solutions[10] = { 0 };
	double solutionsCopy[10] = { 0 };
	double eqArray[10][10] = { 0 };
	double eqResult[10] = { 0 };
	int numOfEq = 0;
	int choice = 0;
	double stoppingError = 0;
	double tempCopy = 0;
	


	// ASK USER FOR NUMBER OF EQUATIONS, MANUAL OR FILE INPUT, AND STOPPING ERROR
	numOfEq = numberOfEquations();
	choice = menuChoice();
	stoppingError = userMaxError();
	
	// PERFORM USER CHOICE FOR INPUT. IF INPUT FAILS FOR EITHER CHOICE, END PROGRAM
	if (choice == 0) {
		manualInput(eqArray, eqResult, numOfEq);
	}
	if (choice == 1) {
		bool badInput = fileInput(eqArray, eqResult, numOfEq);
		if (badInput) {
			cout << "INVALID FILE. PROGRAM EXITING.";
			return EXIT_FAILURE;
		}
	}

	// GET STARTING SOLUTION AND THEN PERFORM JACOBI METHOD FOLLOWED BY GAUSS-SEIDEL METHOD (PRINTING OF VALUES PERFORMED IN EACH METHOD)
	cout << endl;
	startingSolution(solutions, numOfEq);
	// COPY STARTING SOLUTION TO A SECOND ARRAY
	for (int index = 0; index < numOfEq; index++) {
		solutionsCopy[index] = solutions[index];
	}
	cout << "\n** JACOBI METHOD **";
	jacobiMethod(eqArray, eqResult, solutions, stoppingError, numOfEq);
	cout << "\n\n** GAUSS-SEIDEL METHOD **";
	gaussSeidelMethod(eqArray, eqResult, solutionsCopy, stoppingError, numOfEq);
	cout << "\n\n ** END OF PROGRAM **";
	

	return 0;
}// END OF main()

// ASKING USER TO THE NUMBER OF EQUATIONS TO SOLVE. INVALID INPUT ENDS PROGRAM //
int numberOfEquations() {
	int num;
	cout << "Please enter the number of equations you would like to solve (up to 10 equations): ";
	cin >> num;
	if (num < 1 || num > 10 || cin.fail()) {
		cout << "INVALID INPUT. EXITING PROGRAM";
		exit(0);
	}
	return num;
} //END OF numberOfEquations()

// ASKING USER FOR EITHER MANUAL INPUT OR INPUT FROM A FILE. INVALID INPUT ENDS PROGRAM //
int menuChoice() {
	int choice;
	cin.ignore(10000, '\n');
	cin.clear();
	cout << "To load equations from a file please enter 1, for manual input please enter 0: ";
	cin >> choice;
	if (choice < 0 || choice > 1 || cin.fail()) {
		cout << "INVALID INPUT. EXITING PROGRAM";
		exit(0);
	}
	return choice;
} //END OF menuChoice()

// ASKING USER FOR THE MAX DESIRED ERROR VALUE TO TEST AGAINST AS A STOPPING POINT FOR THE PROGRAM
double userMaxError() {
	double errorValue = 0;
	cin.ignore(10000, '\n');
	cin.clear();
	cout << "Please enter the desired stopping error value (as a real number, ie: 0.00000005): ";
	cin >> errorValue;
	if (errorValue > 1 || errorValue < 0 || cin.fail()) {
		cout << "INVALID INPUT. EXITING PROGRAM";
		exit(0);
	}
	return errorValue;
}// END OF userMaxError()

// FUNCTION TO GENERATE MATRIX VALUES USING MANUAL INPUT
void manualInput(double eqArray[10][10], double eqResult[10], int numOfEq) {
	cin.ignore(10000, '\n');
	cin.clear();
	for (int index = 0; index < numOfEq; index++) {
		for (int idx = 0; idx < numOfEq; idx++) {
			cout << "Please enter equation #" << index + 1 << " X" << idx + 1 << "  Value: ";
			cin >> eqArray[index][idx];
			if (cin.fail()) {
				cout << "\nINVALID INPUT. PROGRAM EXITING.";
				exit(0);
			}
		}
		cout << "Please enter equation #" << index + 1 << " Result: ";
		cin >> eqResult[index];
	}
}// END OF manualInput()

// FUNCTION TO GENERATE MATRIX VALUES USING FILE INPUT. RETURN false IF FILE EXISTS, ELSE true
bool fileInput(double eqArray[10][10], double eqResult[10], int numOfEq) {
	string inputLine;
	string fileLocation;
	ifstream inFile;
	cin.ignore(10000, '\n');
	cin.clear();

	while (fileLocation.empty()) {
		cout << "Please enter the file name: ";
		cin >> fileLocation;
	}
	inFile.open(fileLocation.c_str());

	if (inFile.is_open()) {
		for (int index = 0; index < numOfEq; index++) {
			for (int idx = 0; idx < numOfEq; idx++) {
				inFile >> eqArray[index][idx];
			}
			inFile >> eqResult[index];
		}
		inFile.close();
		return false;
	}
	else {
		inFile.close();
		return true;
	}
}// END OF fileInput()


void startingSolution(double solutions[10], int numOfEq) {
	cin.ignore(10000, '\n');
	cin.clear();
	
	for (int index = 0; index < numOfEq; index++) {
		cout << "Please enter the starting solution for X" << index + 1 << ": ";
		cin >> solutions[index];
	}
}

// FUNCTION TO PERFORM JACOBI METHOD AND PRINT SOLUTIONS FOR EACH INTERATION
void jacobiMethod(double eqArray[10][10], double eqResults[10], double solutions[10], double stoppingError, int numOfEq) {
	int maxInterations = 0;
	double error;
	double temp;
	double previousSolution[10] = { 0 };
	bool keepGoing = true;
	typedef std::numeric_limits< double > dblMaxPrecision;

	cout << fixed << setprecision(dblMaxPrecision::max_digits10);
	do {
		temp = 0;
		error = 0;
		for (int index = 0; index < numOfEq; index++) {
			previousSolution[index] = solutions[index];
		}
		
		for (int index = 0; index < numOfEq; index++) {
			if(index == 0)
				cout << "\n| ";
			solutions[index] = eqResults[index] / eqArray[index][index];
			
			for (int idx = 0; idx < numOfEq; idx++) {
				if (idx != index)
					solutions[index] = solutions[index] - (eqArray[index][idx]/eqArray[index][index] * previousSolution[idx]);
			}
			if (index < numOfEq-1)
				cout << solutions[index] << ", ";
			else
				cout << solutions[index];			
		}
		cout << " |";

		if (maxInterations > 0) {
			for (int index = 0; index < numOfEq; index++) {
				error = error + abs(solutions[index]*solutions[index]);
				temp = temp + abs(previousSolution[index]*previousSolution[index]);
			}
			error = abs(sqrt(error) - sqrt(temp)) / abs(sqrt(error));
			if (error < stoppingError || maxInterations > 49)
				keepGoing = false;
		}
		maxInterations++;
		cout << " ==> ERROR: " << error;
	} while (keepGoing);

	if (maxInterations == 51) {
		cout << "\n\nDesired stopping error not reached after 50 interations.";
		cout << "\nFinal Error: " << error;
		cout << "\nFinal Solutions: ";
	}
	else {
		cout << "\n\nNumber of Interations: " << maxInterations-1;
		cout << "\nFinal Error: " << error;
		cout << "\nFinal solution is: ";
	}
	cout << "| ";
	for (int index = 0; index < numOfEq; index++) {
		if (index < numOfEq-1)
			cout << solutions[index] << ", ";
		else
			cout << solutions[index];
	}
	cout << " |";	
}// END OF jacobiMethod()

// FUNCTION TO PERFORM GAUSS-SEIDEL METHOD AND PRINT SOLUTIONS FOR EACH INTERATION
void gaussSeidelMethod(double eqArray[10][10], double eqResults[10], double solutions[10], double stoppingError, int numOfEq) {
	int maxInterations = 0;
	double error;
	double temp;
	double previousSolution[10] = { 0 };
	bool keepGoing = true;
	typedef std::numeric_limits< double > dblMaxPrecision;

	cout << fixed << setprecision(dblMaxPrecision::max_digits10);
	do {
		temp = 0;
		error = 0;
		for (int index = 0; index < numOfEq; index++) {
			previousSolution[index] = solutions[index];
		}

		for (int index = 0; index < numOfEq; index++) {
			if (index == 0)
				cout << "\n| ";
			solutions[index] = eqResults[index] / eqArray[index][index];

			for (int idx = 0; idx < numOfEq; idx++) {
				if (idx != index)
					solutions[index] = solutions[index] - (eqArray[index][idx] / eqArray[index][index] * solutions[idx]);
			}
			if (index < numOfEq-1)
				cout << solutions[index] << ", ";
			else
				cout << solutions[index];
		}
		cout << " |";

		if (maxInterations > 0) {
			for (int index = 0; index < numOfEq; index++) {
				error = error + abs(solutions[index] * solutions[index]);
				temp = temp + abs(previousSolution[index] * previousSolution[index]);
			}
			error = abs(sqrt(error) - sqrt(temp)) / abs(sqrt(error));
			if (error < stoppingError || maxInterations > 49)
				keepGoing = false;
		}
		maxInterations++;
		cout << " ==> ERROR: " << error;
	} while (keepGoing);
	
	if (maxInterations == 51) {
		cout << "\n\nDesired stopping error not reached after 50 interations.";
		cout << "\nFinal Error: " << error;
		cout << "\nFinal Solutions: ";
	}
	else {
		cout << "\n\nNumber of Interations: " << maxInterations-1;
		cout << "\nFinal Error: " << error;
		cout << "\nFinal solution is: ";
	}
	cout << "| ";
	for (int index = 0; index < numOfEq; index++) {
		if (index < numOfEq-1)
			cout << solutions[index] << ", ";
		else
			cout << solutions[index];
	}
	cout << " |";
}// END OF gaussSeidelMethod()




