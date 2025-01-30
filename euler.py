#!/usr/bin/python3

import atexit
import signal
import math
import time
import sys

def clean(_sig, _f):
    print("\n", end="", flush=True)
    sys.exit(0)


def main():
    # atexit.register(clean)
    signal.signal(signal.SIGTERM, clean)
    sys.set_int_max_str_digits(0)
    print("2.", end="")
    a_num = 1;
    a_den = 1;
    c_num = 0;
    c_den = 1;
    cc_num = 0;
    cc_den = 1;
    i = 1;
    digit = 0;
    entered = False;
    prec = 1_000_000_000_000
    while True:
        cc_num = 0;
        cc_den = 1;
        entered = False
        dib = 0
        diby = 1
        while a_num*prec > a_den:
            i += 1
            if i % 10 == 0:
                dib += 10
                diby *= dib
            a_den *= i;
            cc_num *= i;
            cc_num += a_num;
            cc_den = a_den;
            entered = True;
        if entered:
            c_num *= cc_den//c_den
            c_den = cc_den;
            c_num += cc_num;
        if dib and a_num >= 10:
            # print("\n"); print(cc_num, cc_den, c_num, c_den, a_num, a_den, file=sys.stderr); print("\n")
            #sys.exit(1)
            if a_num % diby != 0:
                diby = a_num
            c_num //= diby
            c_den //= diby
            a_num //= diby
            a_den //= diby
        g = c_num*10
        digit = g//c_den
        c_num = g % c_den;
        # print(c_num, c_den, cc_num, cc_den, a_num, a_den)
        print(digit, end="") #, flush=True)
        a_num *= 10;
        # time.sleep(1);


if __name__ == "__main__":
    main()
