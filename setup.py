from distutils.core import setup

setup(
	name         = 'dummy',
	version      = '0.1',
	description  = 'An example Python extension module written in C++.',
	url          = 'https://github.com/adityaramesh/python_dummy_extension',
	author       = 'Aditya Ramesh',
	author_email = '_@adityaramesh.com',
	license      = 'BSD',
	packages     = ['dummy'],
	package_data = {'dummy': ['_dummy.so']}
)
