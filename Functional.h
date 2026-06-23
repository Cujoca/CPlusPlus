#ifndef FUNCTIONAL_H
#define FUNCTIONAL_H

#include <functional>
#include <vector>

template <typename A, typename B>
class VectorFunctional {
public:
    static std::vector<B> map(std::vector<A> vec, std::function<B(A)> foo) {
        std::vector<B> result;
        for (A elem: vec) {
            result.push_back(foo(elem));
        }
        return result;
    }
};
#endif
