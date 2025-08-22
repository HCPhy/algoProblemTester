#pragma once
#include <vector>
#include <utility>

namespace app {
    using In = std::pair<std::vector<int>, int>;
    using Out = int;

    Out ref_solve(const In& in);
    Out user_solve(const In& in);
}

