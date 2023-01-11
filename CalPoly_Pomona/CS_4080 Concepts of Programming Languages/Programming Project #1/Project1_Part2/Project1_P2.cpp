/*
PROGRAMMING PROJECT #1 PART 2

AUTHOR: CHRISTOPHER KOEPKE
CLASS:  CS 4080.03
DATE:   APRIL 2, 2022

DESCRIPTION: This program is desined to perfrom the following matrix operations: addition, subtraction, multiplication.
			This will be accomplished by using pointer to a pointer float matrices (100x100 max size) which will be filled by the user manually, randomly, or from a given file.
			The program will first display a brief description of this program and than display a menu on how a matrix may be filled.
			Once both matrices are filled, the user can chose which operation they would like performed.
			Each operation is a seperate function and will display the results of their respective operation.
			After the chosen matrix operation, the program will display the matrix input menu again, return their choice, than go back to the beginning of the do...while loop.
			This loop can be interated a maxiumum of ten times or upon user desired termination or invalid input.
*/

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <ctime>
#include <chrono>
using namespace std::chrono;
using std::cout;
using std::endl;
using std::fixed;
using std::setprecision;
using std::setw;
using std::right;
using std::cin;
using std::string;
int const MAX_SIZE = 100;

int  showInputMenu();
int  matrixOperationMenu();
void setMatrixManualOrRandom(float**, int, int, int);
int  setMatrixFromFile(std::istream&, float**, int, int);
float **matrixAddition(float**, float**, int, int, int, int);
float **matrixSubtraction(float**, float**, int, int, int, int);
float **matrixMultiplication(float**, float**, int, int, int, int);


int main() {

	// LOCAL VARIABLE DECLARATIONS AND INITIALIZATIONS
	int const MAX_LOOP_TEN = 10;
	float **matrix_A = new float* [MAX_SIZE];
	float **matrix_B = new float* [MAX_SIZE];
	int row_A = 0, row_B = 0;
	int column_A = 0, column_B = 0;
	int menuInputChoice = 0;
	int matrixOperationChoice = 0;
	int randomElementsTrue = 0;
	string fileLocation_A;
	string fileLocation_B;
	int loopCounter = 0;
	float** ptrPtr;
	// SEEDING RANDOM NUMBER GENERATOR WITH THE CURRENT TIME
	srand((unsigned int)time(NULL));

	// ALLOCATING MEMORY FOR POINTER TO A POINTER ARRAY
	for (int index = 0; index < MAX_SIZE; index++) {
		matrix_A[index] = new float[MAX_SIZE];
		matrix_B[index] = new float[MAX_SIZE];
	}

	// DISPLAY PROGRAM INFROMATION AND SHOW MATRIX INPUT MENU AND RETURN USER CHOICE
	cout << "This program will test the matrix operations of Addition, Subtraction, and Multiplication using float values." << endl;
	cout << "You may enter your two matices manually or with two seperate files." << endl;
	cout << "You can also choose to have the program populate the two matrices with random float values." << endl;
	cout << "Please enter the single number for your menu choice. Use -999 to end the program at any time." << endl;
	cout << "NOTE: MATRIX INPUT CHOICE WILL BE PERFORMED FOR BOTH MATICES. YOU CANNONT ENTER MATRIX_A MANUALLY AND MATRIX_B RANDOMLY AS AN EXAMPLE." << endl << endl;
	menuInputChoice = showInputMenu();

	// START OF PROGRAM OPERATION LOOP FOR MATRIX INPUT AND MATRIX OPERATIONS
	do {
		// SWITCH-CASE FOR USER MATRIX INPUT
		switch (menuInputChoice) {
		case 1: {
			// USER INPUTS ELEMENTS MANUALLY
			cout << "\nPlease enter the number of rows for Matrix A: ";
			cin >> row_A;
			cout << "Please enter the number of columns for Matrix A: ";
			cin >> column_A;
			cout << "MATRIX A ELEMENTS" << endl;
			setMatrixManualOrRandom(matrix_A, randomElementsTrue, row_A, column_A);
			cout << "Please enter the number of rows for Matrix B: ";
			cin >> row_B;
			cout << "Please enter the number of columns for Matrix B: ";
			cin >> column_B;
			cout << "MATRIX B ELEMENTS" << endl;
			setMatrixManualOrRandom(matrix_B, randomElementsTrue, row_B, column_B);
			break;
		}
		case 2: {
			// USER PASSES FILE TO READ ROW, COLUMN, AND ELEMENTS
			cout << "\nMATRIX_A FILE INPUT" << endl;
			cout << "Please enter the name of the file:  ";
			cin >> fileLocation_A;
			std::ifstream inFile_A(fileLocation_A);

			if (inFile_A.is_open()) {
				inFile_A >> row_A;
				inFile_A >> column_A;
				setMatrixFromFile(inFile_A, matrix_A, row_A, column_A);
				inFile_A.close();
			}
			else {
				cout << "FILE ERROR. EXITING PROGRAM.";
				exit(0);
			}

			cout << "\nMATRIX_B FILE INPUT" << endl;
			cout << "Please enter the name of the file:  ";
			cin >> fileLocation_B;
			std::ifstream inFile_B(fileLocation_B);

			if (inFile_B.is_open()) {
				inFile_B >> row_B;
				inFile_B >> column_B;
				setMatrixFromFile(inFile_B, matrix_B, row_B, column_B);
				inFile_B.close();
			}
			else {
				cout << "FILE ERROR. EXITING PROGRAM.";
				exit(0);
			}
			break;
		}
		case 3: {
			// USER WANTS RANDOM ELEMENTS TO BE USED IN MATRIX
			randomElementsTrue = 1;
			cout << "\nPlease enter the number of rows for Matrix A: ";
			cin >> row_A;
			cout << "please enter the number of columns for Matrix A: ";
			cin >> column_A;
			setMatrixManualOrRandom(matrix_A, randomElementsTrue, row_A, column_A);
			cout << "Please enter the number of rows for Matrix B: ";
			cin >> row_B;
			cout << "Please enter the number of columns for Matrix B: ";
			cin >> column_B;
			setMatrixManualOrRandom(matrix_B, randomElementsTrue, row_B, column_B);
			break;
		}
		case 4: {
			// USER WANTS TO USE THE SAME MATRICES AS BEFORE
			break;
		}
		case -999: {
			// USER WANTS TO EXIT PROGRAM
			cout << "EXIT";
			exit(0);
		}
		default: {
			// INVALID USER INPUT
			cout << "INVALID MATRIX INPUT CHOICE. EXITING PROGRAM.";
			exit(0);
		}
		}// END OF SWITCH-CASE FOR MATRIX INPUT

		cout << endl;
		cin.clear();
		cin.ignore(10000, '\n');

		// DISPLAY MATRIX OPERATIONS MENU AND RETURN USER CHOICE
		matrixOperationChoice = matrixOperationMenu();
		cout << endl;

		// SWITCH-CASE FOR USER CHOOSEN MATRIX OPERATION
		switch (matrixOperationChoice) {
		case 1: {
			// USER WANTS TO PERFORM MATRIX ADDITION
			if ((row_A == row_B) && (column_A == column_B)) {
				cout << endl;
				cout << "***  ADDITION OF MATRIX_A AND MATRIX_B    ***" << endl;
				cout << "=============================================" << endl;
				cout << setprecision(4) << fixed << right;
				auto start = high_resolution_clock::now();
				ptrPtr = matrixAddition(matrix_A, matrix_B, row_A, column_A, row_B, column_B);
				auto stop = high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<nanoseconds>(stop - start);

				for (int r = 0; r < row_A; r++) {
					for (int c = 0; c < column_A; c++)
						cout << setw(10) << ptrPtr[r][c] << " ";
					cout << endl;
				}
				cout << "=============================================" << endl;
				cout << "    TIME TAKEN = " << duration.count() << " (nanoseconds)" << endl << endl << endl;
			}
			else {
				cout << "MATRIX ADDITION CANNOT BE PERFORMED. NUMBER OF ROWS AND/OR COLUMNS NOT EQUAL BETWEEN THE MATRICES." << endl << endl;
			}
			break;
		}
		case 2: {
			// USER WANTS TO PERFORM MATRIX SUBTRACTION
			if ((row_A == row_B) && (column_A == column_B)) {
				cout << endl;
				cout << "***  SUBTRACTION OF MATRIX_A AND MATRIX_B ***" << endl;
				cout << "=============================================" << endl;
				cout << setprecision(4) << fixed << right;
				
				auto start = high_resolution_clock::now();
				ptrPtr = matrixSubtraction(matrix_A, matrix_B, row_A, column_A, row_B, column_B);
				auto stop = high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<nanoseconds>(stop - start);

				for (int r = 0; r < row_A; r++) {
					for (int c = 0; c < column_A; c++)
						cout << setw(10) << ptrPtr[r][c] << " ";
					cout << endl;
				}
				cout << "=============================================" << endl;
				cout << "    TIME TAKEN = " << duration.count() << " (nanoseconds)" << endl << endl << endl;
			}
			else {
				cout << "MATRIX SUBTRACTION CANNOT BE PERFORMED. NUMBER OF ROWS AND/OR COLUMNS NOT EQUAL BETWEEN THE MATRICES." << endl << endl;
			}
			break;
		}
		case 3: {
			// USER WANTS TO PERFORM MATRIX MULTIPLICATION
			if (column_A == row_B) {
				cout << endl;
				cout << "*** MULTIPLICATION OF MATRIX_A AND MATRIX_B ***" << endl;
				cout << "===============================================" << endl;
				cout << setprecision(4) << fixed << right;
				
				auto start = high_resolution_clock::now();
				ptrPtr = matrixMultiplication(matrix_A, matrix_B, row_A, column_A, row_B, column_B);
				auto stop = high_resolution_clock::now();
				auto duration = std::chrono::duration_cast<nanoseconds>(stop - start);
				
				for (int r = 0; r < row_A; r++) {
					for (int c = 0; c < column_A; c++)
						cout << setw(10) << ptrPtr[r][c] << " ";
					cout << endl;
				}
				cout << "=============================================" << endl;
				cout << "    TIME TAKEN = " << duration.count() << " (nanoseconds)" << endl << endl << endl;
			}
			else {
				cout << "MATRIX MULTIPLICATION CANNOT BE PERFORMED. NUMBER OF COLUMNS OF MATRIX_A NOT EQUAL TO NUMBER OF ROWS IN MATRIX_B." << endl << endl;
			}
			break;
		}
		case -999: {
			// USER WANTS TO EXIT THE PROGRAM
			cout << "EXIT";
			exit(0);
		}
		default: {
			// INVALID USER INPUT
			cout << "INVALID MATRIX OPERATION CHOICE. EXITING PROGRAM.";
			exit(0);
		}
		}// END OF SWITCH-CASE MATRIX OPERATIONS

		cin.clear();
		cin.ignore(10000, '\n');

		// DISPLAY MATRIX INPUT MENU AND RETURN THEIR CHOICE
		menuInputChoice = showInputMenu();
		loopCounter++;

		// END LOOP IF LOOP COUNTER > 9; MAX LOOPS POSSIBLE IS 10
		// PROGRAM CAN EXIT AT EACH MENU (USER DESIRED TERMINATION) OR ON INVALID INPUT USING exit() FUNCTION
	} while (loopCounter < MAX_LOOP_TEN);

	return 0;
}// END OF MAIN


// DISPLAY MATRIX INPUT MENU AND RETURN CHOICE
int showInputMenu() {
	int choice = 0;

	cout << "         MATRIX INPUT MENU" << endl;
	cout << "=====================================" << endl;
	cout << "1) INPUT MATRIX ELEMENTS MANUALLY" << endl;
	cout << "2) INPUT MATRIX ELEMENTS FROM A FILE" << endl;
	cout << "3) INPUT MATRIX ELEMENTS USING RANDOM FLOAT VALUES" << endl;
	cout << "4) USE SAME MATRICES AS BEFORE (If no previous matices were used, all elements will be zero)." << endl;
	cout << "-999) END PROGRAM" << endl;
	cout << "CHOICE: ";
	cin >> choice;

	if (cin.fail()) {
		cout << "INVALID INPUT CHOICE. EXITING PROGRAM.";
		exit(0);
	}
	return choice;
}// END OF showInputMenu()


// DISPLAY MATRIX OPERATION MENU
int matrixOperationMenu() {
	int choice = 0;
	cout << "         MATRIX OPERATION MENU" << endl;
	cout << "======================================" << endl;
	cout << "1) ADDITION OF MATRIX_A AND MATRIX_B" << endl;
	cout << "2) SUBTRACTION OF MATRIX_A AND MATRIX_B" << endl;
	cout << "3) MULTIPLICATION OF MATRIX_A AND MATRIX_B" << endl;
	cout << "-999) END PROGRAM" << endl;
	cout << "CHOICE: ";
	cin >> choice;

	if (cin.fail()) {
		cout << "INVALID OPERATION CHOICE. EXITING PROGRAM.";
		exit(0);
	}
	return choice;
}// END OF matrixOperationMenu()


// FUNCTION TO MANUALLY SET MATRIX ELEMENTS OR USE RANDOM FLOAT VALUES 
void setMatrixManualOrRandom(float **matrix, int random, int row, int column) {
	// RANDOM FLOAT ELEMENTS INSERTED INTO A MATRIX
	if (random == 1) {
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < column; c++)
				matrix[r][c] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50));
		}
	}
	// USER INPUT OF MATRIX ELEMENTS
	else {
		for (int r = 0; r < row; r++) {
			for (int c = 0; c < column; c++) {
				cout << "ROW " << r + 1 << ", COLUMN " << c + 1 << " = ";
				cin >> matrix[r][c];
				cout << endl;
			}
		}
	}

}// END OF setMatrixManualOrRandom()


// FUNCTION TO SET MATRIX ELEMENTS FROM A FILE
int setMatrixFromFile(std::istream& inFile, float **matrix, int row, int column) {
	// FILE INPUT FOR MATRIX ELEMNTS
	for (int r = 0; r < row; r++) {
		for (int c = 0; c < column; c++) {
			inFile >> matrix[r][c];
		}
	}

	return 0;
}// END OF setMatrixFromFile()


// FUNCTION TO ADD MATRIX_A TO MATRIX_B AND RETURN THE RESULTING MATRIX
float **matrixAddition(float **matrix_A, float **matrix_B, int row_A, int column_A, int row_B, int column_B) {

	float** matrix_Sum = new float* [MAX_SIZE];
	for (int index = 0; index < MAX_SIZE; index++) {
		matrix_Sum[index] = new float[MAX_SIZE];
	}

	for (int r = 0; r < row_A; r++) {
		for (int c = 0; c < column_A; c++) {
			matrix_Sum[r][c] = matrix_A[r][c] + matrix_B[r][c];
		}
	}

	return matrix_Sum;
}// END OF matrixAddition()


// FUNCTION TO SUBTRACT MATRIX_A TO MATRIX_B AND RETURN THE RESULTING MATRIX
float **matrixSubtraction(float **matrix_A, float **matrix_B, int row_A, int column_A, int row_B, int column_B) {
	
	float** matrix_Sum = new float* [MAX_SIZE];
	for (int index = 0; index < MAX_SIZE; index++) {
		matrix_Sum[index] = new float[MAX_SIZE];
	} 

	for (int r = 0; r < row_A; r++) {
		for (int c = 0; c < column_A; c++) {
			matrix_Sum[r][c] = (matrix_A[r][c] - matrix_B[r][c]);
		}
	}

	return matrix_Sum;
}// END OF matrixSubtraction()


// FUNCTION TO MULTIPLY MATRIX_A TO MATRIX_B AND RETURN THE RESULTING MATRIX
float **matrixMultiplication(float **matrix_A, float **matrix_B, int row_A, int column_A, int row_B, int column_B) {
	
	float** matrix_Sum = new float* [MAX_SIZE];
	for (int index = 0; index < MAX_SIZE; index++) {
		matrix_Sum[index] = new float[MAX_SIZE];
	}

	float temp = 0.0;
	for (int r = 0; r < row_A; r++) {
		for (int c = 0; c < column_B; c++) {
			for (int k = 0; k < column_A; k++) {
				temp += matrix_A[r][k] * matrix_B[k][c];
			}
			matrix_Sum[r][c] = temp;
			temp = 0.0;
		}			
	}

	return matrix_Sum;
}// END OF matrixMultiplication()