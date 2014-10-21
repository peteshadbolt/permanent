import os
import time
import multiprocessing as mp
import numpy as np
import lib


def test_fn(perm_fn, name, dimension=6, steps=1000, dt=1e-3, bodies=101, threads=1):
    # Test the speed of the evolution function. 
    sreal=np.random.uniform(0,1,(dimension, dimension))
    scomp=np.random.uniform(0,1,(dimension, dimension))
    submatrix=sreal+1j*scomp

    t0 = time.time()
    for i in range(steps):
        p=perm_fn(submatrix)
    t1 = time.time()

    print "{0} ({1}): {2} steps/sec".format(name, threads, int(steps / (t1 - t0)))
    

if __name__ == "__main__":
    d=4
    steps=1000

    # Test on one core
    test_fn(lib.perm_python, "1 core, C", steps=steps, threads=1)

    # Test on one core
    test_fn(lib.perm_c, "1 core, C", steps=steps, threads=1)
    
    # Test on four cores
    test_fn(lib.perm_c, "All cores, C", steps=steps/threads, threads=threads)


