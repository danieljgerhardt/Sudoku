#include <cstdlib>
#include <string>
#include "sudoku.h"


    Sudoku::Sudoku() {
        board = (int*)calloc(81, sizeof(int));
    }

    int Sudoku::getValue(int x, int y) {
        return board[x * 9 + y];
    }

    void Sudoku::setValue(int x, int y, int val) {
        board[x * 9 + y] = val;
    }

    std::string Sudoku::toString() {
        std::string ret = "  ----------------------------------\n";
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (j == 0) {
                    ret += "| ";
                }
                ret += " " + std::to_string(this->board[i * 9 + j]) + " ";
                if (j % 3 == 2) {
                    ret += " | ";
                }
            }
            if (i % 3 == 2) {
                ret += "\n  ----------------------------------";
            }
            ret += "\n";
        }
        return ret;
    }

    bool Sudoku::rowContains(int row, int val) {
        for (int i = 0; i < 9; i++) {
            if (this->board[row * 9 + i] == val) {
                return true;
            }
        }
        return false;
    }

    bool Sudoku::colContains(int col, int val) {
        for (int i = col; i < 81; i += 9) {
            if (this->board[i] == val) {
                return true;
            }
        }
        return false;
    }

    bool Sudoku::boxContains(int box, int val)  {
        //0 for box = 0, 1, 2
        //3 for box = 3, 4, 5
         //6 for box = 6, 7, 8
        int row = box - (box % 3); //top left of box
        int col = (box * 3) % 9;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (this->board[(row + i) * 9 + (col + j)] == val) {
                    return true;
                } 
            }
        }
        return false;
    }

    bool Sudoku::isValidSquare(int x, int y, int val) {
        if (isPopulatedSquare(x, y)) {
            return false;
        }
        if (!rowContains(x, val) && !colContains(y, val) && !boxContains(this->getBox(x, y), val)) {
            return true;
        }
        return false;
    }

    bool Sudoku::isPopulatedSquare(int x, int y) {
        if (getValue(x, y) == 0) {
            return false;
        }
        return true;
    }

    int Sudoku::getBox(int x, int y) {
        if (x < 3) {
            if (y < 3) {
                return 0;
            } else if (y < 6) {
                return 1;
            } else {
                return 2;
            }
        } else if (x < 6) {
            if (y < 3) {
                return 3;
            } else if (y < 6) {
                return 4;
            } else {
                return 5;
            }
        } else {
            if (y < 3) {
                return 6;
            } else if (y < 6) {
                return 7;
            } else {
                return 8;
            }
        }
    }

    bool Sudoku::isSolved() {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                if (getValue(i, j) == 0) {
                    return false;
                }
            }
        }
        return true;
    }

    void Sudoku::copyBoard(Sudoku receiver) {
        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                receiver.setValue(x, y, getValue(x, y));
            }
        }
    }

    Sudoku getDummyBoard() {
        Sudoku ret = Sudoku();
        return ret;
    }

