#include <iostream>
#include <string.h>
#include "solver.h"
#include "sudoku.h"
#include "generator.h"

Sudoku solvePuzzle(Sudoku toSolve) {
    //Try brute force while it works, if any pass of bruteForce doesn't fix 0's, try matrix solve, then pass back

    for (int i = 0; i < 100; i++){
        if (bruteForcePass(toSolve) < 2){
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    matrixSolve(i, j, toSolve);
                }
            }
        }
    }
    return toSolve;
}

int bruteForcePass(Sudoku toSolve) {
    int numSolved = 0;
    for (int x = 0; x < 9; x++) {
        for (int y = 0; y < 9; y++) {
            if (toSolve.getValue(x, y) == 0) {
                int iter = 0;
                bool easy = true;
                int val;
                for (int k = 1; k < 10; k++) {
                    if (toSolve.isValidSquare(x, y, k)){
                        val = k;
                        iter++;
                        if (iter > 1){
                            easy = false;
                            break;
                        }
                    }
                }
                if (easy) {
                    numSolved++;
                    toSolve.setValue(x, y, val);
                }
            }
        }
    }
    return numSolved;
}

//only one square in a region that CAN be a value || regions: 9 boxes, 9 columns, 9 rows
//   1  2  3  4  5  6  7  8  9 //Possible values, i
//1: 0  0
//2: 0  0
//3: 0  0
//4: 0  0
//5: 0  0
//6: 1  1 //AHHHHHHHHH
//7: 0  0
//8: 0  0
//9: 0  0

void matrixSolve(int x, int y, Sudoku toSolve) {
    boxMatrixSolve(toSolve.getBox(x, y), toSolve);
    rowMatrixSolve(x, toSolve);
    columnMatrixSolve(y, toSolve);
}

void boxMatrixSolve(int box, Sudoku toSolve) {       
    int row = box - (box % 3); //top left of box
    int col = (box * 3) % 9;
    int matrix[9][9];
    memset(matrix, 0, sizeof(matrix));
    int mCount = 0, numToSolve = 0;

    for (int r = row; r < row + 3; r++) {
        for (int c = col; c < col + 3; c++) {
            if (!toSolve.isPopulatedSquare(r, c)) {
                numToSolve++;
            }
        }
    }
    if (numToSolve == 0) {
        return;
    }

    for (int r = row; r < row + 3; r++) {
        for (int c = col; c < col + 3; c++) {
            for (int i = 1; i < 10; i++) {
                if (toSolve.isValidSquare(r, c, i)) {
                    matrix[mCount][i - 1] = 1;
                }
            }
            mCount++;
        }
    }

    int x = -1, y = -1, numOptions;
    for (int j = 0; j < 9; j++) {
        numOptions = 0;
        for (int i = 0; i < 9; i++) {
            if (matrix[i][j] == 1) {
                numOptions += 1;
                if (numOptions == 1) {
                    if (i < 3) {
                        x = row;
                    } else if (i < 6) {
                        x = row + 1;
                    } else {
                        x = row + 2;
                    }
                    y = col + (i % 3); 
                }
            }
        }
        if (numOptions == 1) {
            toSolve.setValue(x, y, j + 1);
        }
    }
}

void rowMatrixSolve(int row, Sudoku toSolve) {
    int matrix[9][9];
    memset(matrix, 0, sizeof(matrix));
    int numToSolve = 0;

    for (int i = 0; i < 9; i++) {
        if (!toSolve.isPopulatedSquare(row, i)) {
            numToSolve++;
        }
    }
    if (numToSolve == 0) {
        return;
    }

    for (int col = 0; col < 9; col++) {
        for (int i = 1; i < 10; i++) {
            if (toSolve.isValidSquare(row, col, i)) {
                matrix[col][i - 1] = 1;
            }
        }
    }
    
    int numOptions, column;
    for (int j = 0; j < 9; j++) {
        numOptions = 0;
        for (int i = 0; i < 9; i++) {
            if (matrix[i][j] == 1) {
                numOptions += 1;
                if (numOptions == 1) {
                    column = i;
                }
            }
        }
        if (numOptions == 1) {
            std::cout << "row: " << row << ", col: " << column << std::endl;
            toSolve.setValue(row, column, j + 1);
        }
    }
}

void columnMatrixSolve(int column, Sudoku toSolve) {
    int matrix[9][9];
    memset(matrix, 0, sizeof(matrix));
    int numToSolve = 0;

    for (int i = 0; i < 9; i++) {
        if (!toSolve.isPopulatedSquare(i, column)) {
            numToSolve++;
        }
    }
    if (numToSolve == 0) {
        return;
    }

    for (int row = 0; row < 9; row++) {
        for (int i = 1; i < 10; i++) {
            if (toSolve.isValidSquare(row, column, i)) {
                matrix[row][i - 1] = 1;
            }
        }
    }
    
    int numOptions, row;
    for (int j = 0; j < 9; j++) {
        numOptions = 0;
        for (int i = 0; i < 9; i++) {
            if (matrix[i][j] == 1) {
                numOptions += 1;
                if (numOptions == 1) {
                    row = i;
                }
            }
        }
        if (numOptions == 1) {
            toSolve.setValue(row, column, j + 1);
        }
    }
}