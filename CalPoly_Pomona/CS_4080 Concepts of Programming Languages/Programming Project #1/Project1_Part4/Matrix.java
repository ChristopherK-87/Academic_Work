/*
PROGRAMMING PROJECT #1 PART 4

AUTHOR: CHRISTOPHER KOEPKE
CLASS:  CS 4080.03
DATE:   APRIL 2, 2022

DESCRIPTION: This program is desined to perfrom the following matrix operations: addition, subtraction, multiplication.
			This will be accomplished by using a matrix class where 2D arrays will be used (100x100 max size), which will be filled by the user manually, randomly, or from a given file.
			The program will first display a brief description of this program and than display a menu on how a matrix may be filled.
			Once both matrices are filled, the user can chose which operation they would like performed.
			Each operation is a seperate function and will display the results of their respective operation.
			After the chosen matrix operation, the program will display the matrix input menu again, return their choice, than go back to the beginning of the do...while loop.
			This loop can be interated a maxiumum of ten times or upon user desired termination or invalid input.
*/

import java.io.File;
import java.util.Random;
import java.util.Scanner;

public class Matrix{
    private int rows;
	private int columns;
	private int sum_rows;
	private int sum_columns;
    private long startTime;
    private long endTime;
    private long runTime;
    private final int MAX_SIZE = 100;
    private float[][] matrix;
    private float[][] matrix_Sum;

    // DEFAULT CONSTRUCTO
    public Matrix(){
        rows = 0;
        columns = 0;
        sum_rows = 0;
        sum_columns = 0;
        startTime = 0;
        endTime = 0;
        runTime = 0;
        matrix = new float[MAX_SIZE][MAX_SIZE];
        matrix_Sum = new float[MAX_SIZE][MAX_SIZE];
        for(int r = 0; r < MAX_SIZE; r++){
            for(int c = 0; c < MAX_SIZE; c++){
                matrix[r][c] = 0;
                matrix_Sum[r][c] = 0;
            }
        }
    }// END OF Matrix()

    // METHOD TO INSERT 2D ARRAY FLOAT ELEMENTS MANUALLY BY THE USER OR RANDOMLY
    public void fillMatrix(int numOfRows, int numOfColumns, int randomFill, Scanner input){
        rows = numOfRows;
        columns = numOfColumns;
        Random random = new Random();
        float min = 0.1f;
        float max = 50f;
        float randomFloat;
        if (randomFill == 1) {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++){
                    randomFloat = min + random.nextFloat() * (max - min);
                    this.matrix[r][c] = randomFloat;
                }
            }
        }
        else {
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    System.out.print("Row " + r + " Column " + c + " = ");
                    matrix[r][c] = input.nextFloat();
                }
            }
            
        }
    }// END OF fillMatrix()

    // METHOD TO INSERT FLOAT ELEMENTS INTO A 2D ARRAY FROM FILE
	void fillMatrixFromFile(String fileName){
        try { 
            
            Scanner inputFileElement = new Scanner(new File(fileName));
            rows = inputFileElement.nextInt();
            columns = inputFileElement.nextInt();
            for (int r = 0; r < rows; r++) {
                for (int c = 0; c < columns; c++) {
                    matrix[r][c] = inputFileElement.nextFloat();
                }
            }           
            inputFileElement.close();

        }
        catch (Exception ex) {
            System.out.println("FILE NOT FOUND. EXITING PROGRAM.");
            System.exit(1);         
        }
    }// END OF fillMatrixFromFile()

    // METHOD TO RETURN ROWS
	int getRows(){
        return rows;
    }// END OF getRows()

    // METHOD TO RETURN COLUMNS
	int getColumns(){
        return columns;
    }// END OF getColumns()

    // METHOD TO PRINT THE RUN TIME OF THE LAST ALGORITHM USED
	void printDuration(){
        System.out.println("Time Taken = " + runTime + " (nanoseconds)");
    }// END OF printDuration()

    // METHOD TO DISPLAY THE INPUT MATRIX
	void printMatrix(){
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                System.out.printf("%12.4f ", matrix[r][c]);
            }
            System.out.println();
        }
    }// END OF printMatrix()

    // METHOD TO DISPLAY THE SUMMATION MATRIX
	void printMatrix_Sum(){
        for (int r = 0; r < sum_rows; r++) {
            for (int c = 0; c < sum_columns; c++) {
                System.out.printf("%12.4f ", matrix_Sum[r][c]);;
            }
            System.out.println();
        }
    }// END OF printMatric_Sum()

    // METHOD THAT ADDS TWO MATRICES AND STORES THE RESULTS IN THE SUMMATION MATRIX
	void addMatrices(Matrix otherMatrix){
        startTime = System.nanoTime();
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                matrix_Sum[r][c] = matrix[r][c] + otherMatrix.matrix[r][c];
            }            
        }
        sum_rows = rows;
        sum_columns = columns;
        endTime = System.nanoTime();
        runTime = endTime-startTime;
    }// END OF addMatrices()

    // METHOD THAT CALCULATES THE DIFFERENCE BETWEEN TWO MATRICES AND STORES THE RESULTS IN THE SUMMATION MATRIX
	void subtractMatrices(Matrix otherMatrix){
        startTime = System.nanoTime();
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < columns; c++) {
                matrix_Sum[r][c] = matrix[r][c] - otherMatrix.matrix[r][c];
            }            
        }
        sum_rows = rows;
        sum_columns = columns;
        endTime = System.nanoTime();
        runTime = endTime-startTime;
    }// END OF subtractMatrices()

    // METHOD THAT CALCULATES THE MULTIPLICATIVE SUMMATION OF TWO MATRICES AND STORES THE RESULTS IN THE SUMMATION MATRIX
	void multiplyMatrices(Matrix otherMatrix){
        int otherColumn = otherMatrix.columns;
        float temp = 0;
        startTime = System.nanoTime();
        for (int r = 0; r < rows; r++) {
            for (int c = 0; c < otherColumn; c++) {
                for (int k = 0; k < columns; k++) {
                    temp += matrix[r][k] * otherMatrix.matrix[k][c];
                }
                matrix_Sum[r][c] = temp;
                temp = 0;
            }
        }
        sum_rows = rows;
        sum_columns = otherColumn;
        endTime = System.nanoTime();
        runTime = endTime-startTime;
    }// END OF multiplyMatrices()   
	

    public static void main(String[] args) throws Exception{
        int loopCounter = 0;
        final int MAX_LOOP_TEN = 10;
        int menuInputChoice = 0;
        int matrixOperationChoice = 0;
        int rows_A = 0, rows_B = 0;
        int columns_A = 0, columns_B = 0;
        int noRandomFill = 0, yesRandomFill = 1;
        String fileName_A, fileName_B;
        Matrix matrixObj_A = new Matrix();
        Matrix matrixObj_B = new Matrix();

        // DISPLAY PROGRAM INFORMATION
        System.out.println("This program will test the matrix operations of Addition, Subtraction, and Multiplication using float values.");
        System.out.println("You may enter your two matices manually or with two seperate files.");
        System.out.println("You can also choose to have the program populate the two matrices with random float values.");
        System.out.println("Please enter the single number for your menu choice. Use -999 to end the program at any time.");
        System.out.println("NOTE: MATRIX INPUT CHOICE WILL BE PERFORMED FOR BOTH MATICES. YOU CANNONT ENTER MATRIX_A MANUALLY AND MATRIX_B RANDOMLY AS AN EXAMPLE.");
        System.out.println();
        Scanner input = new Scanner(System.in);
        
        do {	
            // DISPLAY MATRIX INPUT MENU AND STORES THE USER'S CHOICE	
            System.out.println("         MATRIX INPUT MENU");
            System.out.println("=====================================");
            System.out.println("1) INPUT MATRIX ELEMENTS MANUALLY");
            System.out.println("2) INPUT MATRIX ELEMENTS FROM A FILE");
            System.out.println("3) INPUT MATRIX ELEMENTS USING RANDOM FLOAT VALUES");
            System.out.println("4) USE SAME MATRICES AS BEFORE");
            System.out.println("-999) END PROGRAM");
            System.out.print("CHOICE: ");            
            menuInputChoice = input.nextInt();
    
            // SWITCH-CASE FOR USER MATRIX INPUT
            switch (menuInputChoice) {
                case 1: {
                    // USER INPUTS ELEMENTS MANUALLY
                    input.nextLine();
                    System.out.print("\nPlease enter the number of rows for Matrix A: ");
                    rows_A = input.nextInt();
                    System.out.print("Please enter the number of columns for Matrix A: ");
                    columns_A = input.nextInt();
                    System.out.println("MATRIX A ELEMENTS");
                    input.nextLine();
                    matrixObj_A.fillMatrix(rows_A, columns_A, noRandomFill, input);
                    System.out.print("Please enter the number of rows for Matrix B: ");
                    rows_B = input.nextInt();
                    System.out.print("Please enter the number of columns for Matrix B: ");
                    columns_B = input.nextInt();
                    System.out.println("MATRIX B ELEMENTS");
                    input.nextLine();
                    matrixObj_B.fillMatrix(rows_B, columns_B, noRandomFill, input);                    
                    break;
                }
                case 2: {
                    // USER PASSES FILE TO READ ROW, COLUMN, AND ELEMENTS
                    input.nextLine();
                    System.out.println("\nMATRIX_A FILE INPUT");
                    System.out.print("Please enter the name of the file:  ");
                    fileName_A = input.nextLine();    
                    matrixObj_A.fillMatrixFromFile(fileName_A);
                    rows_A = matrixObj_A.getRows();
                    columns_A = matrixObj_A.getColumns();
                    System.out.println("\nMATRIX_B FILE INPUT");
                    System.out.print("Please enter the name of the file:  ");
                    fileName_B = input.nextLine();
                    matrixObj_B.fillMatrixFromFile(fileName_B);
                    rows_B = matrixObj_B.getRows();
                    columns_B = matrixObj_B.getColumns();
                    break;
                }
                case 3: {
                    // USER WANTS RANDOM ELEMENTS TO BE USED IN MATRIX
                    input.nextLine();
                    System.out.print("\nPlease enter the number of rows for Matrix A: ");
                    rows_A = input.nextInt();
                    System.out.print("please enter the number of columns for Matrix A: ");
                    columns_A = input.nextInt();
                    matrixObj_A.fillMatrix(rows_A, columns_A, yesRandomFill, input);
                    input.nextLine();
                    System.out.print("Please enter the number of rows for Matrix B: ");
                    rows_B = input.nextInt();
                    System.out.print("Please enter the number of columns for Matrix B: ");
                    columns_B = input.nextInt();
                    matrixObj_B.fillMatrix(rows_B, columns_B, yesRandomFill, input);
                    break;
                }
                case 4: {
                    // USER WANTS TO USE THE SAME MATRICES AS BEFORE. IF FIRST INTERATION, NO OBJECTS WERE CREATED, END PROGRAM BY EXIT FUNCTION
                    if (loopCounter == 0) {
                        System.out.print("NO PREVIOUS MATRICES AVAILABLE. EXITING PROGRAM");
                        input.close();
                        System.exit(1);
                    }
                    break;
                }
                case -999: {
                    // USER WANTS TO EXIT PROGRAM
                    System.out.print("EXIT");
                    input.close();
                    System.exit(0);
                }
                default: {
                    // INVALID USER INPUT
                    System.out.print("INVALID MATRIX INPUT CHOICE. EXITING PROGRAM.");
                    input.close();
                    System.exit(1);
                }
            }// END OF SWITCH-CASE FOR MATRIX INPUT            

            // DISPLAY MATRIX OPERATION MENU AND STORE THE USER'S CHOICE
            System.out.println();    
            System.out.println("         MATRIX OPERATION MENU");
            System.out.println("======================================");
            System.out.println("1) ADDITION OF MATRIX_A AND MATRIX_B");
            System.out.println("2) SUBTRACTION OF MATRIX_A AND MATRIX_B");
            System.out.println("3) MULTIPLICATION OF MATRIX_A AND MATRIX_B");
            System.out.println("-999) END PROGRAM");
            System.out.print("CHOICE: ");
            matrixOperationChoice = input.nextInt();
    
            // SWITCH-CASE FOR USER CHOOSEN MATRIX OPERATION
            switch (matrixOperationChoice) {
            case 1: {
                // USER WANTS TO PERFORM MATRIX ADDITION
                if ((rows_A == rows_B) && (columns_A == columns_B)) {
                    System.out.println();
                    System.out.println("***  ADDITION OF MATRIX_A AND MATRIX_B    ***");
                    System.out.println("=============================================");
                    matrixObj_A.addMatrices(matrixObj_B);
                    matrixObj_A.printMatrix_Sum();				
                    System.out.println("=============================================");
                    matrixObj_A.printDuration();
                    System.out.println();		
                }
                else {
                    System.out.println("MATRIX ADDITION CANNOT BE PERFORMED. NUMBER OF ROWS AND/OR COLUMNS NOT EQUAL BETWEEN THE MATRICES.");
                    System.out.println();
                }
                break;
            }
            case 2: {
                // USER WANTS TO PERFORM MATRIX SUBTRACTION
                if ((rows_A == rows_B) && (columns_A == columns_B)) {
                    System.out.println();
                    System.out.println("***  SUBTRACTION OF MATRIX_A AND MATRIX_B ***");
                    System.out.println("=============================================");
                    matrixObj_A.subtractMatrices(matrixObj_B);
                    matrixObj_A.printMatrix_Sum();
                    System.out.println("=============================================");
                    matrixObj_A.printDuration();
                    System.out.println();            
                }
                else {
                    System.out.println("MATRIX SUBTRACTION CANNOT BE PERFORMED. NUMBER OF ROWS AND/OR COLUMNS NOT EQUAL BETWEEN THE MATRICES.");
                    System.out.println();
                }
                break;
            }
            case 3: {
                // USER WANTS TO PERFORM MATRIX MULTIPLICATION
                if (columns_A == rows_B) {
                    System.out.println();
                    System.out.println("*** MULTIPLICATION OF MATRIX_A AND MATRIX_B ***");
                    System.out.println("===============================================");
                    matrixObj_A.multiplyMatrices(matrixObj_B);
                    matrixObj_A.printMatrix_Sum();
                    System.out.println("=============================================");
                    matrixObj_A.printDuration();
                    System.out.println();
                }
                else {
                    System.out.println("MATRIX MULTIPLICATION CANNOT BE PERFORMED. NUMBER OF COLUMNS OF MATRIX_A NOT EQUAL TO NUMBER OF ROWS IN MATRIX_B.");
                    System.out.println();
                }
                break;
            }
            case -999: {
                // USER WANTS TO EXIT THE PROGRAM
                System.out.println("EXIT");
                System.exit(0);
            }
            default: {
                // INVALID USER INPUT
                System.out.println("INVALID MATRIX OPERATION CHOICE. EXITING PROGRAM.");
                System.exit(1);
            }
            }// END OF SWITCH-CASE MATRIX OPERATIONS
            loopCounter++;
        } while (loopCounter < MAX_LOOP_TEN);
        
    }// END OF Main
}// END OF CLASS Matrix