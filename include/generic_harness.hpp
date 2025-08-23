#pragma once
#include <chrono>
#include <functional>
#include <iostream>
#include <optional>
#include <string>
#include <tuple>
#include <type_traits>
#include <utility>
#include <vector>

namespace th{
    // tuple-like type detection, invoke if tuple like, apply if non-tuple

    template<typename T, typename = void>
    struct is_tuple_like : std::false_type{};

    template<typename T>
    struct is_tuple_like<T, std::void_t<decltype(std::tuple_size<std::decay_t<T>>::value)>>: std::true_type {};

    template<typename Fn, typename In>
    decltype(auto) invoke_with(Fn&& fn, In&& in){
        if constexpr (is_tuple_like<std::decay_t<In>>::value){
            return std::apply(std::forward<Fn>(fn), std::forward<In>(in));
        }else{
            return std::invoke(std::forward<Fn>(fn), std::forward<In>(in))
        }
    }

    // 




    

}

