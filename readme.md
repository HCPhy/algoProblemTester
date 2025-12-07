# AlgoProblemTester

This project serves two personal goals:

1. To understand C++ basic features such as templates and type deduction.
2. To provide a test environment for algo/coding problems met during interviews or from online sources.

## Features

- **Automatic Harness**: Automatically deduces input types from your function signature and generates random test cases.
- **Zero Configuration**: No common header file (`def.hpp`) required. Just include your solution files in the runner.

## Usage (Recommended)

This method allows you to separate your code into files without maintaining a shared header file.

**1. Create Solution Files**

Write your Reference and User solutions in separate files. Use concrete types (e.g., `std::vector<int>`).

`src/ref_sol.cpp`:

```cpp
#include <vector>
#include <algorithm>

int ref_sol(std::vector<int> v) { ... }
```

`src/user_sol.cpp`:

```cpp
#include <vector>
#include <algorithm>

int user_sol(std::vector<int> v) { ... }
```

**2. Create a Runner**

Create a `src/test_runner.cpp` that includes your solution files.

```cpp
#include "auto_harness.hpp"
// Include your solution files directly
#include "ref_sol.cpp"
#include "user_sol.cpp"

int main() {
    // The harness deduces int(vector<int>) and tests automatically
    ah::execute(ref_sol, user_sol, 1000); 
    return 0;
}
```

**3. Run**

```bash
g++ -std=c++17 -I include src/test_runner.cpp -o bin/test_runner
./bin/test_runner
```

### Legacy Method

If you prefer the old way with `def.hpp`, you can still use `src/main.cpp` and configure types manually in `include/def.hpp`.
