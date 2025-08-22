#include "def.hpp"
#include <deque>
#include <algorithm>

namespace app {

Out ref_solve(const In& in){
    const auto& a = in.first;
    int limit = in.second;

    std::deque<int> maxq, minq;
    int best = 0, L = 0;
    for(int R=0; R<(int)a.size(); ++R){
        while(!maxq.empty() && a[maxq.back()] < a[R]) maxq.pop_back();
        maxq.push_back(R);
        while(!minq.empty() && a[minq.back()] > a[R]) minq.pop_back();
        minq.push_back(R);
        while(!maxq.empty() && !minq.empty() &&
              a[maxq.front()] - a[minq.front()] > limit){
            if(maxq.front()==L) maxq.pop_front();
            if(minq.front()==L) minq.pop_front();
            ++L;
        }
        best = std::max(best, R-L+1);
    }
    return best;
}

} 