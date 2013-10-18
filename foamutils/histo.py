#!/usr/bin/env python2
# coding: utf-8

import sys
from pylab import *
import libfoamutils

filename = sys.argv[1]

shape, flat = libfoamutils.image_import(filename)
image = array(flat).reshape(shape)

figure()
xlabel("x")
ylabel("y")
imshow(image[:,:,int(shape[2]/2)])

figure()
imshow(image[:,int(shape[1]/2),:])
xlabel("x")
ylabel("z")

figure()
imshow(image[int(shape[0]/2),:,:])
xlabel("x")
ylabel("z")

figure()
hist(flat,bins=64)

show()
