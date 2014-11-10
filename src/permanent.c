/* Computes the permanent, given a numpy array */
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <complex.h> 

// Array access macros.
#define SM(x0, x1) (*(npy_complex128*)((PyArray_DATA(submatrix) + \
                    (x0) * PyArray_STRIDES(submatrix)[0] +  \
                    (x1) * PyArray_STRIDES(submatrix)[1])))
#define SM_shape(x0) (int) PyArray_DIM(submatrix, x0)
#define complex_inc(x0, x1) x0.real+=x1.real; x0.imag+=x1.imag;

// Boilerplate: Forward function declaration, method list, module initialization
static PyObject *permanent(PyObject *self, PyObject *args); 
static PyMethodDef methods[] = {
  { "permanent", permanent, METH_VARARGS, "Compute the permanent"},
  { NULL, NULL, 0, NULL } /* Sentinel */
};
PyMODINIT_FUNC initpermanent(void) {
  (void) Py_InitModule("permanent", methods);
  import_array();
}

// Ryser's algorithm takes exponential time
// This just calculates the sum
static npy_complex128 perm_ryser(PyArrayObject *submatrix) {
  npy_complex128 p = {.real=0, .imag=0};
  int size = (int) PyArray_DIM(submatrix, 0);
  int i, j;
  for (i = 0; i < size; ++i) {
    for (j = 0; j < size; ++j) {
      complex_inc(p, SM(0,0));
    }
  }
  return p;
}


// This is basically a wrapper which chooses the optimal permanent function
static PyObject *permanent(PyObject *self, PyObject *args) {
  // Parse input
  PyArrayObject *submatrix;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {return NULL;}

  npy_complex128 p = perm_ryser(submatrix);
  return PyComplex_FromDoubles(p.real, p.imag);
}
