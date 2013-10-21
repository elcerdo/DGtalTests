#!/usr/bin/env python2
# coding: utf-8

import sys
from pylab import *
import foamutils

input_filename = sys.argv[1]
output_filename = sys.argv[2]

image = foamutils.image_import(input_filename)
print image.shape
image = image[32:96,:64,32:96]
#image = image>60
print image.shape
foamutils.image_export(image,output_filename)

show()
