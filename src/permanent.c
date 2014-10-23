/* Computes the permanent, given a numpy array */

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <complex.h> 

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
#define SM(x0, x1) (*(npy_complex128*)((PyArray_DATA(submatrix) + \
                    (x0) * PyArray_STRIDES(submatrix)[0] +  \
                    (x1) * PyArray_STRIDES(submatrix)[1])))
#define SM_shape(x0) (int) PyArray_DIM(submatrix, x0)

static PyObject *permanent(PyObject *self, PyObject *args) {
  // Parse input
  PyArrayObject *submatrix;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {
    return NULL;
  }

  // Check for stupid mistakes
  if ((int) PyArray_NDIM(submatrix) != 2) {return NULL;}
  int d = (int) PyArray_DIM(submatrix, 0);
  if ((int) PyArray_DIM(submatrix, 1) != d) {return NULL;}

  // This number ends up being the permanent
  npy_complex64 p;
  p.real=0; p.imag=0;

  int i, j;
  for (i = 0; i < d; ++i) {
    for (j = 0; j<d; ++j) {
      npy_complex128 q = SM(0,0);
      p.real += q.real;
      p.imag += q.imag;
    }
  }

  // Convert to a python complex number and return
  PyObject *output=PyComplex_FromDoubles(p.real,p.imag);
  return output;
}
