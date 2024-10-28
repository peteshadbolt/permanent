#!/usr/bin/env python3

from distutils.core import setup, Extension
import numpy

setup(
    ext_modules=[
        Extension(
            'permanentbis.permanent', ['./src/permanent.c'],
            extra_compile_args=["-Ofast", "-march=native"],
            include_dirs=[numpy.get_include()]),
    ],
)
