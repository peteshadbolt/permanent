import os
import time
import multiprocessing as mp
import numpy as np
import lib
import time

def perm_ryser(a):
    ''' the permanent calculated using the ryser formula. much faster than the naive approach '''
    n,n2=a.shape
    z=np.arange(n)
    irange=xrange(2**n)
    get_index=lambda i: (i & (1 << z)) != 0 
    get_term=lambda index: ((-1)**np.sum(index))*np.prod(np.sum(a[index,:], 0))
    indeces=map(get_index, irange)
    terms=map(get_term, indeces) 
    return np.sum(terms)*((-1)**n)

dimension=2
real=np.ones((dimension, dimension))
imag=np.ones((dimension, dimension))*0
submatrix=real+1j*imag
submatrix[0,0]*=2
print lib.permanent(submatrix)
print perm_ryser(submatrix)
