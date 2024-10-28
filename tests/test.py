import numpy as np
from permanentbis import permanent
from nose.tools import raises

def test_permanent():
    """ Dumb tests """
    m = np.eye(10, dtype=complex)
    assert permanent(m) == 1
    m = np.zeros((10, 10), dtype=complex)
    assert permanent(m) == 0


def test_floaty():
    """ More tests using a precomputed permanent """
    np.random.seed(1234)
    m = np.random.uniform(0, 1, 16) + 1j*np.random.uniform(0, 1, 16)
    m = m.reshape(4,4)
    p = permanent(m)
    assert np.allclose(p, -8.766131870776363+1.072095650303524j)

    
@raises(TypeError)
def test_error():
    """ Should raise a TypeError as we are using the wrong dtype """
    m = np.eye(10, dtype=float)
    permanent(m)
    
