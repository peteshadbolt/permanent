import os, sys
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

dimension=9
real=np.random.uniform(-1, 1, dimension*dimension).reshape((dimension, dimension))
imag=np.random.uniform(-1, 1, dimension*dimension).reshape((dimension, dimension))
submatrix=real+1j*imag

#print lib.permanent(submatrix), perm_ryser(submatrix)

#sys.exit(0)
#t=time.clock()
#for i in range(1000):
    #perm_ryser(submatrix)
#t1=time.clock()-t

t=time.clock()
for i in range(1000):
    lib.permanent(submatrix)
t2=time.clock()-t
print t2

#print t1/t2
