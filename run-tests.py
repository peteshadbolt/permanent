import os
import time
import multiprocessing as mp
import numpy as np
import lib
import time

dimension=2
real=np.ones((dimension, dimension))
imag=np.ones((dimension, dimension))*0
submatrix=real+1j*imag
submatrix[0,0]*=2
print submatrix

p=lib.permanent(submatrix)
print p
