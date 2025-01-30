#include <iostream>
#include <cstdint>
#include <cinttypes>
#include <unistd.h>


int main() {

    std::cout << "2.";
    std::cerr << "2.: 1" << std::endl;

    uint64_t a_num = 1;
    uint64_t a_den = 2;

    uint64_t c_num = 0;
    uint64_t c_den = 1;

    uint64_t cc_num = 0;
    uint64_t cc_den = 1;

    uint64_t i = 2;

    uint64_t digit;

    // uint64_t rem;

    goto start;

    bool entered;

    while (true) {
        // c_num *= (cc_den / c_den);
        // c_num = rem;
        // c_den = cc_den;
        // std::cout << "\n" << c_num << "/" << c_den << std::endl;
        start:
        cc_num = 0;
        cc_den = 1;
        entered = false;

        uint64_t dsupp = 0;
        while (a_num*1'000'000'000 > a_den) {
            cc_num *= i;
            cc_num += a_num;
            cc_den = a_den;
            a_den *= ++i;
            // std::cout << "\nyes\n";
            entered = true;
        }
        // if (!entered)
            std::cerr << "\n----------\na_num: " << a_num << ", a_den: " << a_den << std::endl;
        if (entered) {
            c_num *= (cc_den/c_den);
            c_den = cc_den;
            c_num += cc_num;
        }
        // if (!entered)
            std::cerr << "cc_num: " << cc_num << ", cc_den: " << cc_den << ", c_num: " << c_num << ", c_den: " << c_den << std::endl;
        digit = (c_num*10)/c_den + dsupp;
        c_num = (c_num*10) % c_den;
        std::cout << digit << std::flush;
        std::cerr << digit << ": " << a_den << std::boolalpha << " (entered: " << entered << ")\n----------\n" << std::endl;
        a_num *= 10;
        sleep(1);
    }
    std::cout << std::endl;
    return 0;
}
