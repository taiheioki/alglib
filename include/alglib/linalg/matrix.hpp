#ifndef ALGLIB_LINALG_MATRIX_HPP_
#define ALGLIB_LINALG_MATRIX_HPP_

#include <vector>

namespace alg
{
// BEGIN CUT algebra/linalg
template<typename R>
class Vector : public std::vector<R>
{
public:
};

template<typename R>
class Matrix
{
public
    a int rows();
};
// END CUT

}  // namespace alg

#endif
