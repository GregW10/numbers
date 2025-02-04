#!/usr/bin/python3


import mpmath as mp

mp.dps = 90

a = mp.mpf(10)
b = mp.mpf(7)
c = a/b

mp.nprint(c, mp.dps)
