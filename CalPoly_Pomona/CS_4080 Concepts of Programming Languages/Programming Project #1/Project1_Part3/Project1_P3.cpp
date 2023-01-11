/*
PROGRAMMING PROJECT #1 PART 3

AUTHOR: CHRISTOPHER KOEPKE
CLASS:  CS 4080.03
DATE:   APRIL 2, 2022

DESCRIPTION: This program is desined to perfrom the following matrix operations: addition, subtraction, multiplication.
			This will be accomplished by using pointer to a pointer float matrices (100x100 max size) inside a class, which will be filled by the user manually, randomly, or from a given file.
			The program will first display a brief description of this program and than display a menu on how a matrix may be filled.
			Once both matrices are filled, the user can chose which operation they would like performed.
			Each operation is a seperate function and will display the results of their respective operation.
			After the chosen matrix operation, the program will display the matrix input menu again, return their choice, than go back to the beginning of the do...while loop.
			This loop can be interated a maxiumum of ten times or upon user desired termination or invalid input.
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <ctime>
#include <chrono>

using std::cout;
using std::cin;
using std::endl;
using std::setprecision;
using std::fixed;
using std::right;
using std::setw;
using std::string;
using std::istream;



class Matrix {
private:
	int rows;
	int columns;
	int sum_rows;
	int sum_columns;
	std::chrono::nanoseconds duration;
	std::chrono::nanoseconds start;
	std::chrono::nanoseconds stop;
	//double time;
	static int const MAX_SIZE = 100;
	float **matrix;
	float **matrix_Sum;
public:
	Matrix();
	~Matrix();
	void fillMatrix(int, int, int);
	void fillMatrixFromFile(istream&);
	int getRows();
	int getColumns();
	void printDuration();
	void printMatrix();
	void printMatrix_Sum();
	void operator+(Matrix&);
	void operator-(Matrix&);
	void operator*(Matrix&);   
	void operator=(Matrix&);
	float operator()(int, int);
	

};

// DEFAULT CONSTURUCTOR
Matrix::Matrix() {
	rows = 0;
	columns = 0;
	sum_rows = 0;
	sum_columns = 0;
	//time = 0;
	matrix = new float* [MAX_SIZE];
	matrix_Sum = new float* [MAX_SIZE];
	for (int index = 0; index < MAX_SIZE; index++) {
		matrix[index] = new float[MAX_SIZE];
		matrix_Sum[index] = new float[MAX_SIZE];
	}
}// END OF Matrix()

// DESTRUCTOR
Matrix::~Matrix() {
	for (int r = 0; r < rows; r++) {
		delete[] matrix[r];
		delete[] matrix_Sum[r];
	}
	delete matrix;
	delete matrix_Sum;
}// END OF ~Matrix()

// METHOD TO FILL MATRIX WITH FLOATS BY MANUAL INPUT OR RANDOMLY
void Matrix::fillMatrix(int numOfRows, int numOfColumns, int randomFill) {
	rows = numOfRows;
	columns = numOfColumns;
	if (randomFill == 1) {
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++)
				matrix[r][c] = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 50));
		}
	}
	else {
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				cout << "ROW " << r + 1 << ", COLUMN " << c + 1 << " = ";
				cin >> matrix[r][c];
			}
		}
	}
}// END OF fillMatrix()

// METHOD TO FILL MATRIX USING FILE INPUT
void Matrix::fillMatrixFromFile(istream& inFile) {
	inFile >> rows;
	inFile >> columns;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			inFile >> matrix[r][c];
		}
	}
}//	END OF fillMatrixFromFile()

// METHOD TO RETURN ROWS
int Matrix::getRows() {
	int temp = rows;
	return temp;
}// END OF getRows()

// METHOD OT RETURN COLUMNS
int Matrix::getColumns() {
	int temp = columns;
	return temp;
}// END OF getColumns()

// METHOD TO PRINT THE RUN TIME OF THE LAST ALGORMITHM USED
void Matrix::printDuration() {
	cout << "Time taken = " << duration.count() << " (nanoseconds)" << endl << endl;
}// END OF printDuration()

// METHOD TO PRINT THE INPUT MATRIX
void Matrix::printMatrix() {
	cout << setprecision(4) << fixed << right;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++)
			cout << setw(12) << matrix[r][c] << " ";
		cout << endl;
	}
}// END OF printMatrix()

// METHOD TO PRINT THE SUMMATION MATRIX
void Matrix::printMatrix_Sum() {
	cout << setprecision(4) << fixed << right;
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++)
			cout << setw(12) << matrix_Sum[r][c] << " ";
		cout << endl;
	}
}// END OF printMatrix_Sum()

// METHOD TO OVERLOAD THE + OPERATOR. STORE THE SUM OF THIS OBJECT'S MATRIX AND THE OTHER OBJECT'S MATRIX INTO THE THIS OBJECT'S MATRIX SUM
void Matrix::operator+(Matrix& otherMatrix) {
	auto start = std::chrono::high_resolution_clock::now();
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			matrix_Sum[r][c] = this->matrix[r][c] + otherMatrix(r,c);
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	sum_rows = rows;
	sum_columns = columns;
}// END OF operator+()

// METHOD TO OVERLOAD THE - OPERATOR. STORE THE DIFFERENCE OF THIS OBJECT'S MATRIX AND THE OTHER OBJECT'S MATRIX INTO THE THIS OBJECT'S MATRIX SUM
void Matrix::operator-(Matrix& otherMatrix) {
	auto start = std::chrono::high_resolution_clock::now();
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			matrix_Sum[r][c] = this->matrix[r][c] - otherMatrix(r,c);
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	sum_rows = rows;
	sum_columns = columns;
}// END OF operator-()

// METHOD TO OVERLOAD THE * OPERATOR. STORE THE MULTIPLICATIVE SUM OF THIS OBJECT'S MATRIX AND THE OTHER OBJECT'S MATRIX INTO THE THIS OBJECT'S MATRIX SUM
void Matrix::operator*(Matrix& otherMatrix) {
	int otherColumn = otherMatrix.getColumns();
	float temp = 0.0;
	auto start = std::chrono::high_resolution_clock::now();
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < otherColumn; c++) {
			for (int k = 0; k < columns; k++) {
				temp += matrix[r][k] * otherMatrix(k,c);
			}
			matrix_Sum[r][c] = temp;
			temp = 0.0;
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
	sum_rows = rows;
	sum_columns = otherColumn;
}// END OF operator*()

// METHOD TO OVERLOAD THE () OPERATOR. USED TO RETURN A SPECIFIC ELEMENT OF THE OBJECT'S 2D MATRIX 
float Matrix::operator()(int row_idx, int col_idx) {
	float temp = matrix[row_idx][col_idx];
	return temp;
}// END OF operator()

// START OF main()
int main() {
	int const MAX_LOOP_TEN = 10;
	int loopCounter = 0;
	int menuInputChoice = 0;
	int matrixOperationChoice = 0;
	int noRandomFill = 0;
	int yesRandomFill = 1;
	int rows_A = 0, rows_B = 0;
	int columns_A = 0, columns_B = 0;
	string fileName_A, fileName_B;
	
	// INSTANTIATE OBJECTS WITH THE DEFAULT CONSTRUCTOR
	Matrix matrixObj_A;
	Matrix matrixObj_B;
	Matrix matrixObj_Sum;

	// SEEDING RANDOM NUMBER GENERATOR WITH THE CURRENT TIME
	srand((unsigned int)time(NULL));

	// DISPLAY PROGRAM INFROMATION
	cout << "This program will test the matrix operations of Addition, Subtraction, and Multiplication using float values." << endl;
	cout << "You may enter your two matices manually or with two seperate files." << endl;
	cout << "You can also choose to have the program populate the two matrices with random float values." << endl;
	cout << "Please enter the single number for your menu choice. Use -999 to end the program at any time." << endl;
	cout << "NOTE: MATRIX INPUT CHOICE WILL BE PERFORMED FOR BOTH MATICES. YOU CANNONT ENTER MATRIX_A MANUALLY AND MATRIX_B RANDOMLY AS AN EXAMPLE." << endl << endl;
	

	do {
		// DISPLAY MATRIX INPUT MENU AND STORE THE USER'S CHOICE
		cout << "         MATRIX INPUT MENU" << endl;
		cout << "=====================================" << endl;
		cout << "1) INPUT MATRIX ELEMENTS MANUALLY" << endl;
		cout << "2) INPUT MATRIX ELEMENTS FROM A FILE" << endl;
		cout << "3) INPUT MATRIX ELEMENTS USING RANDOM FLOAT VALUES" << endl;
		cout << "4) USE SAME MATRICES AS BEFORE" << endl;
		cout << "-999) END PROGRAM" << endl;
		cout << "CHOICE: ";
		cin >> menuInputChoice;

		// SWITCH-CASE FOR USER MATRIX INPUT
		switch (menuInputChoice) {
			case 1: {
				// USER INPUTS ELEMENTS MANUALLY
				cout << "\nPlease enter the number of rows for Matrix A: ";
				cin >> rows_A;
				cout << "Please enter the number of columns for Matrix A: ";
				cin >> columns_A;
				cout << "MATRIX A ELEMENTS" << endl;
				matrixObj_A.fillMatrix(rows_A, columns_A, noRandomFill);
				cout << "Please enter the number of rows for Matrix B: ";
				cin >> rows_B;
				cout << "Please enter the number of columns for Matrix B: ";
				cin >> columns_B;
				cout << "MATRIX B ELEMENTS" << endl;
				matrixObj_B.fillMatrix(rows_B, columns_B, noRandomFill);
				break;
			}
			case 2: {
				// USER PASSES FILE TO READ ROW, COLUMN, AND ELEMENTS
				cout << "\nMATRIX_A FILE INPUT" << endl;
				cout << "Please enter the name of the file:  ";
				cin >> fileName_A;
				std::ifstream inFile_A(fileName_A);

				if (inFile_A.is_open()) {
					matrixObj_A.fillMatrixFromFile(inFile_A);
					inFile_A.close();
					rows_A = matrixObj_A.getRows();
					columns_A = matrixObj_A.getColumns();
				}
				else {
					cout << "FILE ERROR. EXITING PROGRAM.";
					exit(0);
				}

				cout << "\nMATRIX_B FILE INPUT" << endl;
				cout << "Please enter the name of the file:  ";
				cin >> fileName_B;
				std::ifstream inFile_B(fileName_B);

				if (inFile_B.is_open()) {
					matrixObj_B.fillMatrixFromFile(inFile_B);
					inFile_B.close();
					rows_B = matrixObj_B.getRows();
					columns_B = matrixObj_B.getColumns();
				}
				else {
					cout << "FILE ERROR. EXITING PROGRAM.";
					exit(0);
				}
				break;
			}
			case 3: {
				// USER WANTS RANDOM ELEMENTS TO BE USED IN MATRIX
				cout << "\nPlease enter the number of rows for Matrix A: ";
				cin >> rows_A;
				cout << "please enter the number of columns for Matrix A: ";
				cin >> columns_A;
				matrixObj_A.fillMatrix(rows_A, columns_A, yesRandomFill);
				cout << "Please enter the number of rows for Matrix B: ";
				cin >> rows_B;
				cout << "Please enter the number of columns for Matrix B: ";
				cin >> columns_B;
				matrixObj_B.fillMatrix(rows_B, columns_B, yesRandomFill);
				break;
			}
			case 4: {
				// USER WANTS TO USE THE SAME MATRICES AS BEFORE. IF FIRST INTERATION, NO OBJECTS WERE CREATED, END PROGRAM BY EXIT FUNCTION
				if (loopCounter == 0) {
					cout << "NO PREVIOUS MATRICES AVAILABLE. EXITING PROGRAM";
					exit(0);
				}
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

		// DISPLAY MATRIX OPERATION MENU AND STORE THE USER'S CHOICE
		cout << "         MATRIX OPERATION MENU" << endl;
		cout << "======================================" << endl;
		cout << "1) ADDITION OF MATRIX_A AND MATRIX_B" << endl;
		cout << "2) SUBTRACTION OF MATRIX_A AND MATRIX_B" << endl;
		cout << "3) MULTIPLICATION OF MATRIX_A AND MATRIX_B" << endl;
		cout << "-999) END PROGRAM" << endl;
		cout << "CHOICE: ";
		cin >> matrixOperationChoice;

		// SWITCH-CASE FOR USER CHOOSEN MATRIX OPERATION
		switch (matrixOperationChoice) {
		case 1: {
			// USER WANTS TO PERFORM MATRIX ADDITION
			if ((rows_A == rows_B) && (columns_A == columns_B)) {
				cout << endl;
				cout << "***  ADDITION OF MATRIX_A AND MATRIX_B    ***" << endl;
				cout << "=============================================" << endl;
				matrixObj_A + matrixObj_B;
				matrixObj_A.printMatrix_Sum();				
				cout << "=============================================" << endl;
				matrixObj_A.printDuration();		
			}
			else {
				cout << "MATRIX ADDITION CANNOT BE PERFORMED. NUMBER OF ROWS AND/OR COLUMNS NOT EQUAL BETWEEN THE MATRICES." << endl << endl;
			}
			break;
		}
		case 2: {
			// USER WANTS TO PERFORM MATRIX SUBTRACTION
			if ((rows_A == rows_B) && (columns_A == columns_B)) {
				cout << endl;
				cout << "***  SUBTRACTION OF MATRIX_A AND MATRIX_B ***" << endl;
				cout << "=============================================" << endl;
				matrixObj_A - matrixObj_B;
				matrixObj_A.printMatrix_Sum();
				cout << "=============================================" << endl;
				matrixObj_A.printDuration();		
			}
			else {
				cout << "MATRIX SUBTRACTION CANNOT BE PERFORMED. NUMBER OF ROWS AND/OR COLUMNS NOT EQUAL BETWEEN THE MATRICES." << endl << endl;
			}
			break;
		}
		case 3: {
			// USER WANTS TO PERFORM MATRIX MULTIPLICATION
			if (columns_A == rows_B) {
				cout << endl;
				cout << "*** MULTIPLICATION OF MATRIX_A AND MATRIX_B ***" << endl;
				cout << "===============================================" << endl;
				matrixObj_A * matrixObj_B;
				matrixObj_A.printMatrix_Sum();
				cout << "=============================================" << endl;
				matrixObj_A.printDuration();
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
		loopCounter++;
	} while (loopCounter < MAX_LOOP_TEN);
	return 0;
}// END OF main()