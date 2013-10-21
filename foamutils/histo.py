#!/usr/bin/env python2
# coding: utf-8

import sys
from pylab import *
import foamutils

filename = sys.argv[1]

image = foamutils.image_import(filename)

figure()
xlabel("x")
ylabel("y")
imshow(image[:,:,int(image.shape[2]/2)])

figure()
imshow(image[:,int(image.shape[1]/2),:])
xlabel("x")
ylabel("z")

figure()
imshow(image[int(image.shape[0]/2),:,:])
xlabel("x")
ylabel("z")

figure()
hist(image.ravel(),bins=64)

show()
