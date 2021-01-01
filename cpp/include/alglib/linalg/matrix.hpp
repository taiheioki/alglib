#ifndef ALGLIB_LINALG_MATRIX_HPP_
#define ALGLIB_LINALG_MATRIX_HPP_

#include <vector>

namespace alg
{
// BEGIN DISPLAY linalg
template<typename R>
class Vector : public std::vector<R>
{
public:
};

template<typename R>
class Matrix
{
public
    int rows();
};
// END DISPLAY linalg

}  // namespace alg

#endif
