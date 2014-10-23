/* Computes the permanent, given a numpy array */

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>
#include <complex.h> 

// Forward function declaration.
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

/*****************************************************************************
 * Array access macros.                                                      *
 *****************************************************************************/
#define r(x0, x1) (*(npy_float64*)((PyArray_DATA(py_r) +                \
                                    (x0) * PyArray_STRIDES(py_r)[0] +   \
                                    (x1) * PyArray_STRIDES(py_r)[1])))
#define r_shape(i) (py_r->dimensions[(i)])

static PyObject *permanent(PyObject *self, PyObject *args) {
  // Parse input
  PyArrayObject *submatrix;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {
    return NULL;
  }

  // Testing algebra
  npy_complex128 a;

  /*a.real=1; a.imag=1;*/
  /*b.real=1; b.imag=1;*/

  /*a.real=a.real+b.real;*/
  /*a.imag=a.imag+b.imag;*/

  // Let's see if we can add to a number from the numpy array
  int xpos=0; int ypos=0;
  a=(*(npy_complex128*)((PyArray_DATA(submatrix) +                \
                     (xpos) * PyArray_STRIDES(submatrix)[0] +   \
                     (ypos) * PyArray_STRIDES(submatrix)[1])));



  // Convert to a python complex number and return
  PyObject *output=PyComplex_FromDoubles(a.real,a.imag);
  return output;

  /*

  // Compute the permanent
  for(i = 0; i < d; ++i) {
    for(j = 0; j<d; ++j) {
        sum+=1j;
    }
  }
  */

}
