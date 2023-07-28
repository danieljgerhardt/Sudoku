#ifndef GENERATOR_H
#define GENERATOR_H
#include "sudoku.h"

void seedRand();

int getRand();
            
int getValidRand(int x, int y, Sudoku board);

int* getRandomPermutation();
        
Sudoku genBoard();

bool genRecursive(int x, int y, Sudoku board);

void removeRandomSquares(Sudoku board, int amt);

#endif