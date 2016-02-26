# Overview

This is an example Python 3 extension module written in C++14. The [source file](source/dummy.cpp)
for the extension module defines the following functions:

- `make_message`: Returns a string containing a message.
- `reverse`: Reverses a given string (assuming that each visible character is one code point). Also
  demonstrates how to pass exceptions to Python.

# Installation

Run the following commands:

	rake
	pip install .
