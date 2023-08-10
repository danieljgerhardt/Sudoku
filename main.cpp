#include <iostream>
#include "sudoku.cpp"
#include "generator.cpp"
#include "solver.cpp"

using namespace std;

int main() {
    
    //Sudoku sudoku = genBoard();
    //cout << sudoku.toString() << endl;
    
    //removeRandomSquares(sudoku, 64);

    //cout << sudoku.toString() << endl;

    //solvePuzzle(sudoku);
    
    //cout << sudoku.toString() << endl;

    //Sudoku unsolved = genUnsolvedRecDriver(57);

    Sudoku unsolved = unsolvedUniqueDriver(60);

    cout << unsolved.toString() << endl;

    return 0;
}