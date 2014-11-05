/* Computes the permanent, given a numpy array */

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <complex.h> 

// Globals 
PyArrayObject *submatrix;
int size;

// Boilerplate: Forward function declaration.
static PyObject *permanent(PyObject *self, PyObject *args); 

// Boilerplate: method list.
static PyMethodDef methods[] = {
  { "permanent", permanent, METH_VARARGS, "Compute the permanent"},
  { NULL, NULL, 0, NULL } /* Sentinel */
};

// Boilerplate: Module initialization.
PyMODINIT_FUNC initpermanent(void) {
  (void) Py_InitModule("permanent", methods);
  import_array();
}

// Array access macros.
#define SM(x0, x1) (*(npy_complex64*)((PyArray_DATA(submatrix) + \
                    (x0) * PyArray_STRIDES(submatrix)[0] +  \
                    (x1) * PyArray_STRIDES(submatrix)[1])))
#define SM_shape(x0) (int) PyArray_DIM(submatrix, x0)

// Ryser's algorithm takes exponential time
// The advantage over naive perm() only kicks in at around 6x6 matrices 
// TODO: should take matrix as arg really, get rid of consts
static npy_complex64 perm_ryser(void) {
  npy_complex64 p;
  p.real=0; p.imag=0; 
  int i, j;
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j) {
      npy_complex64 q = SM(0,0);
      p.real += q.real;
      p.imag += q.imag;
    }
  }
  return p;
}

void TODO(void) {
    int n = size;
    int i = 0; int z = 0; int y = 0;
    npy_complex64 perm; perm.real=0; perm.imag=0; 
    npy_complex64 prod; 
    npy_complex64 sum; sum.real=0; sum.imag=0; 
    npy_complex64 element;
    int exp=pow(2.0, n);

    // Iterate over exponentially many index strings
    for (i=0; i<exp; ++i) {
        prod.real = 1; prod.imag=0;
        for (y=0; y<n; ++y) {               // Rows
            sum.real = 0; sum.imag = 0;
            for (z=0; z<n; ++z) {           // Columns
                if ((i & (1 << z)) > 0) { sum.real += SM(z,y).real;  sum.imag += SM(z,y).imag; }
            }
            prod = prod*sum;
        }
        perm += parity(i) * prod;
    }
    return (pow(-1,n))*perm;
}

// This is basically a wrapper which chooses the optimal permanent function
static PyObject *permanent(PyObject *self, PyObject *args) {
  // Parse input
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {
    return NULL;
  }

  // Check for stupid mistakes
  if ((int) PyArray_NDIM(submatrix) != 2) {return NULL;}
  size = (int) PyArray_DIM(submatrix, 0);
  if ((int) PyArray_DIM(submatrix, 1) != size) {return NULL;}

  // Get the permanent, convert to a python object, and return
  npy_complex64 p = perm_ryser();
  return PyComplex_FromDoubles(p.real,p.imag);
}
