#!/bin/bash

rm permanent/*.so
python ./setup.py build_ext --inplace &&
python ./run-tests.py
