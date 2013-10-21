#!/usr/bin/env python2
# coding: utf-8

from distutils.core import setup, Extension
import os

dgtal_dir = os.environ.get("DGtal","~/git/DGtal")
dgtal_dir = os.path.expanduser(dgtal_dir)

module1 = Extension(name = 'foamutils_ext',
                    sources = ['foamutils_ext.cpp'],
                    include_dirs = [os.path.join(dgtal_dir,"install/include")],
                    library_dirs = [os.path.join(dgtal_dir,"install/lib")],
                    libraries = ['boost_python','DGtal'])

setup (name = 'foamutils',
       version = '1.0',
       description = 'Foam project utils',
       py_modules  = ["foamutils"],
       ext_modules = [module1])


