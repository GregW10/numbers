#!/usr/bin/python3

import decimal
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
        # print(gcf(10238294823, 11829))
        a = decimal.Decimal(10)
        b = decimal.Decimal(7)
        decimal.getcontext().prec = 5
        print(a/b)
        sys.exit(1)
    # atexit.register(clean)
    signal.signal(signal.SIGINT, clean)
    signal.signal(signal.SIGTERM, clean)
    sys.set_int_max_str_digits(0)
    # print("2.", end="")
    num = 2
    denom = 1
    i = 2
    while True:
        # print(f"{i}\r", end="")
        denom *= i
        num *= i
        num += 1
        print(i)
        i += 1
        if bye:
            break;
        """if i % 10 == 0:
            gcf = math.gcd(num, denom)
            num //= gcf
            denom //= gcf"""
    decimal.getcontext().prec = int(math.log10(denom)) - 10
    print(f"NUMBER OF DIGITS: {decimal.getcontext().prec}")
    num = decimal.Decimal(num)
    denom = decimal.Decimal(denom)
    with open(sys.argv[1], "w") as f:
        f.write(f"{num/denom}\n")


if __name__ == "__main__":
    main()
