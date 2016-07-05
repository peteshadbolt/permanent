/* Functions to compute the permanent, given a numpy array */
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include "npy_util.h"
#include "bithacks.h"

// Forward function declaration 
static PyObject *permanent(PyObject *self, PyObject *args);    

// Method list
static PyMethodDef methods[] = {                                
  { "permanent", permanent, METH_VARARGS, "Computes the permanent of a numpy using the most appropriate method available"},
  { NULL, NULL, 0, NULL } // Sentinel
};

// Module initialization
PyMODINIT_FUNC initpermanent(void) {                            
  (void) Py_InitModule("permanent", methods);
  import_array();
}

// Ryser's algorithm 
static npy_complex128 ryser(PyArrayObject *submatrix) {
    int n = (int) PyArray_DIM(submatrix, 0);
    npy_complex128 rowsum, rowsumprod;
    npy_complex128 perm = complex_zero;
    int exp = 1 << n; 
    int i, y, z;
    for (i=0; i<exp; ++i) {
        rowsumprod = complex_one;
        for (y=0; y<n; ++y) {               
            rowsum = complex_zero;
            for (z=0; z<n; ++z) { 
                if ((i & (1 << z)) != 0) { complex_inc(&rowsum, SM(z, y)); }
            }
            complex_multiply(&rowsumprod, rowsum);
        }
        complex_inc(&perm, complex_float_prod(rowsumprod, bitparity(i)));
    }
    if (n%2 == 1) { perm=complex_float_prod(perm, -1); }
    return perm;
}


// This is a wrapper which chooses the optimal permanent function
static PyObject *permanent(PyObject *self, PyObject *args) {
  // Parse the input
  PyArrayObject *submatrix;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {return NULL;}
  if (!PyArray_ISCOMPLEX(submatrix)) {
      PyErr_SetString(PyExc_TypeError, "Array dtype must be `complex`.");
      return NULL;
  }

  // Compute the permanent
  npy_complex128 p = ryser(submatrix);
  return PyComplex_FromDoubles(p.real, p.imag);
}
