#include <math.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <signal.h>
#include <unistd.h>
#include <sys/stat.h>
#include <inttypes.h>

#define MAX_PRIMES 1000000000

uint64_t *primes = NULL;

int leave = 0;

void interrupted(int) {
    leave = 1;
}

/* uint64_t gcf(uint64_t x, uint64_t y) {
    uint64_t r;
    goto begin;
    do {
        x = y;
        y = r;
        begin:
        r = x % y;
    } while (r);
    return y;
} */

int main(int argc, char **argv) {
    // printf("%" PRIu64 "\n", gcf(42, 18));
    // return 1;
    primes = malloc(sizeof(uint64_t)*MAX_PRIMES);
    if (!primes) {
        fprintf(stderr, "malloc() error.\n");
        return 1;
    }
    signal(SIGINT, interrupted);
    signal(SIGTERM, interrupted);
    *primes = 2;
    *(primes + 1) = 3;
    *(primes + 2) = 5;
    printf("2\n3\n5\n");
    uint64_t i = 7;
    int isprime;
    double root;
    uint64_t *ptr;
    uint64_t *last = primes + 2;
    uint64_t counter = MAX_PRIMES - 3;
    uint64_t *const asof5 = primes + 2;
    while (counter > 0) {
        if (!(i % 2)) {
            ++i;
            continue;
        }
        if (!(i % 3)) {
            ++i;
            continue;
        }
        // j = 1;
        ptr = asof5;
        isprime = 1;
        root = sqrt((double) i);
        while (*ptr <= root) {
            if (!(i % *ptr)) {
                isprime = 0;
                break;
            }
            ++ptr;
        }
        if (isprime) {
            *++last = i;
            printf("%" PRIu64 "\n", i);
            --counter;
        }
        if (leave)
            break;
        ++i;
    }
    int fd = open("primes.bin", O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (fd == -1) {
        free(primes);
        return 2;
    }
    ssize_t rem = (last - primes + 1)*sizeof(uint64_t);
    ssize_t written;
    char *p = (char*) primes;
    do {
        if ((written = write(fd, p, rem)) == -1) {
            close(fd);
            free(primes);
            return 3;
        }
        rem -= written;
        p += written;
    } while (rem);
    free(primes);
    return 0;
}
