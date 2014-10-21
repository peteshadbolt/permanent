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


/*****************************************************************************
 * compute_F                                                                 *
 *****************************************************************************/
static inline void compute_F(npy_int64 N,
                             PyArrayObject *py_m,
                             PyArrayObject *py_r,
                             PyArrayObject *py_F) {
  npy_int64 i, j;
  npy_float64 sx, sy, Fx, Fy, s3, tmp;
  
  // Set all forces to zero. 
  for(i = 0; i < N; ++i) {
    F(i, 0) = F(i, 1) = 0;
  }
  
  // Compute forces between pairs of bodies.
  for(i = 0; i < N; ++i) {
    for(j = i + 1; j < N; ++j) {
      sx = r(j, 0) - r(i, 0);
      sy = r(j, 1) - r(i, 1);

      s3 = sqrt(sx*sx + sy*sy);
      s3 *= s3 * s3;

      tmp = m(i) * m(j) / s3;
      Fx = tmp * sx;
      Fy = tmp * sy;

      F(i, 0) += Fx;
      F(i, 1) += Fy;

      F(j, 0) -= Fx;
      F(j, 1) -= Fy;
    }
  }
}

static PyObject *permanent(PyObject *self, PyObject *args) {
  // Declare variables. 
  npy_int64 d, i, j;
  npy_float64 output;
  PyArrayObject *submatrix;

  // Parse variables. 
  if (!PyArg_ParseTuple(args, "ldllO!O!O!O!",
                        &threads,
                        &dt,
                        &steps,
                        &N,
                        &PyArray_Type, &submatrix)) {
    return NULL;
  }

  // Compute the permanent
  for(i = 0; i < d; ++i) {
    for(j = 0; j<d; ++j) {

    }
  }

  Py_RETURN_NONE;
}
