# coding: utf-8
__all__ = ["image_import","image_export"]

import foamutils_ext
import numpy

def image_import(filename):
    shape, flat = foamutils_ext.image_import(filename)
    image = numpy.array(flat).reshape(shape)
    return image

def image_export(image,filename):
    flat = image.astype("int").ravel().tolist()
    shape = image.shape
    foamutils_ext.image_export(shape,flat,filename)

