import os, sys
import time
import multiprocessing as mp
import numpy as np
import lib
import time
from matplotlib import pyplot as plt

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

maxtime=1
dimensions=range(1,11)

for (function, label) in zip((lib.permanent, perm_ryser), ("C", "Python")):
    counts=[]
    for dimension in dimensions:
        print dimension
        real=np.random.uniform(-1, 1, dimension*dimension).reshape((dimension, dimension))
        imag=np.random.uniform(-1, 1, dimension*dimension).reshape((dimension, dimension))
        submatrix=real+1j*imag

        t=time.clock()
        n=0
        while time.clock()-t < maxtime:
            for i in range(5):
                function(submatrix)
            n+=5
        counts.append(n)

    plt.plot(dimensions, counts, '.-', label=label)

plt.ylabel('Number of permanents per second')
plt.xlabel('Dimension')
plt.xlim(min(dimensions), max(dimensions))
plt.legend()
plt.semilogy()
plt.savefig('out.pdf')
