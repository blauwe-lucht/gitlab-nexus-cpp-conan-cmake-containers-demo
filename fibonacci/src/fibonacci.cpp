#include "fibonacci.hpp"
#include <stdexcept>

int Fibonacci::compute(int n) const {
    if (n < 0) {
        throw std::invalid_argument("Negative input not allowed");
    }

    if (n <= 1)
    {
        return n;
    }
    
    return compute(n - 1) + compute(n - 2);
}
