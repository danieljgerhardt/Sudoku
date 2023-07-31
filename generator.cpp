#include <iostream>
#include "sudoku.h"
#include "solver.h"
#include "generator.h"


    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    void seedRand() {
        srand(time(NULL));
    }

    int getRand() {
        //returns random int from 1 to 9 inclusive
        return rand() % 9 + 1;
    }

    int getValidRand(int x, int y, Sudoku board) {
        int checked[9] = {};
        bool hasValid = false;
        for (int i = 1; i < 10; i++) {
            if (board.isValidSquare(x, y, i)) {
                checked[i - 1] = 1;
                hasValid = true;
            } else {
                checked[i - 1] = 0;
            }
        }
        if (!hasValid) {
            return -1;
        }

        int randNums[9];
        std::copy(std::begin(nums), std::end(nums), std::begin(randNums));
        for (int i = 0; i < 9; i++) {
            int temp = randNums[i];
            int j = getRand() - 1;
            randNums[i] = randNums[j];
            randNums[j] = temp;
        }
        
        //std::cout << randNums[0] << std::endl;
        for (int i = 0; i < 9; i++) {
            int curr = randNums[i];
            if (checked[curr - 1] == 1) {
                return curr;
            }
        }
        return -1;
    }

    Sudoku genBoard() {
        seedRand();
        Sudoku currBoard = Sudoku();
        bool curr = genRecursive(0, 0, currBoard);
        while (!curr) {
            //std::cout << currBoard.toString() << std::endl;
            currBoard = Sudoku();
            curr = genRecursive(0, 0, currBoard);
        }
        return currBoard;
    }

    bool genRecursive(int x, int y, Sudoku board) {
        int valid = getValidRand(x, y, board);
        if (valid == -1) {
            return false;
        }
        board.setValue(x, y, valid);
        if (y < 8) {
            return true && genRecursive(x, y + 1, board);
        } 
        else if (x < 8) {
            return true && genRecursive(x + 1, 0, board);
        } else {
            return true;
        }
    }

    void removeRandomSquares(Sudoku board, int amt) {
        int x, y;
        for (int i = 0; i < amt; i++) {
            x = getRand() - 1, y = getRand() - 1;
            while (1) {
                if (board.getValue(x, y) != 0) {
                    board.setValue(x, y, 0);
                    break;
                }
                x = getRand() - 1, y = getRand() - 1;
            }
        }
    }

    Sudoku genUnsolved(int squaresToRemove) {
        Sudoku curr = genBoard(), temp;
        removeRandomSquares(curr, squaresToRemove);
        curr.copyBoard(temp);
        solvePuzzle(curr);
        while (!curr.isSolved()) {
            curr = genBoard();
            removeRandomSquares(curr, squaresToRemove);
            curr.copyBoard(temp);
            solvePuzzle(curr);
        }
        return temp;
    }

    Sudoku genUnsolvedRecDriver(int squaresToRemove) {
        Sudoku sudoku = genBoard(), prev;
        sudoku.copyBoard(prev);
        while (!genUnsolvedRec(sudoku, prev, squaresToRemove)) {
            sudoku = genBoard();
        }
        return sudoku;
    }
    
    bool genUnsolvedRec(Sudoku sudoku, Sudoku prev, int squaresToRemove) {
        if (squaresToRemove == 0) {
            return true;
        }
        sudoku.copyBoard(prev);
        removeRandomSquares(sudoku, 1);
        Sudoku temp;
        sudoku.copyBoard(temp);
        if (!solvePuzzle(temp)) {
            prev.copyBoard(sudoku);
            genUnsolvedRec(sudoku, prev, squaresToRemove);
        } else {
            return true && genUnsolvedRec(sudoku, prev, squaresToRemove - 1);
        }
    }
