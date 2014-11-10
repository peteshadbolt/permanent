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
static const npy_complex128 complex_zero = {.real=0, .imag=0};
static const npy_complex128 complex_one = {.real=1, .imag=0};
static void complex_inc(npy_complex128 a, npy_complex128 b) { a.real+=b.real; a.imag+=b.imag;}
static npy_complex128 complex_mult(npy_complex128 a, npy_complex128 b) { 
    npy_complex128 x;
    x.real = a.real*b.real+a.imag*b.imag;
    x.imag = a.real*b.imag+a.imag*b.real;
    return x;
}

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

// The parity
/*static int parity(int x) { return 0; }*/

// Ryser's algorithm takes exponential time
// This just calculates the sum
static npy_complex128 perm_ryser(PyArrayObject *submatrix) {
    int n = (int) PyArray_DIM(submatrix, 0);
    int i = 0; int z = 0; int y = 0;
    npy_complex128 prod;
    npy_complex128 perm = complex_zero;
    npy_complex128 sum = complex_zero;
    int exp=1 << n; //TODO: use a shift operator

    // Iterate over exponentially many index strings
    for (i=0; i<exp; ++i) {
        prod = complex_one;
        for (y=0; y<n; ++y) {               // Rows
            sum = complex_zero;
            for (z=0; z<n; ++z) {           // Columns
                if ((i & (1 << z)) > 0) { complex_inc(sum, SM(z,y)); }
            }
            prod = complex_mult(prod, sum);
        }
        /*complex_add(perm, parity(i) * prod);*/
        complex_inc(perm, prod);
    }
    /*return c_prod((pow(-1,n)), perm); #TODO power is fucked*/
    return perm;
}

// This is basically a wrapper which chooses the optimal permanent function
static PyObject *permanent(PyObject *self, PyObject *args) {
  // Parse input
  PyArrayObject *submatrix;
  if (!PyArg_ParseTuple(args, "O!", &PyArray_Type, &submatrix)) {return NULL;}

  npy_complex128 p = perm_ryser(submatrix);
  return PyComplex_FromDoubles(p.real, p.imag);
}
