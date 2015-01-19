import os, sys
import numpy as np
import time
from matplotlib import pyplot as plt
from permanent import permanent
import itertools as it


def permanent(a):
    """ Slow way to compute the permanent """
    r = range(len(a))
    return sum([np.prod(a[r, p]) for p in it.permutations(r)])


if __name__ == '__main__':
    maxtime=1
    dimensions=range(1,11)

    for (function, label) in zip((permanent, perm_ryser), ("C", "Python")):
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

        plt.plot(dimensions, counts, ".-", label=label)

    plt.ylabel("Number of permanents per second")
    plt.xlabel("Dimension")
    plt.xlim(min(dimensions), max(dimensions))
    plt.legend()
    plt.semilogy()
    plt.savefig("out.pdf")
