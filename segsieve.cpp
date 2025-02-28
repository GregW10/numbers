#include <cinttypes>
#include <iostream>
#include <concepts>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <cmath>

uint64_t to_uint(const char *str) {
    if (!str || !*str)
        return -1;
    uint64_t num = 0;
    goto start;
    while (*str) {
        num *= 10;
        start:
        if (*str < 48 || *str > 57) {
            fprintf(stderr, "Error: non-numeric character \"%c\" found.\n", *str);
            exit(1);
        }
        num += *str++ - 48;
    }
    return num;
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: ./sieve <num_vals>\n");
        return 1;
    }
    uint64_t N = to_uint(*(argv + 1));
    uint64_t i = 3;
    double broot = sqrt((double) N);
    uint64_t broot_u = broot;
    std::vector<bool> marked((broot_u % 2 ? broot_u / 2 : broot_u / 2 - 1), false);
    uint64_t multiple;
    std::cout << "2\n"; // only even prime
    uint64_t two_i;
    uint64_t idx = 0;
    uint64_t midx;
    std::vector<uint64_t> primes;
    while (i <= broot_u) {
        multiple = i*i;
        two_i = 2*i;
        midx = multiple/2 - 1;
        while (multiple <= broot_u) {
            marked[midx] = true; // marked as composite
            multiple += two_i;
            midx += i;
        }
        std::cout << i << '\n';
        primes.push_back(i);
        i += 2;
        while (marked[++idx]) i += 2;
    }
    primes.push_back(i);
    uint64_t prev = broot_u + 1;
    uint64_t next = 2*broot_u;
    uint64_t maxw = broot_u*broot_u;
    std::vector<bool> window(broot_u, false);
    uint64_t psq;
    uint64_t diff;
    while (next <= maxw) {
        for (const auto uint64_t &prime : primes) {
            psq = prime*prime;
            i = prev + prime - (prev % prime);
            i = i > psq ? i : psq;
            diff = i - prev;
            while (i <= next) {
                
            }
        }
        i = prev;
        while (i <= next) {
            
            i += 2;
        }
        prev = next + 1;
        next += broot_u;
    }
    return 0;
}
