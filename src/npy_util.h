// Array access macros.
#define SM(x0, x1) (*(npy_complex128*)(((char*)PyArray_DATA(submatrix) + \
                    (x0) * PyArray_STRIDES(submatrix)[0] +  \
                    (x1) * PyArray_STRIDES(submatrix)[1])))
#define SM_shape(x0) (int) PyArray_DIM(submatrix, x0)

// Complex numbers
static const npy_complex128 complex_one = 1 + 0 * I;
static const npy_complex128 complex_zero = 0 + 0 * I;

// Add two numbers
npy_complex128 complex_add(npy_complex128 a, npy_complex128 b) { 
    return a+b;
}

// Product of two numbers
npy_complex128 complex_prod(npy_complex128 a, npy_complex128 b) { 
    return a*b;
}

// Product of complex and float
npy_complex128 complex_float_prod(npy_complex128 a, float b) { 
    return a*b;
}

// Increment a number
void complex_inc(npy_complex128 *a, npy_complex128 b) { 
    *a += b;
}

// Multipy a number by another one
void complex_multiply(npy_complex128 *a, npy_complex128 b) { 
    *a *= b;
}

