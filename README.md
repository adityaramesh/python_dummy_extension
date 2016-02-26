# Overview

This is an example Python 3 extension module written in C++14. The [source file](source/dummy.cpp)
for the extension module defines the following functions:

- `make_message`: Returns a string containing a message.
- `reverse`: Reverses a given string (assuming that each visible character is one code point). Also
  demonstrates how to pass exceptions to Python.

# Installation

First, define the following environment variables:

- `CXX`: Path to a version of g++ or clang++ that is C++14-compliant.
- `PYTHON_INCLUDE_PATH`: Path to the include directory of the active Python installation.

Then run the following commands:

	rake
	pip install .
