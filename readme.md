# AlgoProblemTester

This project serves two personal goals:

1. To understand C++ basic features such as templates and type deduction.
2. To provide a test environment for algo/coding problems met during interviews or from online sources.

## Features

- **Automatic Harness**: Automatically deduces input types from your function signature and generates random test cases.
- **Legacy Harness**: Manual control over types and I/O via `def.hpp`.

## Usage

### 1. Automatic Harness (Recommended)

The new automatic harness allows you to run tests without modifying header files.

**Steps:**

1. Create a `.cpp` file (e.g., `src/my_solution.cpp`) or use `src/auto_main.cpp`.
2. Include `"auto_harness.hpp"`.
3. Define your **Reference** solution (brute force / correct implementation).
4. Define your **User** solution (optimized implementation).
5. Call `ah::execute(ref_fn, user_fn, iterations)` in `main()`.

**Example:**

```cpp
#include "auto_harness.hpp"
#include <vector>

// Reference Solution
int ref_sol(std::vector<int> nums) { ... }

// User Solution
int user_sol(std::vector<int> nums) { ... }

int main() {
    // Run 1000 random test cases
    ah::execute(ref_sol, user_sol, 1000); 
    return 0;
}
```

**Run:**

```bash
g++ -std=c++17 -I include src/auto_main.cpp -o bin/auto_main
./bin/auto_main
```

### 2. Legacy Harness

This method requires manual configuration.

1. Modify `./include/def.hpp` to define the `In` (input) and `Out` (output) data types.
2. Implement the reference solution in `./src/ref.cpp`.
3. Implement your solution in `./src/user.cpp`.
4. Add custom test cases in `./src/samples.cpp`.

## Future Work

- Add LLM API integration.
- Frontend user interface.
