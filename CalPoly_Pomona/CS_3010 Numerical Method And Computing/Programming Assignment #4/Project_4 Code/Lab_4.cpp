/*
AUTHOR: CHRISTOPHER KOEPKE
CLASS: CS 3010.02
ASSIGNMENT: PROGRAMMING PROJECT #4

This program is designed to take in a text file with an equal number of x and y values (in a row format; ie: x-values in the 
first row and y-values in the second row) which will be used to perform divided difference.

Once all calculations are completed and stored, the program will output all relevent information. The given data points will be in a row
format, same as the text file used, and the divided difference results will be in a column format and in a tabular like form.

Next, the program will output a polynomial of the given data points in a simplifided form, Newton's form, and Lagrange's form.
*/

#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <sstream>

int main() {

	std::string fileName;
	std::vector<float> xValue;
	std::vector<float> yValue;
	float dividedDiffResults[50][50] = { 0 };
	float tempValue = 0;

	// OUTPUT STATEMENT FOR FILE NAME
	std::cout << "Please enter the file name of the data you would like to use: ";
	std::cin >> fileName;
	std::ifstream inFile (fileName);

	// CHECK TO SEE IF FILE EXISTS
	if (!inFile) {
		std::cout << "\nFILE INPUT ERROR. EXITING PROGRAM.\n";
		exit(EXIT_FAILURE);
	}
	
	// GET A LINE OF THE INPUT FILE AND STREAM THIS LINE INTO A VECTOR OF X-VALUES 
	std::string line_1;
	getline(inFile, line_1, '\n');
	std::istringstream iss(line_1);
	while (iss >> tempValue)
	{
		xValue.push_back(tempValue);
	}
	
	// GET THE NEXT LINE OF THE INPUT FILE AND STREAM THAT LINE INTO A VECTOR OF Y-VALUES
	std::string line_2;
	getline(inFile, line_2, '\n');
	std::istringstream iss_2(line_2);
	while (iss_2 >> tempValue)
	{
		yValue.push_back(tempValue);
		
	}

	// CHECK IF THE NUMBER OF DATA POINTS IS EQUAL, IF NOT EXIT
	inFile.close();
	int n = xValue.size();
	int m = yValue.size();
	if (n != m) {
		std::cout << "NUMBER OF DATA POINTS OF X AND Y ARE NOT EQUAL. EXITING PROGRAM.";
		exit(EXIT_FAILURE);
	}

	// PERFORM THE DIVIDED DIFFERENCE OF THE INPUTTED VALUES
	
	for(int index = 0; index < n; index++)
		dividedDiffResults[index][0] = yValue[index];
	for (int index = 1; index < n; index++) {
		for (int idx = index; idx < n; idx++) {
			dividedDiffResults[idx][index] = (dividedDiffResults[idx][index-1]-dividedDiffResults[idx-1][index-1])/(xValue[idx]-xValue[idx-index]);
		}
	}

	// OUTPUT GIVEN DATA POINTS IN A ROW FORMAT
	std::cout << "\nDATA POINTS" << std::endl;
	std::cout << "X: ";
	for (int index = 0; index < n; index++) {
		std::cout << xValue[index] << " ";
	}
	std::cout << "\nY: ";
	for (int index = 0; index < n; index++) {
		std::cout << yValue[index] << " ";
	}

	// OUTPUT THE DIVIDED DIFFERENCE TABLE 
	std::cout << "\n\nDIVIDED DIFFERENCE TABLE" << std::endl;
	int idx = 0;
	do {
		std::cout << std::left << "f[" << std::string(idx, ',') << "]" << std::string(7-idx, ' ');
		idx++;
	} while (idx < n);
	std::cout << std::endl;
	std::cout << std::left << std::setprecision(6) << std::setfill(' ');
	for (int index = 0; index < n; index++) {
		for (int idx = 0; idx < (index+1); idx++) {
			std::cout << std::setw(9) << dividedDiffResults[index][idx] << " ";
		}
		std::cout << std::endl;
	}

	// OUTPUT THE SIMPLIFIED POLYNOMIAL OF THE GIVEN DATA POINTS
	std::cout << "\nSIMPLIFIED FORM: ";
	for (int index = n-1; index > 0; index--) {
		std::cout << "(" << dividedDiffResults[index][index] << ")(x^" << index << ")+";
	}
	std::cout << "(" << yValue[0] << ")";

	// OUTPUT THE NEWTON FORM OF THE POLYNOMIAL OF THE GIVEN DATA POINTS
	std::cout << "\n\nNEWTON FORM:     ";
	int count = 1;
	for (int index = 0; index < n; index++) {
		std::cout << "(" << dividedDiffResults[index][index] << ")";
		for (int idx = 0; idx < index; idx++) {
			std::cout << "(X";
			if (xValue[idx] < 0) {
				std::cout << "+" << xValue[index - count] << ")";
			}
			else
				std::cout << "-" << xValue[index - count] << ")";
			count++;
		}
		if (index < (n - 1))
			std::cout << "+";
		count = 1;
	}
	
	

	// OUTPUT THE LAGRANGE FORM OF THE POLYNOMIAL OF THE GIVEN DATA POINTS
	std::cout << "\n\nLAGRANGE FORM:   ";
	std::cout << "y = ";
	for (int index = 0; index < n; index++) {
		std::cout << "(" << dividedDiffResults[index][index] << ")([";
		for (int idx = 0; idx < n; idx++) {
			if (idx != index) {
				std::cout << "(X";
				if (xValue[idx] < 0)
					std::cout << "+" << xValue[idx] << ")";
				else
					std::cout << "-" << xValue[idx] << ")";
			}
		}
		std::cout << "]/[";
		for (int idx = 0; idx < n; idx++) {			
			if (idx != index) {				
				if (xValue[idx] < 0)
					std::cout << "(" << xValue[index] << "+" << xValue[idx] << ")";
				else
					std::cout << "(" << xValue[index] << "-" << xValue[idx] << ")";
			}
		}
		if (index < (n - 1))
			std::cout << "]) + ";
		else
			std::cout << "])" << std::endl;
	}


	return 0;
}// END OF main()