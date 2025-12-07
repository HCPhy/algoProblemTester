#include "auto_harness.hpp"

// Directly include the source files. 
// This allows the compiler to see the function definitions and deduce types 
// without needing a shared header file like "def.hpp".
#include "ref_sol.cpp"
#include "user_sol.cpp"

int main() {
    // The harness automatically deduces that the input is std::vector<int>
    // and generates random vectors for testing.
    ah::execute(ref_solution, user_solution, 1000);
    return 0;
}
