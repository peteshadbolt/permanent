/* Computes the permanent, given a numpy array */
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>

// Array access macros.
#define SM(x0, x1) (*(npy_complex128*)((PyArray_DATA(submatrix) + \
                    (x0) * PyArray_STRIDES(submatrix)[0] +  \
                    (x1) * PyArray_STRIDES(submatrix)[1])))
#define SM_shape(x0) (int) PyArray_DIM(submatrix, x0)

// Complex numbers
static const npy_complex128 complex_one = {.real=1, .imag=0};
static const npy_complex128 complex_zero = {.real=0, .imag=0};
static void complex_inc(npy_complex128 a, npy_complex128 b) { a.real+=b.real; a.imag+=b.imag;}
static npy_complex128 complex_prod(npy_complex128 a, npy_complex128 b) { 
    npy_complex128 x;
    x.real = a.real*b.real+a.imag*b.imag;
    x.imag = a.real*b.imag+a.imag*b.real;
    return x;
}

// Boilerplate
static PyObject *permanent(PyObject *self, PyObject *args);     // Forward function declaration
static PyMethodDef methods[] = {                                // Method list
  { "permanent", permanent, METH_VARARGS, "Compute the permanent"},
  { NULL, NULL, 0, NULL } /* Sentinel */
};
PyMODINIT_FUNC initpermanent(void) {                            // Module initialization
  (void) Py_InitModule("permanent", methods);
  import_array();
}

// Ryser's algorithm 
static npy_complex128 perm_ryser(PyArrayObject *submatrix) {
    int n = (int) PyArray_DIM(submatrix, 0);
    int i = 0; int z = 0; int y = 0;
    npy_complex128 prod;
    npy_complex128 perm = complex_zero;
    npy_complex128 sum = complex_zero;
    int exp = 1 << n; 
    printf("2^%d = %d\n", n, exp);

    // Iterate over exponentially many index strings
    for (i=0; i<exp; ++i) {
        prod = complex_one;
        printf("prod %.3f %.3f \n", prod.real, prod.imag);
        for (y=0; y<n; ++y) {               // Rows
            sum = complex_zero;
            for (z=0; z<n; ++z) {           // Columns
                printf("element %.3f %.3f \n", SM(z,y).real, SM(z,y).imag);
                // Below is a suspicious line
                if ((i & (1 << z)) > 0) { complex_inc(sum, SM(z,y)); }
                printf("sum %.3f %.3f \n", sum.real, sum.imag);
            }
            prod = complex_prod(prod, sum);
        }
        printf("prod %.3f %.3f \n", prod.real, prod.imag);
        if (i%2 == 0) {prod.real*=-1; prod.imag*=-1;}
        complex_inc(perm, prod);
    }
    if (i%2 == 0) {perm.real*=-1; perm.imag*=-1;}
    return perm;
}

// This is a wrapper which chooses the optimal permanent function
static PyObject *permanent(PyObject *self, PyObject *args) {
  // Parse the input
  PyArrayObject *submatrix;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {return NULL;}

  // Compute the permanent
  npy_complex128 p = perm_ryser(submatrix);
  return PyComplex_FromDoubles(p.real, p.imag);
}
