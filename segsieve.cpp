#include <algorithm>
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
    if (N < 2)
        return 0;
    if (N == 2) {
        std::cout << "2\n";
        return 0;
    }
    if (N == 3) {
        std::cout << "2\n3\n";
        return 0;
    }
    uint64_t i = 3;
    double broot = sqrt((double) N);
    uint64_t broot_u = broot;
    broot_u += broot_u % 2; // made sure the root-value is even as this avoids having to switch between odd/even sizes of "marked" in the loop
    uint64_t size = broot_u/2;//broot_u % 2 ? broot_u / 2 : broot_u / 2 - 1;
    std::vector<bool> marked(size, false);
    uint64_t multiple;
    std::cout << "2\n"; // only even prime
    uint64_t two_i;
    uint64_t idx = 0;
    uint64_t midx;
    std::vector<uint64_t> primes;
    // std::cout << "broot: " << broot << ", broot_u: " << broot_u << ", marked.size(): " << marked.size() << std::endl;
    do {
        multiple = i*i;
        two_i = i << 1;
        midx = multiple/2 - 1;
        while (multiple <= broot_u) {
            marked[midx] = true; // marked as composite
            multiple += two_i;
            midx += i;
        }
        std::cout << i << '\n';
        primes.push_back(i);
        i += 2;
        while (++idx < size && marked[idx]) i += 2;
    } while (i <= broot_u);
    // primes.push_back(i);
    uint64_t prev = broot_u + 1;
    uint64_t next = broot_u << 1;
    uint64_t maxw = broot_u*broot_u;
    maxw = maxw < N ? maxw : N;
    // std::vector<bool> window(broot_u);
    // uint64_t psq;
    // uint64_t diff;
    uint64_t p2;
    // for (const auto &prime : primes)
        // std::cout << "prime: " << prime << std::endl;
    uint64_t rem;
    // std::cout << "marked.size(): " << marked.size() << std::endl;
    while (next <= maxw) {
        idx = 0;
        while (idx < size) {
            marked[idx++] = false;
        }
        for (const uint64_t &prime : primes) {
            i = prev + ((rem = prev % prime) ? prime - rem : 0);
            if (!(i % 2))
                i += prime;
            idx = (i - prev)/2;
            p2 = prime << 1;
            while (i <= next) {
                /* if (idx == 49)
                    std::cout << "Yes! idx: " << idx << ", i: " << i << ", prime: " << prime << std::endl; */
                marked[idx] = true;
                idx += prime;
                i += p2;
            }
        }
        i = prev + 1 - (prev % 2);
        std::for_each(marked.begin(), marked.end(), [&i](bool b){if (!b) std::cout << i << '\n'; i += 2;});
        /* for (bool b : marked) {
            std::cout << std::boolalpha << "b: " << b << ", i: " << i << std::endl;
            i += 2;
        } */
        prev = next + 1;
        next += broot_u;
    }
    if (prev > N)
        return 0;
    uint64_t left = N - prev;
    left = left/2 + ((prev % 2) || (N % 2));
    // std::cout << "left: " << left << ", N: " << N << ", prev: " << prev << std::endl;
    if (left) {
        marked.resize(left);
        idx = left;
        while (idx --> 0)
            marked[idx] = false;
        for (const uint64_t &prime : primes) {
            i = prev + ((rem = prev % prime) ? prime - rem : 0);
            if (!(i % 2))
                i += prime;
            idx = (i - prev)/2;
            p2 = prime << 1;
            while (i <= N) {
                marked[idx] = true;
                idx += prime;
                i += p2;
            }
        }
        i = prev % 2 ? prev : prev + 1;
        std::for_each(marked.begin(), marked.end(), [&i](bool b){if (!b) std::cout << i << '\n'; i += 2;});
    }
    return 0;
}
