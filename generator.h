#ifndef GENERATOR_H
#define GENERATOR_H
#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <random>
#include <chrono>
#include "sudoku.h"
#include "solver.h"

using namespace std;

void seedRand();

int getRand();
            
int getValidRand(int x, int y, Sudoku board);

int* getRandomPermutation();
        
Sudoku genBoard();

bool genRecursive(int x, int y, Sudoku board);

void removeRandomSquares(Sudoku board, int amt);

Sudoku genUnsolved(int squaresToRemove);

Sudoku genUnsolvedRecDriver(int squaresToRemove);
    
bool genUnsolvedRec(Sudoku sudoku, Sudoku prev, int squaresToRemove, int backOut);

bool canRemove(Sudoku board, int x, int y);

Sudoku unsolvedUniqueDriver(int squaresToRemove);

//coordinate value pair
struct cvpair {
    int x;
    int y;
    int val;
};
    
Sudoku unsolvedUnique(Sudoku board, vector<cvpair>& list, int squaresToRemove);

#endif