#include "auto_harness.hpp"
#include <vector>
#include <algorithm>
#include <iostream>

// --- Reference Solution ---
// Example: Maximum subarray sum (simplistic O(N^2) ref)
long long max_subarray_ref(std::vector<int> nums) {
    long long max_so_far = -1e18;
    for(size_t i=0; i<nums.size(); ++i) {
        long long current_sum = 0;
        for(size_t j=i; j<nums.size(); ++j) {
            current_sum += nums[j];
            max_so_far = std::max(max_so_far, current_sum);
        }
    }
    // Handle empty case or return 0 if preferred, but let's stick to this
    if(nums.empty()) return 0;
    return max_so_far;
}

// --- User Solution ---
// Optimized O(N) Kadane's Algorithm
long long max_subarray_user(std::vector<int> nums) {
    long long max_so_far = -1e18;
    long long current_max = 0;
    
    if(nums.empty()) return 0;

    max_so_far = nums[0];
    current_max = nums[0];

    for(size_t i=1; i<nums.size(); ++i) {
        current_max = std::max((long long)nums[i], current_max + nums[i]);
        max_so_far = std::max(max_so_far, current_max);
    }
    return max_so_far;
}


int main() {
    // Example 1: Vector input
    std::cout << "Testing Max Subarray Problem:\n";
    ah::execute(max_subarray_ref, max_subarray_user, 500);

    return 0;
}
