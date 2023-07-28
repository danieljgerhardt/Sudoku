#include <iostream>
#include <string.h>
#include "solver.h"
#include "sudoku.h"
#include "generator.h"

Sudoku solvePuzzle(Sudoku toSolve) {
    /*for (int i = 0; i < 30; i++) {
        bruteForcePass(toSolve);
    }
    return toSolve;*/
    for (int i = 0; i < 9; i++) {
        boxMatrixSolve(i, toSolve);
    }
    return toSolve;
    
}

void bruteForcePass(Sudoku toSolve) {
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
                    toSolve.setValue(x, y, val);
                }
            }
            
        }
    }
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
                    /*std::cout << "FOUND UNSOLVED SQUARE" << std::endl;
                    std::cout << "box: " << box << std::endl;
                    std::cout << "unsolved square of box: " << mCount << " possible num: " << i << std::endl;*/
                }
            }
            mCount++;
        }
    }
 

    std::cout << "box " << box << std::endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            std::cout << matrix[i][j];
        }
        std::cout << std::endl;
    }

    int x = -1, y = -1, numOptions;
    for (int j = 0; j < 9; j++) {
        numOptions = 0;
        for (int i = 0; i < 9; i++) {
            if (matrix[i][j] == 1) {
                numOptions += 1;
                if (numOptions == 1) {
                    //Test
                    std::cout << i << ", " << j << std::endl;
                    //End test
                    x = row + (i % 3);
                    if (i < 3) {
                        y = col;
                    } else if (i < 6) {
                        y = col + 1;
                    } else {
                        y = col + 2;
                    }
                }
            }
        }
        if (numOptions == 1) {
            std::cout << "SOLVING SQUARE" << std::endl;
            std::cout << "box: " << box << std::endl;
            std::cout << "x: " << x << " y: " << y << " possible num: " << j + 1 << std::endl;
            toSolve.setValue(x, y, j + 1);
        }
    }

    //pseudocode:
    //1) iterate through the numbers in each column
    //2) count the number of 1s
    //3) if there is one 1, that means there is one option
    //4) update the square that has only one option

}