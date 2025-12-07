#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <tuple>
#include <functional>
#include <random>
#include <type_traits>
#include <chrono>
#include <iomanip>

namespace ah {

    // --- Singleton Random Engine ---
    inline std::mt19937_64& rng() {
        static std::mt19937_64 engine(std::random_device{}());
        return engine;
    }

    // --- Generator Traits ---
    template<typename T>
    struct Generator;

    // Generator for int: default range [-100, 100]
    template<>
    struct Generator<int> {
        static int generate() {
            std::uniform_int_distribution<int> dist(-100, 100);
            return dist(rng());
        }
    };

     // Generator for long long: default range [-100, 100]
    template<>
    struct Generator<long long> {
        static long long generate() {
            std::uniform_int_distribution<long long> dist(-100, 100);
            return dist(rng());
        }
    };


    // Generator for std::string: default length [0, 10], 'a'-'z'
    template<>
    struct Generator<std::string> {
        static std::string generate() {
            std::uniform_int_distribution<int> len_dist(0, 10);
            std::uniform_int_distribution<int> char_dist('a', 'z');
            int len = len_dist(rng());
            std::string s;
            s.reserve(len);
            for(int i=0; i<len; ++i) s.push_back(static_cast<char>(char_dist(rng())));
            return s;
        }
    };

    // Generator for std::vector<T>
    template<typename T>
    struct Generator<std::vector<T>> {
        static std::vector<T> generate() {
            std::uniform_int_distribution<int> len_dist(0, 10); // default small vector
            int len = len_dist(rng());
            std::vector<T> v;
            v.reserve(len);
            for(int i=0; i<len; ++i) {
                v.push_back(Generator<T>::generate());
            }
            return v;
        }
    };

    // --- Function Traits to deduce argument types ---
    template<typename T>
    struct function_traits;

    // Specialization for function pointers
    template<typename R, typename... Args>
    struct function_traits<R(*)(Args...)> {
        using result_type = R;
        using args_tuple = std::tuple<Args...>;
    };

    // --- Harness Logic ---

    struct Stats {
        int passed = 0;
        int failed = 0;
        double total_us = 0;
    };

    template<typename T>
    void print(const T& t) {
        // Fallback print
        std::cout << "[obj]"; 
    }
    // Simple overloads for common types
    inline void print(int x) { std::cout << x; }
    inline void print(long long x) { std::cout << x; }
    inline void print(const std::string& s) { std::cout << "\"" << s << "\""; }
    template<typename T>
    void print(const std::vector<T>& v) {
        std::cout << "{";
        for(size_t i=0; i<v.size(); ++i) {
            print(v[i]);
            if(i+1 < v.size()) std::cout << ",";
        }
        std::cout << "}";
    }

    template<typename Tuple, size_t... Is>
    void print_tuple_impl(const Tuple& t, std::index_sequence<Is...>) {
        ((print(std::get<Is>(t)), std::cout << (Is + 1 == sizeof...(Is) ? "" : ", ")), ...);
    }

    template<typename... Args>
    void print_args(const std::tuple<Args...>& t) {
        std::cout << "(";
        print_tuple_impl(t, std::index_sequence_for<Args...>{});
        std::cout << ")";
    }

    // --- Detailed Implementation ---
    
    template<typename Tuple, size_t... Is>
    auto generate_tuple_impl(std::index_sequence<Is...>) {
        return std::make_tuple(Generator<std::decay_t<std::tuple_element_t<Is, Tuple>>>::generate()...);
    }

    template<typename Tuple>
    auto generate_tuple() {
        return generate_tuple_impl<Tuple>(std::make_index_sequence<std::tuple_size_v<Tuple>>{});
    }

    template<typename Func, typename Tuple>
    auto apply_func(Func f, Tuple&& args) {
        return std::apply(f, std::forward<Tuple>(args));
    }

    template<typename RefFn, typename UserFn>
    void execute(RefFn ref, UserFn user, int iterations = 1000) {
        using Traits = function_traits<RefFn>;
        using ArgsTuple = typename Traits::args_tuple; // std::tuple<Args...>
        using Result = typename Traits::result_type;

        Stats st;
        
        for(int i=1; i<=iterations; ++i) {
            auto args = generate_tuple<ArgsTuple>();
            
            // Run Reference
            Result expect = std::apply(ref, args);

            // Run User
            auto t0 = std::chrono::high_resolution_clock::now();
            Result got = std::apply(user, args);
            auto t1 = std::chrono::high_resolution_clock::now();
            
            st.total_us += std::chrono::duration<double, std::micro>(t1 - t0).count();

            if(got == expect) {
                st.passed++;
            } else {
                st.failed++;
                std::cout << "x Case #" << i << " FAILED\n";
                std::cout << "Input: ";
                print_args(args);
                std::cout << "\nExpect: ";
                print(expect);
                std::cout << "\nGot:    ";
                print(got);
                std::cout << "\n\n";
                // Optionally stop on first failure or continue? 
                // Let's continue for a bit but maybe not spam.
                if(st.failed >= 10) {
                    std::cout << "Too many failures, stopping.\n";
                    break;
                }
            }
        }

        std::cout << "\n=== Summary ===\n";
        std::cout << "Passed: " << st.passed << "/" << (st.passed + st.failed) << "\n";
        std::cout << "Failed: " << st.failed << "\n";
        double avg = (st.passed + st.failed) ? (st.total_us / (st.passed + st.failed)) : 0;
        std::cout << "Avg User Time: " << std::fixed << std::setprecision(2) << avg << " us\n";
    }

}
