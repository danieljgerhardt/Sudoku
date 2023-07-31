#include <iostream>
#include "sudoku.cpp"
#include "generator.cpp"
#include "solver.cpp"

using namespace std;

int main() {
    
    //Sudoku sudoku = genBoard();
    //cout << sudoku.toString() << endl;
    
    //removeRandomSquares(sudoku, 40);

    //cout << sudoku.toString() << endl;
    
    //cout << solvePuzzle(sudoku).toString() << endl;

    Sudoku unsolved = genUnsolvedRecDriver(58);

    cout << unsolved.toString() << endl;
    
    return 0;
}