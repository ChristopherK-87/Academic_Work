#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <fstream>



void bisectionMethod(double, double, char, std::string);
void newtonRaphsonMethod(double, char, std::string);
void secantMethod(double, double, char, std::string);
void falsePositionMethod(double, double, char, std::string);
void modifiedSecantMethod(double, double, char, std::string);

int main() {
	char choice_a = 'a';
	char choice_b = 'b';
	std::string fileName_A = "bisection_A.txt";
	std::string fileName_B = "bisection_B.txt";
	bisectionMethod(0, 1.25, choice_a, fileName_A);
	bisectionMethod(1.25, 2.5, choice_a, fileName_A);
	bisectionMethod(2.5, 4, choice_a, fileName_A);	
	bisectionMethod(120, 130, choice_b, fileName_B);

	fileName_A = "newtonRaphson_A.txt";
	fileName_B = "newtonRaphson_B.txt";
	newtonRaphsonMethod(1, choice_a, fileName_A);
	newtonRaphsonMethod(2, choice_a, fileName_A);
	newtonRaphsonMethod(3, choice_a, fileName_A);	
	newtonRaphsonMethod(120, choice_b, fileName_B);

	fileName_A = "secant_A.txt";
	fileName_B = "secant_B.txt";
	secantMethod(0, 1.25, choice_a, fileName_A);
	secantMethod(1.25, 2.5, choice_a, fileName_A);
	secantMethod(2.5, 4, choice_a, fileName_A);
	secantMethod(120, 130, choice_b, fileName_B);

	fileName_A = "modifiedSecant_A.txt";
	fileName_B = "modifiedSecant_B.txt";
	modifiedSecantMethod(0, 1.25, choice_a, fileName_A);
	modifiedSecantMethod(1.25, 2.5, choice_a, fileName_A);
	modifiedSecantMethod(2.5, 4, choice_a, fileName_A);
	modifiedSecantMethod(120, 130, choice_b, fileName_B);

	fileName_A = "falsePosition_A.txt";
	fileName_B = "falsePosition_B.txt";
	falsePositionMethod(0, 1.25, choice_a, fileName_A);
	falsePositionMethod(1.25, 2.5, choice_a, fileName_A);
	falsePositionMethod(2.5, 4, choice_a, fileName_A);
	falsePositionMethod(120, 130, choice_b, fileName_B);



	return 0;
}// END OF main()

// FUNCTION TO PERFORM BISECTION METHOD OF FINDING ROOTS OF AN EQUATION
void bisectionMethod(double lowerBound, double upperBound, char choice, std::string fileName) {
	double a = lowerBound;
	double b = upperBound;
	double c = 0;
	double Fa = 0;
	double Fb = 0;
	double Fc = 0;
	double relativeError = 0;
	double approximateError = 0;
	int maxInteration = 0;
	double old_c = 0;
	bool keepGoing = true;
	std::ofstream outFile;
	outFile.open(fileName, std::ios::out | std::ios::app);
	if (outFile.fail()) {
		std::cout << "FILE ERROR. PROGRAM EXITING.";
		exit(EXIT_FAILURE);
	}
	outFile << "N " << "An " << "Bn " << "Cn " << "f(An) " << "f(Bn) " << "f(Cn) " << "Approx. Error " << "Relative Error" << std::endl;
	while (keepGoing) {
		old_c = c;
		c = (a + b) / 2;
		if (choice == 'a') {
			Fa = (2 * pow(a, 3)) - (11.7 * pow(a, 2)) + (17.7 * a) - 5;
			Fb = (2 * pow(b, 3)) - (11.7 * pow(b, 2)) + (17.7 * b) - 5;
			Fc = (2 * pow(c, 3)) - (11.7 * pow(c, 2)) + (17.7 * c) - 5;
		}
		else {
			if (choice == 'b') {
				Fa = a + 10 - (a * cosh(50 / a));
				Fb = b + 10 - (b * cosh(50 / b));
				Fc = c + 10 - (c * cosh(50 / c));
			}
			else {
				std::cout << "BAD INPUT. EXIT PROGRAM";
				exit(EXIT_FAILURE);
			}
		}
		approximateError = abs(c - old_c);
		if (maxInteration > 0) {
			relativeError = abs(c - old_c) / abs(c);
			if ((relativeError < 0.01) | (maxInteration == 99)) {
				keepGoing = false;
			}
		}
		outFile << maxInteration << " " << a << " " << b << " " << c << " " << Fa << " " << Fb << " " << Fc << " " << approximateError << " " << relativeError << std::endl;
		
		if (Fc == 0) {
			keepGoing = false;
		}
		else {
			if ((Fa * Fc) < 0)
				b = c;
			else
				a = c;
		}		
		maxInteration++;
	}

}// END OF bisectionMethod()

// FUNCTION TO PERFORM NEWTON-RAPHSON METHOD OF FINDING ROOTS OF AN EQUATION
void newtonRaphsonMethod(double startingPoint, char choice, std::string fileName) {
	double x = startingPoint;
	double x_next = 0;
	double Fx = 0;
	double Fx_prime = 0;
	double relativeError = 0;
	double approximateError = 0;
	int maxInteration = 0;
	bool keepGoing = true;
	std::ofstream outFile;
	outFile.open(fileName, std::ios::out | std::ios::app);
	if (outFile.fail()) {
		std::cout << "FILE ERROR. PROGRAM EXITING.";
		exit(EXIT_FAILURE);
	}
	outFile << "N " << "Xn " << "f(Xn)" << "f'(Xn)" << "Xn+1 " << "Approx. Error " << "Relative Error" << std::endl;
	while (keepGoing) {
		
		if (choice == 'a') {
			Fx = (2 * pow(x, 3)) - (11.7 * pow(x, 2)) + (17.7 * x) - 5;
			Fx_prime = (6 * pow(x, 2)) - (23.4 * x) + 17.7;
		}
		else {
			if (choice == 'b') {
				Fx = x + 10 - (x * cosh(50 / x));
				Fx_prime = ((50 * sinh(50 / x)) / x) - cosh(50 / x) + 1;
			}
			else {
				std::cout << "BAD INPUT. PROGRAM EXITING.";
				exit(EXIT_FAILURE);
			}
		}
		x_next = x - (Fx / Fx_prime);
		approximateError = abs(x_next - x);
		if (maxInteration > 0) {
			relativeError = abs(x_next - x) / abs(x_next);
			if ((relativeError < 0.01) | (maxInteration == 99)) {
				keepGoing = false;
			}
		}
		outFile << maxInteration << " " << x << " " << Fx << " " << Fx_prime << " " << x_next << " " << approximateError << " " << relativeError << std::endl;
		x = x_next;
		maxInteration++;
	}



}// END OF newtonRaphsonMethod()

// FUNCTION TO PERFORM SECANT METHOD OF FINDING ROOTS OF AN EQUATION
void secantMethod(double lowerBound, double upperBound, char choice, std::string fileName) {
	double x_old = lowerBound;
	double x = upperBound;
	double x_next = 0;
	double Fx = 0;
	double Fx_old = 0;
	double relativeError = 0;
	double approximateError = 0;
	int maxInteration = 0;
	bool keepGoing = true;
	std::ofstream outFile;
	outFile.open(fileName, std::ios::out | std::ios::app);
	if (outFile.fail()) {
		std::cout << "FILE ERROR. PROGRAM EXITING.";
		exit(EXIT_FAILURE);
	}
	outFile << "N " << "Xn " << "f(Xn) " << "Approx. Error " << "Relative Error" << std::endl;
	if (choice == 'a') {
		Fx = (2 * pow(x_old, 3)) - (11.7 * pow(x_old, 2)) + (17.7 * x_old) - 5;
	}
	else {
		if (choice == 'b') {
			Fx = x_old + 10 - (x_old * cosh(50 / x_old));
		}
		else {
			std::cout << "BAD INPUT. PROGRAM EXITING.";
			exit(EXIT_FAILURE);
		}
	}
	outFile << maxInteration << " " << x_old << " " << Fx << " N/A N/A" << std::endl;
	Fx_old = Fx;
	maxInteration++;
	if (choice == 'a') {
		Fx = (2 * pow(x, 3)) - (11.7 * pow(x, 2)) + (17.7 * x) - 5;
	}
	if (choice == 'b') {
		Fx = x + 10 - (x * cosh(50 / x));
	}
	approximateError = abs(x - x_old);
	if (maxInteration > 0) {
		relativeError = abs(x - x_old) / abs(x);
		if ((relativeError < 0.01) | (maxInteration == 99)) {
			keepGoing = false;
		}
	}
	outFile << maxInteration << " " << x << " " << Fx << " " << approximateError << " " << relativeError << std::endl;
	maxInteration++;
	x_next = x - (((x - x_old) / (Fx - Fx_old)) * Fx);
	
	
	while (keepGoing) {
		Fx_old = Fx;
		if (choice == 'a') {
			Fx = (2 * pow(x_next, 3)) - (11.7 * pow(x_next, 2)) + (17.7 * x_next) - 5;
		}
		else {
			if (choice == 'b') {
				Fx = x_next + 10 - (x_next * cosh(50 / x_next));
			}
			else {
				std::cout << "BAD INPUT. PROGRAM EXITING.";
				exit(EXIT_FAILURE);
			}
		}
		approximateError = abs(x_next - x);
		if (maxInteration > 0) {
			relativeError = abs(x_next - x) / abs(x_next);
			if ((relativeError < 0.01) | (maxInteration == 99)) {
				keepGoing = false;
			}
		}
		outFile << maxInteration << " " << x_next << " " << Fx << " " << approximateError << " " << relativeError << std::endl;
		x = x_next;
		x_next = x_next - (((x_next - x) / (Fx - Fx_old)) * Fx);
		maxInteration++;
	}

}
// END OF secantMethod()

// FUNCTION TO PERFORM FALSE-POSITION METHOD OF FINDING ROOTS OF AN EQUATION
void falsePositionMethod(double lowerBound, double upperBound, char choice, std::string fileName) {
	double a = lowerBound;
	double b = upperBound;
	double c = 0;
	double Fa = 0;
	double Fb = 0;
	double Fc = 0;
	double relativeError = 0;
	double approximateError = 0;
	int maxInteration = 0;
	double old_c = 0;
	bool keepGoing = true;
	std::ofstream outFile;
	outFile.open(fileName, std::ios::out | std::ios::app);
	if (outFile.fail()) {
		std::cout << "FILE ERROR. PROGRAM EXITING.";
		exit(EXIT_FAILURE);
	}
	outFile << "N " << "An " << "Bn " << "Cn " << "f(An) " << "f(Bn) " << "f(Cn) " << "Approx. Error " << "Relative Error" << std::endl;
	while (keepGoing) {
		old_c = c;
		if (choice == 'a') {
			Fa = (2 * pow(a, 3)) - (11.7 * pow(a, 2)) + (17.7 * a) - 5;
			Fb = (2 * pow(b, 3)) - (11.7 * pow(b, 2)) + (17.7 * b) - 5;
			c = ((b * Fa) - (a * Fb)) / (Fa - Fb);
			Fc = (2 * pow(c, 3)) - (11.7 * pow(c, 2)) + (17.7 * c) - 5;
		}
		else {
			if (choice == 'b') {
				Fa = a + 10 - (a * cosh(50 / a));
				Fb = b + 10 - (b * cosh(50 / b));
				c = ((b * Fa) - (a * Fb)) / (Fa - Fb);
				Fc = c + 10 - (c * cosh(50 / c));
			}
			else {
				std::cout << "BAD INPUT. EXIT PROGRAM";
				exit(EXIT_FAILURE);
			}
		}
		approximateError = abs(c - old_c);
		if (maxInteration > 0) {
			relativeError = abs(c - old_c) / abs(c);
			if ((relativeError < 0.01) | (maxInteration == 99)) {
				keepGoing = false;
			}
		}
		outFile << maxInteration << " " << a << " " << b << " " << c << " " << Fa << " " << Fb << " " << Fc << " " << approximateError << " " << relativeError << std::endl;

		if (Fc == 0) {
			keepGoing = false;
		}
		else {
			if (((Fa > 0) & (Fc > 0)) | ((Fa < 0) & (Fc < 0))) {
				a = c;
			}
			else
				b = c;
		}
		maxInteration++;
	}
}// END OF falsePositionMethod()

// FUNCTION TO PERFORM MODIFIED SECANT METHOD OF FINDING ROOTS OF AN EQUATION
void modifiedSecantMethod(double lowerBound, double upperBound, char choice, std::string fileName) {
	double x_old = lowerBound;
	double x = upperBound;
	double x_next = 0;
	double Fx = 0;
	double Fx_old = 0;
	double relativeError = 0;
	double approximateError = 0;
	int maxInteration = 0;
	double d = 0.001;
	bool keepGoing = true;
	std::ofstream outFile;
	outFile.open(fileName, std::ios::out | std::ios::app);
	if (outFile.fail()) {
		std::cout << "FILE ERROR. PROGRAM EXITING.";
		exit(EXIT_FAILURE);
	}
	outFile << "N " << "Xn " << "f(Xn) " << "Approx. Error " << "Relative Error" << std::endl;
	if (choice == 'a') {
		Fx = (2 * pow(x_old, 3)) - (11.7 * pow(x_old, 2)) + (17.7 * x_old) - 5;
	}
	else {
		if (choice == 'b') {
			Fx = x_old + 10 - (x_old * cosh(50 / x_old));
		}
		else {
			std::cout << "BAD INPUT. PROGRAM EXITING.";
			exit(EXIT_FAILURE);
		}
	}
	outFile << maxInteration << " " << x_old << " " << Fx << " N/A N/A" << std::endl;
	Fx_old = Fx;
	maxInteration++;
	if (choice == 'a') {
		Fx = (2 * pow(x, 3)) - (11.7 * pow(x, 2)) + (17.7 * x) - 5;
		x_next = x - (((d * x) * Fx) / ((2 * pow((x * d), 3)) - (11.7 * pow((x * d), 2)) + (17.7 * (x * d) - 5) - Fx));
	}
	if (choice == 'b') {
		Fx = x + 10 - (x * cosh(50 / x));
		x_next = x - ((d * x) * Fx) / ((d*x) + 10 - ((d*x) * cosh(50 / (d*x))) - Fx);
	}
	approximateError = abs(x - x_old);
	if (maxInteration > 0) {
		relativeError = abs(x - x_old) / abs(x);
		if ((relativeError < 0.01) | (maxInteration == 99)) {
			keepGoing = false;
		}
	}
	outFile << maxInteration << " " << x << " " << Fx << " " << approximateError << " " << relativeError << std::endl;
	maxInteration++;
	


	while (keepGoing) {
		x = x_next;
		Fx_old = Fx;
		if (choice == 'a') {
			Fx = (2 * pow(x, 3)) - (11.7 * pow(x, 2)) + (17.7 * x) - 5;
			x_next = x - (((d * x) * Fx) / ((2 * pow((x * d), 3)) - (11.7 * pow((x * d), 2)) + (17.7 * (x * d) - 5) - Fx));
		}
		if (choice == 'b') {
			Fx = x + 10 - (x * cosh(50 / x));
			x_next = x - ((d * x) * Fx) / ((d * x) + 10 - ((d * x) * cosh(50 / (d * x))) - Fx);
		}
		approximateError = abs(x_next - x);
		if (maxInteration > 0) {
			relativeError = abs(x_next - x) / abs(x_next);
			if ((relativeError < 0.01) | (maxInteration == 99)) {
				keepGoing = false;
			}
		}
		outFile << maxInteration << " " << x << " " << Fx << " " << approximateError << " " << relativeError << std::endl;
		maxInteration++;
	}

}// END OF modifiedSecantMethod()