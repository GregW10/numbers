#include <cinttypes>
#include <iostream>
#include <concepts>
#include <cstdint>
#include <cstdlib>
#include <vector>
#include <cmath>

uint64_t num_vals(const char *str) {
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
    uint64_t nvals = num_vals(*(argv + 1));
    // std::vector<uint64_t> nums;
    // nums.reserve(nvals);
    uint64_t i = 2;
    uint64_t biggest = nvals + 1;
    /* while (i <= biggest) {
        nums.push_back(i++);
    } */
    std::vector<bool> marked(nvals, false);
    // std::cout << std::boolalpha << marked.front() << ", " << marked.back() << std::endl;
    // uint64_t *p = nums.data();
    i = 2;
    double broot = sqrt((double) biggest);
    uint64_t multiple;
    while (i <= broot) {
        multiple = i*i;
        while (multiple <= biggest) {
            marked[multiple - 2] = true; // marked as composite
            multiple += i;
        }
        std::cout << i << '\n';// printf("%" PRIu64 "\n", i);
        while (marked[++i - 2]);
    }
    while (i <= biggest) {
        if (!marked[i - 2])
            std::cout << i << '\n';// printf("%" PRIu64 "\n", nums[i]);
        ++i;
    }
    /* do {
        printf("%" PRIu64 "\n", i);
    } while (marked[++i - 2]); */
    return 0;
}
