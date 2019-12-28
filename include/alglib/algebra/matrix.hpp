#ifndef _ALGLIB_MATRIX_HPP_
#define _ALGLIB_MATRIX_HPP_

#include <vector>

namespace alg
{

template<typename R>
class Vector : public std::vector<R>
{
public:
    
};

template<typename R>
class Matrix
{
public:
    int rows();
};

} // end of namespace alg

#endif
