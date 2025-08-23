#include "def.hpp"
#include <iostream>
#include <deque>

namespace app {

Out user_solve(const In& in){

    const auto& a = in.first;
    int limit = in.second;

    std::deque<int> maxq, minq;
    int L = 0, best{};

    for(int R = 0; R < int(a.size()); ++R){
        while (!maxq.empty() and a[maxq.back()] < a[R]){
            maxq.pop_back();
        }
        maxq.push_back(R);

        while(!minq.empty() and a[minq.back()] > a[R]){
            minq.pop_back();
        }
        minq.push_back(R);

        while(!maxq.empty() and !minq.empty() and a[maxq.front()] - a[minq.front()] > limit){

            if(maxq.front() == L) maxq.pop_front();
            if(minq.front() == L) minq.pop_front();

            ++L;
        }

        best = std::max(best, R - L + 1);


    }


    
    return best;

    // return ref_solve(in);
}

}