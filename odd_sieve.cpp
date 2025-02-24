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
    uint64_t biggest = to_uint(*(argv + 1));
    // std::vector<uint64_t> nums;
    // nums.reserve(nvals);
    uint64_t i;
    /* while (i <= biggest) {
        nums.push_back(i++);
    } */
    // uint64_t nvals = biggest % 2 ? biggest / 2 : biggest / 2 - 1;
    std::vector<bool> marked((biggest % 2 ? biggest / 2 : biggest / 2 - 1), false);
    // std::cout << std::boolalpha << marked.front() << ", " << marked.back() << std::endl;
    // uint64_t *p = nums.data();
    i = 3;
    double broot = sqrt((double) biggest);
    uint64_t multiple;
    std::cout << "2\n"; // only even prime
    uint64_t two_i;
    uint64_t idx = 0;
    uint64_t midx;
    while (i <= broot) {
        multiple = i*i;
        two_i = 2*i;
        midx = multiple/2 - 1;
        while (multiple <= biggest) {
            marked[/*multiple/2 - 1*/ midx] = true; // marked as composite
            multiple += two_i;
            midx += i;
        }
        std::cout << i << '\n';// printf("%" PRIu64 "\n", i);
        i += 2;
        while (marked[/*(i += 2)/2 - 1*/++idx]) i += 2;
    }
    while (i <= biggest) {
        if (!marked[idx++])
            std::cout << i << '\n';// printf("%" PRIu64 "\n", nums[i]);
        i += 2;
    }
    /* do {
        printf("%" PRIu64 "\n", i);
    } while (marked[++i - 2]); */
    return 0;
}
