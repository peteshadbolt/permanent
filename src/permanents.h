// Ryser's algorithm 
static npy_complex128 perm_ryser(PyArrayObject *submatrix) {
    int n = (int) PyArray_DIM(submatrix, 0);
    npy_complex128 rowsum, rowsumprod;
    npy_complex128 perm = complex_zero;
    int exp = 1 << n; 
    int i, y, z;
    for (i=0; i<exp; ++i) {
        rowsumprod = complex_one;
        for (y=0; y<n; ++y) {               
            rowsum = complex_zero;
            for (z=0; z<n; ++z) { 
                if ((i & (1 << z)) != 0) { complex_inc(&rowsum, SM(z, y)); }
            }
            complex_multiply(&rowsumprod, rowsum);
        }
        complex_inc(&perm, complex_float_prod(rowsumprod, bitparity(i)));
    }
    if (n%2 == 1) {perm=complex_float_prod(perm, -1);}
    return perm;
}

