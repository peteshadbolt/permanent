// Array access macros.
#define SM(x0, x1) (*(npy_complex128*)((PyArray_DATA(submatrix) + \
                    (x0) * PyArray_STRIDES(submatrix)[0] +  \
                    (x1) * PyArray_STRIDES(submatrix)[1])))
#define SM_shape(x0) (int) PyArray_DIM(submatrix, x0)

// Complex numbers
static const npy_complex128 complex_one = {.real=1, .imag=0};
static const npy_complex128 complex_zero = {.real=0, .imag=0};

// Add two numbers
npy_complex128 complex_add(npy_complex128 a, npy_complex128 b) { 
    npy_complex128 x;
    x.real = a.real+b.real;
    x.imag = a.imag+b.real;
    return x;
}

// Product of two numbers
npy_complex128 complex_prod(npy_complex128 a, npy_complex128 b) { 
    npy_complex128 x;
    x.real = a.real*b.real - a.imag*b.imag;
    x.imag = a.imag*b.real + a.real*b.imag;
    return x;
}

// Product of complex and float
npy_complex128 complex_float_prod(npy_complex128 a, float b) { 
    npy_complex128 x;
    x.real = a.real*b;
    x.imag = a.imag*b;
    return x;
}

// Increment a number
void complex_inc(npy_complex128 *a, npy_complex128 b) { 
    a->real += b.real;
    a->imag += b.imag;
}

// Multipy a number by another one
void complex_multiply(npy_complex128 *a, npy_complex128 b) { 
    double c = a->real;
    a->real  = a->real*b.real-a->imag*b.imag;
    a->imag  = c*b.imag+a->imag*b.real;
}

