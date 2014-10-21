/* Computes the permanent, given a numpy array */

#include <Python.h>
#include <numpy/arrayobject.h>
#include <math.h>

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
#define m(x0) (*(npy_float64*)((PyArray_DATA(py_m) +                \
                                (x0) * PyArray_STRIDES(py_m)[0])))
#define m_shape(i) (py_m->dimensions[(i)])

#define r(x0, x1) (*(npy_float64*)((PyArray_DATA(py_r) +                \
                                    (x0) * PyArray_STRIDES(py_r)[0] +   \
                                    (x1) * PyArray_STRIDES(py_r)[1])))
#define r_shape(i) (py_r->dimensions[(i)])

#define v(x0, x1) (*(npy_float64*)((PyArray_DATA(py_v) +                \
                                    (x0) * PyArray_STRIDES(py_v)[0] +   \
                                    (x1) * PyArray_STRIDES(py_v)[1])))
#define v_shape(i) (py_v->dimensions[(i)])

#define F(x0, x1) (*(npy_float64*)((PyArray_DATA(py_F) +              \
                                    (x0) * PyArray_STRIDES(py_F)[0] +   \
                                    (x1) * PyArray_STRIDES(py_F)[1])))
#define F_shape(i) (py_F->dimensions[(i)])

static PyObject *permanent(PyObject *self, PyObject *args) {
  // Declare variables. 
  npy_int64 d, i, j;
  Py_complex sum;
  PyArrayObject *submatrix;

  // Parse variables. 
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {
    return NULL;
  }

  // Compute the permanent
  for(i = 0; i < d; ++i) {
    for(j = 0; j<d; ++j) {

    }
  }

  PyObject *output=PyComplex_FromCComplex(sum);
  return output;
}
