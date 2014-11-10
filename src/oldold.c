/* Computes the permanent, given a numpy array */

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <complex.h> 

// Globals 

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
static npy_complex64 perm_ryser(PyArrayObject *submatrix) {
  int size = (int) PyArray_DIM(submatrix, 0);
  npy_complex64 p;
  p.real=0; p.imag=0; 
  int i, j;
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j) {
      npy_complex64 q = SM(i,j);
      printf("real: %f\n", q.real);
      printf("imag: %f\n", q.imag);
      p.real += q.real;
      p.imag += q.imag;
    }
  }
  return p;
}

// This is basically a wrapper which chooses the optimal permanent function
static PyObject *permanent(PyObject *self, PyObject *args) {
  // Parse input
  PyArrayObject *submatrix;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {
    return NULL;
  }

  // Check for stupid mistakes
  if ((int) PyArray_NDIM(submatrix) != 2) {return NULL;}
  int size = (int) PyArray_DIM(submatrix, 0);
  if ((int) PyArray_DIM(submatrix, 1) != size) {return NULL;}

  // Get the permanent, convert to a python object, and return
  npy_complex64 p = perm_ryser(submatrix);
  return PyComplex_FromDoubles(p.real, p.imag);
}
