#!/usr/bin/python3

import decimal
import mpmath
import atexit
import signal
import math
import time
import sys

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
    if len(sys.argv) != 2 and len(sys.argv) != 5:
        sys.exit(1)
    signal.signal(signal.SIGINT, clean)
    signal.signal(signal.SIGTERM, clean)
    sys.set_int_max_str_digits(0)
    prev_num = None
    if len(sys.argv) == 5:
        with open(sys.argv[2], "rb") as f:
            num = int.from_bytes(f.read(), byteorder="big")
        with open(sys.argv[3], "rb") as f:
            denom = int.from_bytes(f.read(), byteorder="big")
        with open(sys.argv[4], "rb") as f:
            i = int.from_bytes(f.read(), byteorder="big")
        prev_num = num
        prev_i = i
        num = 0
    else:
        num = 2
        denom = 1
        i = 2
        # loaded = False
    while True:
        denom *= i
        num *= i
        num += 1
        print(i)
        i += 1
        if bye:
            break;
    #gcd = math.gcd(num, denom)
    #num //= gcd
    #denom //= gcd
    if prev_num:
        prev_num *= math.prod(range(prev_i, i))
        num += prev_num
    with open("numerator.bin", "wb") as f:
        f.write(num.to_bytes(length=(num.bit_length() + 7)//8, byteorder="big"))
    with open("denominator.bin", "wb") as f:
        f.write(denom.to_bytes(length=(denom.bit_length() + 7)//8, byteorder="big"))
    with open("factorial.bin", "wb") as f:
        f.write(i.to_bytes(length=(i.bit_length() + 7)//8, byteorder="big"))
    # if loaded:
    #     mpmath.mp.dps = int(math.log10(math.factorial(i - 1))) - 5
    # else:
    mpmath.mp.dps = int(math.log10(denom)) - 5
    print(f"NUMBER OF DIGITS: {mpmath.mp.dps}", flush=True)
    with open(sys.argv[1], "w") as f:
        f.write(f"{mpmath.nstr(mpmath.mpf(num)/mpmath.mpf(denom), mpmath.mp.dps)}\n")

if __name__ == "__main__":
    main()
