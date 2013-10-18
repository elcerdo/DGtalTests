#!/usr/bin/env python2
# coding: utf-8

from pylab import *
import libfoamutils

shape, flat = libfoamutils.generic_import("../../mousse.vol")
image = array(flat).reshape(shape)

figure()
imshow(image[:,:,int(shape[2]/2)])
figure()
imshow(image[:,int(shape[1]/2),:])
figure()
imshow(image[int(shape[0]/2),:,:])
show()
