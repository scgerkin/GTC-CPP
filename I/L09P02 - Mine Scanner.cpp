/*
Name: Stephen Gerkin
Date: 03/08/2019
Lesson 9 Program 2
Program Title:
    Mine "Scanner"
Program Description:
    Program takes input from a file with values for a minefield
    Then determines which squares in the field are mines
    If a square is not a mine, but is touching a mine, it determines how many
    mines that square is touching
    The data is then written to an output file.
*/
#include <iostream>
#include <fstream>
using namespace std;

// global constant for max array size
const int MAX_SIZE = 200;

// function prototypes
void
buildField(ifstream&, int[][MAX_SIZE], int, int),    // creates new array vals
determineSquares(int[][MAX_SIZE], int, int),         // determines square vals
writeOut(ofstream&, int, int[][MAX_SIZE], int, int); // writes vals to file

/*
* Main function body
*/
int main() {
    // open files for input/output
    ifstream inFile("inputdata.dat");
    ofstream outFile("outputdata.dat");
        
    // array for minefield
    int minefield[MAX_SIZE][MAX_SIZE];
    
    int fields = 0; // var for field #, init as 0
    int row;        // var for # rows in input file
    int col;        // var for # cols in input file

    // entrance msg
    cout << "Welcome to the mine scanning utility." << endl
        << "Minefields will be read from \"inputdata.dat\" file" << endl
        << "The data will be analyzed for mine positions and written to file."
        << endl << endl;

    // get first field size
    inFile >> row >> col;

    // do stuff while there's a field
    while (row != 0 && col != 0) {
        
        // increment number of fields
        fields++;
        
        // create the array from the input file
        buildField(inFile, minefield, row, col);

        // determine the square values of the field
        determineSquares(minefield, row, col);

        // write the values of the squares to file
        writeOut(outFile, fields, minefield, row, col);

        // get next field size
        inFile >> row >> col;
    }

    // exit msg
    cout << "Program is finished scanning for mines." << endl
        << "A total of " << fields << " fields were scanned." << endl
        << "The field information has been written to: \"outputdata.dat\"."
        << endl << endl;

    // close files
    inFile.close();
    outFile.close();

    // terminate
    system("pause");
    return 0;
}

/*
* Name:
*   buildField
* Parameters:
*   ifstream&   inFile      input file to read
*   int[][]     minefield   minefield array to build
*   int         row         number of actual rows in field
*   int         col         number of actual columns in field
* Return:
*   none
* Description:
*   Builds the new minefield array with buffer surrounding so that determination
*   function does not go out of bounds of array
*/
void buildField(ifstream& inFile, int minefield[][MAX_SIZE], int row, int col) {
    int rowPos;     // row position variable
    int colPos;     // column position variable
    char readVal;   // variable to read in '*' as a mine

    // init array with field and buffer as 0
    for (rowPos = 0; rowPos <= (row + 1); rowPos++) {
        for (colPos = 0; colPos <= (col + 1); colPos++) {
            minefield[rowPos][colPos] = 0;
        }
    }

    // place mines
    for (rowPos = 1; rowPos <= row; rowPos++) {
        for (colPos = 1; colPos <= col; colPos++) {
            inFile >> readVal;
            // if a mine is read in, decrement the square to -1
            if (readVal == '*') {
                minefield[rowPos][colPos]--;
            }
        }
    }
}

/*
* Name:
*   determineSquares
* Parameters:
*   int[][]     minefield   minefield array
*   int         row         number of actual rows in minefield
*   int         col         number of actual columns in minefield
* Return:
*   none
* Description:
*   Function scans through the minefield looking for mines in each square
*   If a mine is found, the squares surrounding the mine are incremented
*/
void determineSquares(int minefield[][MAX_SIZE], int row, int col) {

    int rowPos;     // var for row value: field scan
    int colPos;     // var for col value: field scan
    
    int mineRow;    // var for row value: incrementing around mine
    int mineCol;    // var for col value: incrementing around mine

    // scan the field for mines
    for (rowPos = 1; rowPos <= row; rowPos++) {
        for (colPos = 1; colPos <= col; colPos++) {
            // if current square is a mine
            if (minefield[rowPos][colPos] == -1) {
                // increment the surrounding squares
                for (mineRow = (rowPos - 1); mineRow <= (rowPos + 1);
                     mineRow++) {
                    for (mineCol = (colPos - 1); mineCol <= (colPos + 1);
                         mineCol++) {
                        // but only if the square is not a mine
                        if (minefield[mineRow][mineCol] >= 0) {
                            minefield[mineRow][mineCol]++;
                        }
                    }
                }
            }
        }
    }
}

/*
* Name:
*   writeOut
* Parameters:
*   ofstream    outFile     output file for writing to
*   int         field       minefield number
*   int[][]     minefield   minefield array to write
*   int         row         number of rows in minefield
*   int         col         number of columns in minefield
* Return:
*   none
* Description:
*   writes the array to file
*/
void writeOut(ofstream& outFile, int field, int minefield[][MAX_SIZE], int row, int col) {
    // write header for field
    outFile << "Field #" << field << ":" << endl << endl;

    // write array
    for (int i = 1; i <= row; i++) {
        for (int j = 1; j <= col; j++) {
            // if array value is -1, write a mine character
            if (minefield[i][j] == -1) {
                outFile << "*";
            }
            // otherwise write the value
            else {
                outFile << minefield[i][j];
            }
        }
        // write new line after each column
        outFile << endl << endl;
    }
}