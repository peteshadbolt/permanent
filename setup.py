#!/usr/bin/env python

from distutils.core import setup, Extension
import numpy

setup(
    name="permanent",
    version="0.1.3",
    description="Calculates the permanent of a Numpy matrix",
    author="Pete Shadbolt",
    author_email="hello@peteshadbolt.co.uk",
    maintainer="hello@peteshadbolt.co.uk",
    url="https://github.com/peteshadbolt/permanent",
    packages=["permanent"],
    setup_requires=["numpy"],
    ext_modules=[
        Extension(
            'permanent.permanent', ['./src/permanent.c'],
            extra_compile_args=["-Ofast", "-march=native"],
            include_dirs=[numpy.get_include()]),
    ],
)
