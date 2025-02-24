#!/usr/bin/python3

import sys
import signal


bye = False


def leave(_sig, _f):
    global bye
    bye = True


def main():
    sl = len(sys.argv)
    if sl > 3 or sl == 1:
        sys.exit(1)
    signal.signal(signal.SIGINT, leave)
    signal.signal(signal.SIGTERM, leave)
    N = int(sys.argv[1])
    if N < 2:
        sys.exit(1)
    sys.set_int_max_str_digits(0)
    i = 0
    j = 1
    n = 1
    if sl == 3:
        f = sys.stdout.buffer
    else:
        f = open("fibs.bin", "wb")
    f.write((1).to_bytes(length=4, byteorder="big"))
    f.write(i.to_bytes(length=1, byteorder="big"))
    l = (j.bit_length() + 7)//8
    f.write(l.to_bytes(length=4, byteorder="big"))
    f.write(j.to_bytes(length=l, byteorder="big"))
    max_l = 2**32 - 1
    while n < N:
        k = j
        j += i
        i = k
        l = (j.bit_length() + 7)//8
        if l > max_l:
            break;
        f.write(l.to_bytes(length=4, byteorder="big"))
        f.write(j.to_bytes(length=l, byteorder="big"))
        n += 1
        print(n, file=sys.stderr)
        if bye:
            break;
    if sl != 3:
        f.close()

if __name__ == "__main__":
    main()

