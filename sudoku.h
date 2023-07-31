#ifndef Included_SUDOKU_H
#define Included_SUDOKU_H

class Sudoku {
    public:
        Sudoku();

        int getValue(int x, int y);

        void setValue(int x, int y, int val);

        std::string toString();

        bool rowContains(int row, int val);

        bool colContains(int col, int val);

        bool boxContains(int box, int val);

        bool isValidSquare(int x, int y, int val);

        bool isPopulatedSquare(int x, int y);

        int getBox(int x, int y);

        bool isSolved();

        void copyBoard(Sudoku receiver);
    
    private:
        int* board;
};

#endif