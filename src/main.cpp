#include <iomanip>
#include <iostream>
#include "def.hpp"
#include "harness.hpp"

namespace app{
    std::vector<std::pair<In, Out>> samples();
    In random_case();
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    app::Stats st;

    for(auto& [in, expect]: app::samples()){
        run_case("sample", in, expect, app::user_solve, st);
    }

    const int FUZZ = 3000;
    app::fuzz("fuzz", FUZZ, app::ref_solve, app::user_solve, app::random_case, st);

    int total = st.passed + st.failed;

    std::cout << "\n================ Summary ================\n";
    std::cout << "Passed: " << st.passed << "/" << total << "\n";
    std::cout << "Failed: " << st.failed << "\n";
    std::cout << "Avg runtime (user) per case: "
              << std::fixed << std::setprecision(2)
              << (total ? st.us_total/total : 0.0) << " us\n";
    std::cout << "=========================================\n";
    return (st.failed==0)? 0 : 1;

}