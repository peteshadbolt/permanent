/* Computes the permanent, given a numpy array */
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <numpy/arrayobject.h>

// Array access macros.
#define SM(x0, x1) (*(npy_complex128*)((PyArray_DATA(submatrix) + \
                    (x0) * PyArray_STRIDES(submatrix)[0] +  \
                    (x1) * PyArray_STRIDES(submatrix)[1])))
#define SM_shape(x0) (int) PyArray_DIM(submatrix, x0)

int countbits(unsigned int n) 
{
    int q=n;
    q = (q & 0x5555555555555555) + ((q & 0xAAAAAAAAAAAAAAAA) >> 1);
    q = (q & 0x3333333333333333) + ((q & 0xCCCCCCCCCCCCCCCC) >> 2);
    q = (q & 0x0F0F0F0F0F0F0F0F) + ((q & 0xF0F0F0F0F0F0F0F0) >> 4);
    q = (q & 0x00FF00FF00FF00FF) + ((q & 0xFF00FF00FF00FF00) >> 8);
    q = (q & 0x0000FFFF0000FFFF) + ((q & 0xFFFF0000FFFF0000) >> 16);
    q = (q & 0x00000000FFFFFFFF) + ((q & 0xFFFFFFFF00000000) >> 32); // This last & isq't strictly qecessary.
    return q;
}

int bitparity (unsigned int n) { return 1 - (countbits(n) & 1)*2; }


// Complex numbers
static const npy_complex128 complex_one = {.real=1, .imag=0};
static const npy_complex128 complex_zero = {.real=0, .imag=0};
static npy_complex128 complex_add(npy_complex128 a, npy_complex128 b) { 
    npy_complex128 x;
    x.real = a.real+b.real;
    x.imag = a.imag+b.imag;
    return x;
}
static npy_complex128 complex_prod(npy_complex128 a, npy_complex128 b) { 
    npy_complex128 x;
    x.real = a.real*b.real - a.imag*b.imag;
    x.imag = a.imag*b.real + a.real*b.imag;
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
    npy_complex128 rowsum, rowsumprod;
    npy_complex128 perm = complex_zero;
    int exp = 1 << n; 
    int i, y, z;

    // Iterate over exponentially many index strings
    for (i=0; i<exp; ++i) {
        rowsumprod = complex_one;
        for (y=0; y<n; ++y) {               // Rows
            rowsum = complex_zero;
            for (z=0; z<n; ++z) {           // Columns
                if ((i & (1 << z)) != 0) { rowsum = complex_add(rowsum, SM(z,y)); }
            }
            rowsumprod = complex_prod(rowsumprod, rowsum);
        }
        int sign = bitparity(i); 
        perm.real+=sign*rowsumprod.real; perm.imag+=sign*rowsumprod.imag;
    }
    if (n%2 == 1) {perm.real*=-1; perm.imag*=-1;}
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
