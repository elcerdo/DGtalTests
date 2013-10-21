#!/usr/bin/env python2
# coding: utf-8

from distutils.core import setup, Extension
import os

module1 = Extension(name = 'foamutils_ext',
                    sources = ['foamutils_ext.cpp'],
                    include_dirs = [os.path.join(os.environ["DGtal"],"install/include")],
                    library_dirs = [os.path.join(os.environ["DGtal"],"install/lib")],
                    libraries = ['boost_python','DGtal'])

setup (name = 'foamutils',
       version = '1.0',
       description = 'Foam project utils',
       py_modules  = ["foamutils"],
       ext_modules = [module1])


