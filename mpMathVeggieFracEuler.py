#!/usr/bin/python3

import fractions
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
    prev_sum = None
    if len(sys.argv) == 5:
        with open(sys.argv[2], "rb") as f:
            num = int.from_bytes(f.read(), byteorder="big")
        with open(sys.argv[3], "rb") as f:
            denom = int.from_bytes(f.read(), byteorder="big")
        with open(sys.argv[4], "rb") as f:
            i = int.from_bytes(f.read(), byteorder="big")
        prev_sum = fractions.Fraction(numerator=num, denominator=denom)
        num = 0
    else:
        num = 2
        denom = 1
        i = 2
    partial_sum = fractions.Fraction(numerator=num, denominator=denom)
    fac = math.factorial(i)
    while True:
        partial_sum += fractions.Fraction(numerator=1, denominator=fac)
        print(i)
        # print(partial_sum)
        i += 1
        fac *= i
        if bye:
            break;
    if prev_sum:
        partial_sum += prev_sum
    with open("numerator.bin", "wb") as f:
        f.write(partial_sum.numerator.to_bytes(length=(partial_sum.numerator.bit_length() + 7)//8, byteorder="big"))
    with open("denominator.bin", "wb") as f:
        f.write(partial_sum.denominator.to_bytes(length=(partial_sum.denominator.bit_length() + 7)//8, byteorder="big"))
    with open("factorial.bin", "wb") as f:
        f.write(i.to_bytes(length=(i.bit_length() + 7)//8, byteorder="big"))
    mpmath.mp.dps = int(math.log10(partial_sum.denominator)) - 5
    print(f"NUMBER OF DIGITS: {mpmath.mp.dps}", flush=True)
    with open(sys.argv[1], "w") as f:
        f.write(f"{mpmath.nstr(mpmath.mpf(partial_sum.numerator)/mpmath.mpf(partial_sum.denominator), mpmath.mp.dps)}\n")

if __name__ == "__main__":
    main()
