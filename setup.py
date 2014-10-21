#!/usr/bin/env python

from distutils.core import setup, Extension

setup(name             = "loqcmath",
      version          = "1.0",
      description      = "Fast maths for LOQC",
      author           = "Pete Shadbolt",
      author_email     = "pete.shadbolt@gmail.com",
      maintainer       = "pete.shadbolt@gmail.com",
      url              = "https://www.peteshadbolt.co.uk",
      ext_modules      = [
          Extension(
              'permanent', ['src/permanent.c'],
              extra_compile_args=["-Ofast", "-march=native"]),
      ], 
      
)
