# coding: utf-8
__all__ = ["image_import"]

import foamutils_ext
import numpy

def image_import(filename):
    shape, flat = foamutils_ext.image_import(filename)
    image = numpy.array(flat).reshape(shape)
    return image

