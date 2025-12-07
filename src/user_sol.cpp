#include <vector>
#include <algorithm>

// User solution with concrete types.
inline int user_solution(std::vector<int> v) {
    if (v.empty()) return 0;
    // Just a dummy implementation (max element)
    int m = -1e9;
    for(auto x : v) {
        if(x > m) m = x;
    }
    return m;
}
