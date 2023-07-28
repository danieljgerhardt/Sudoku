#ifndef SOLVER_H
#define SOLVER_H
#include "sudoku.h"

Sudoku solvePuzzle(Sudoku toSolve);

void bruteForcePass(Sudoku toSolve);

void boxMatrixSolve(int box, Sudoku toSolve);

#endif