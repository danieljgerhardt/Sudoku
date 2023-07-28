#include <iostream>
#include "sudoku.cpp"
#include "generator.cpp"
#include "solver.cpp"

using namespace std;

int main() {
    
    Sudoku sudoku = genBoard();
    cout << sudoku.toString() << endl;
    
    removeRandomSquares(sudoku, 3);

    cout << sudoku.toString() << endl;
    
    cout << solvePuzzle(sudoku).toString() << endl;
    
    return 0;
}