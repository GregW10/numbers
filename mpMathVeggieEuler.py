#!/usr/bin/python3

import decimal
import mpmath
import atexit
import signal
import math
import time
import sys

num = 0
denom = 1

bye = False

def clean(_sig, _f):
    global bye
    bye = True


def gcf(num: int, denom: int):
    rem = num % denom
    while rem:
        num = denom
        denom = rem
        rem = num % denom
    return denom


def main():
    if len(sys.argv) != 2:
        sys.exit(1)
    signal.signal(signal.SIGINT, clean)
    signal.signal(signal.SIGTERM, clean)
    sys.set_int_max_str_digits(0)
    num = 2
    denom = 1
    i = 2
    while True:
        denom *= i
        num *= i
        num += 1
        print(i)
        i += 1
        if bye:
            break;
    mpmath.mp.dps = int(math.log10(denom)) - 10
    print(f"NUMBER OF DIGITS: {mpmath.mp.dps}")
    with open(sys.argv[1], "w") as f:
        f.write(f"{mpmath.nstr(mpmath.mpf(num)/mpmath.mpf(denom), mpmath.mp.dps)}\n")

if __name__ == "__main__":
    main()
