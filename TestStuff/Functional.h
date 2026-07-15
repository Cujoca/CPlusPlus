#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <functional>
#include <vector>

using namespace std;

template <typename A, typename F>
auto map (vector<A> ref, F foo) {
    using B = decltype(foo(declval<A>()));
    vector<B> res;
    for (const auto& elem : ref) { res.push_back(foo(elem)); }
    return res;
}
#endif
