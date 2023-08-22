from setuptools import setup
from Cython.Build import cythonize

setup(ext_modules = cythonize(
           "gui.pyx",                 # our Cython source
           language="c++",             # generate C++ code
      ))