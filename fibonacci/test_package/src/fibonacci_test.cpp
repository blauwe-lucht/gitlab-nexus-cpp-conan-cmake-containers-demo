#include "fibonacci.hpp"
#include <iostream>

int main() {
    Fibonacci fib;
    int n = 10;
    int result = fib.compute(n);
    std::cout << "Fibonacci of " << n << " is " << result << std::endl;
    return 0;
}
