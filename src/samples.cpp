#include "def.hpp"
#include <random>
#include <vector>

namespace app{
    std::vector<std::pair<In, Out>> samples(){
        return {
            {{ {1,4,9,5,8} , 4}, 3},
            {{ {1}, 10}, 1},
            {{ {1,2,6,7,9,3,3,3,3}, 0}, 4},
            {{ {8,2,4,7}, 4}, 2},
        };
    }

    In random_case(){
        static std::mt19937_64 rng(12039);
        std::uniform_int_distribution<int> N(0, 60);
        std::uniform_int_distribution<int> V(-20, 20);

        int n = N(rng);
        std::vector<int> a(n);
        for(int i = 0; i < n; ++i){
            a[i] = V(rng);
        }

        int limit = std::uniform_int_distribution(0, 25)(rng);

        return {a, limit};
    }
}