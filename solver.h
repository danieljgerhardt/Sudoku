#ifndef SOLVER_H
#define SOLVER_H
#include "sudoku.h"

bool solvePuzzle(Sudoku toSolve);

int bruteForcePass(Sudoku toSolve);

void matrixSolve(int x, int y, Sudoku toSolve);

void boxMatrixSolve(int box, Sudoku toSolve);

void rowMatrixSolve(int row, Sudoku toSolve);

void columnMatrixSolve(int column, Sudoku toSolve);

#endif