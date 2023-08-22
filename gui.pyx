import cython
# distutils: sources = sudoku.cpp

cdef extern from "sudoku.cpp":
        pass
        
print("Yay")