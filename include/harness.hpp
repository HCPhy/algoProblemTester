#pragma once
#include <chrono>
#include <functional>
#include <iostream>
#include <string>
#include <type_traits>
#include "def.hpp"
#include "print.hpp"

namespace app{
    struct Stats {
        int passed = 0, failed = 0; 
        double us_total = 0;
    };

    template<typename T>
    inline bool eq(const T& a, const T& b){
        return a == b;
    }

    template<typename InT, typename OutT, typename UserFn>
    inline void run_case(const std::string& name, 
         const InT& input, const OutT& expect, UserFn user_fn, Stats& st){

        auto t0 = std::chrono::high_resolution_clock::now();
        OutT got = std::invoke(user_fn, input);
        auto t1 = std::chrono::high_resolution_clock::now();
        st.us_total += std::chrono::duration<double, std::micro> (t1 - t0).count();

        if(eq(got, expect)){
            ++st.passed;
        }else{
            ++st.failed;
            std::cerr << "x "<< name << " failed\n"
            << " input : " << input << "\n"
            << " expect: " << expect<< "\n"
            << " got   : " << got << "\n";
        }
    }

    template<typename RefFn, typename UserFn, typename GenFn>
    inline void fuzz(const std:: string& tag, int N, 
    RefFn ref_fn, UserFn user_fn, GenFn gen_fn, Stats& st){
        using InT = std::invoke_result_t<GenFn&>;
        using OutRef = std::invoke_result_t<RefFn&, const InT&>;
        using OutUser= std::invoke_result_t<UserFn&, const InT&>;

        static_assert(std::is_same_v<OutRef, OutUser>, "ref_fn and user_fn must have the same type ");
        
        for(int i = 1; i <= N; ++i){
            InT in = std::invoke(gen_fn);
            OutRef expect = std::invoke(ref_fn, in);
            run_case(tag + '#' + std::to_string(i), in, expect, user_fn, st);
        }
    }

}