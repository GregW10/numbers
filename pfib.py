#!/usr/bin/python3

import sys
import mpmath


def main():
    sys.set_int_max_str_digits(0)
    i = 2
    j = 3
    print("2\n3")
    primes = [2, 3]
    root = None
    while True:
        k = j
        j += i
        i = k
        if j % 2 != 0:
            if j % 3 != 0:
                root = mpmath.sqrt(mpmath.mpf(j))
                z = 1
                y = 6*z + 1
                x = 6*z + 5
                isprime = True
                while x <= root:
                    if j % x == 0 or j % y == 0:
                        isprime = False
                        break;
                    z += 1
                    y = 6*z + 1
                    x = 6*z + 5
                if isprime:
                    print(j)


if __name__ == "__main__":
    main()

