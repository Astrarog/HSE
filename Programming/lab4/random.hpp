#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <algorithm>
#include <vector>
#include <cstdint>

namespace ral {

/*====================================================================================
 *Interfaces
 *====================================================================================*/
template <typename Unsigned= std::uint64_t>
Unsigned dummyRandNext(Unsigned x, Unsigned y);

template <typename Unsigned= std::uint64_t>
std::vector<Unsigned> dummyRand(Unsigned n, Unsigned x = 73, Unsigned y = 17);

template <typename Unsigned = std::uint64_t, Unsigned k1=0, Unsigned k2=69069, Unsigned b=313>
Unsigned smartRandNext(Unsigned start);

template <typename Unsigned = std::uint64_t, Unsigned k1=0, Unsigned k2=69069, Unsigned b=313>
std::vector<Unsigned> smartRand(Unsigned n, Unsigned start = 5);

/*====================================================================================
 *Implementation
 *====================================================================================*/

template <typename Unsigned>
Unsigned dummyRandNext(Unsigned x, Unsigned y)
{
     return (((x * y)>>8) & 0xffff);
}

template <typename Unsigned>
std::vector<Unsigned> dummyRand(Unsigned n, Unsigned x, Unsigned y)
{
    std::vector<Unsigned> data;
    data.reserve(n);
    while(n--)
    {
        x = dummyRandNext(x, y);
        std::swap(x, y);
        data.push_back(y);
    }
    return data;
}


template <typename Unsigned, Unsigned k1, Unsigned k2, Unsigned b>
Unsigned smartRandNext(Unsigned start)
{
    return k1*start*start + k2*start + b;
}


template <typename Unsigned, Unsigned k1, Unsigned k2, Unsigned b>
std::vector<Unsigned> smartRand(Unsigned n, Unsigned start)
{
    std::vector<Unsigned> data;
    data.reserve(n);
    while(n--)
    {
        start = smartRandNext(start);
        data.push_back(start);
    }
    return data;
}

}
#endif // RANDOM_HPP
