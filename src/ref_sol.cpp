#include <vector>
#include <algorithm>

// No "def.hpp" needed. Just standard C++.
// Function name should be consistent or mapped in the runner.
inline int ref_solution(std::vector<int> v) {
    if (v.empty()) return 0;
    int max_val = -1e9;
    for(int x : v) max_val = std::max(max_val, x);
    return max_val;
}
