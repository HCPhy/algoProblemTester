#pragma once
#include <ostream>
#include <vector>
#include <utility>
#include "def.hpp"

template<typename T>
inline std::ostream& operator << (std::ostream& os, const std::vector<T>& v){
    os << '[';
    for(size_t i = 0; i < v.size(); ++i){
        if(i) os << ',';
        os << v[i];
    }
    os << ']';

    return os;
}

template<typename A, typename B>
inline std::ostream operator << (std::ostream& os, const std::pair<A, B>& p){
    return os << '( ' << p.first << ', ' << p.second << ')';
}


namespace app {
inline std::ostream& operator<<(std::ostream& os, const In& in){
    return os << '(' << in.first << ',' << in.second << ')';
}
} 