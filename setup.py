#!/usr/bin/env python

from distutils.core import setup, Extension

setup(name             = "permanent",
      version          = "0.1.2",
      description      = "Calculates the permanent of a Numpy matrix",
      author           = "Pete Shadbolt",
      author_email     = "pete.shadbolt@gmail.com",
      maintainer       = "pete.shadbolt@gmail.com",
      url              = "https://github.com/peteshadbolt/permanent",
      packages         = ["permanent"],
      ext_modules      = [
          Extension(
              'permanent.permanent', ['./src/permanent.c'],
              extra_compile_args=["-Ofast", "-march=native"]),
      ], 
      
)
