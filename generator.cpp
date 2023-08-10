#include "generator.h"

    using namespace std;

    int nums[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

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
        bool looping = true;
        for (int i = 0; i < amt; i++) {
            x = getRand() - 1, y = getRand() - 1;
            while (looping) {
                if (board.getValue(x, y) != 0) {
                    board.setValue(x, y, 0);
                    looping = false;
                }
                x = getRand() - 1, y = getRand() - 1;
            }
        }
    }

    /*Sudoku genUnsolved(int squaresToRemove) {
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
        while (!genUnsolvedRec(sudoku, prev, squaresToRemove, 0)) {
            sudoku = genBoard();
        }
        //genUnsolvedRec(sudoku, prev, squaresToRemove, backOut);
        return sudoku;
    }
    
    bool genUnsolvedRec(Sudoku sudoku, Sudoku prev, int squaresToRemove, int backOut) {
        if (squaresToRemove == 0) {
            return true;
        }
        if (backOut > (81 - squaresToRemove)) {
        //if (squaresToRemove < 7 && backOut > 3) {
            //std::cout << "giving up" << std::endl;
            return false;
        }
        
        sudoku.copyBoard(prev);
        removeRandomSquares(sudoku, 1);
        Sudoku temp;
        sudoku.copyBoard(temp);
        if (!solvePuzzle(temp)) {
            prev.copyBoard(sudoku);
            genUnsolvedRec(sudoku, prev, squaresToRemove, backOut + 1);
        } else {
            return true && genUnsolvedRec(sudoku, prev, squaresToRemove - 1, 0);
        }
    }

    struct coord {
        int x;
        int y;
    };

    
    Sudoku unsolvedJohnStyle(int squaresToRemove) {

        Sudoku board = genBoard();

        coord coords[81];
        memset(coords, 0, sizeof(coords));
        int length = 0;
        
        for (int i = 0; i < squaresToRemove; i++) {
            for (int x = 1; x < 9; x++) {
                for (int y = 1; y < 9; y++) {
                    if (board.getValue(x, y) != 0 && canRemove(board, x, y)) {
                        board.setValue(x, y, 0);
                        coord coordinate;
                        coordinate.x = x;
                        coordinate.y = y;
                        coords[length] = coordinate;
                        length++;
                    }
                }
            }
            coord toRemove = coords[0];
            board.setValue(toRemove.x, toRemove.y, 0);
            memset(coords, 0, sizeof(coords));
            length = 0;
        }
        return board;
    }*/
    
    bool canRemove(Sudoku board, int x, int y) {
        Sudoku temp;
        board.copyBoard(temp);
        temp.setValue(x, y, 0);
        if (solvePuzzle(temp)) {
            return true;
        } else {
            return false;
        }
    }
    
    Sudoku unsolvedUniqueDriver(int squaresToRemove) {
        vector<cvpair> list;
        Sudoku board = genBoard();
        for (int x = 0; x < 9; x++) {
            for (int y = 0; y < 9; y++) {
                cvpair curr;
                curr.x = x;
                curr.y = y;
                curr.val = board.getValue(x, y);
                list.push_back(curr);
            }
        }
        
        //shuffle(list.begin(), list.end(), default_random_engine(seed));
        return unsolvedUnique(board, list, squaresToRemove);
    }
    
    Sudoku unsolvedUnique(Sudoku board, vector<cvpair>& list, int squaresToRemove) {
        shuffle(list.begin(), list.end(), default_random_engine(seed));
        cout << "e" << endl;
        int count = 0;
        vector<cvpair> listCopy = list;
        //copy(list.begin(), list.end(), back_inserter(listCopy));
        while (list.size() > 0) {
            cvpair curr = list.back();
            list.pop_back();
            if (canRemove(board, curr.x, curr.y)) {
                board.setValue(curr.x, curr.y, 0);
                count++;
            } 
            if (count == squaresToRemove) {
                return board;
            }
        }
        return unsolvedUniqueDriver(squaresToRemove);
    }
    