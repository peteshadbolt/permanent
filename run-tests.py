import os
import time
import multiprocessing as mp
import numpy as np
import lib

dimension=8
real=np.random.uniform(0,1,(dimension, dimension))
imag=np.random.uniform(0,1,(dimension, dimension))
submatrix=real+1j*imag

print "OUTPUT:", lib.permanent(submatrix)
