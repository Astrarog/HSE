#ifndef SEARCH_HPP
#define SEARCH_HPP


namespace ral {

/*====================================================================================
 *Interfaces
 *====================================================================================*/
template <typename ForwardIt>
ForwardIt linear_search(ForwardIt first,
                        ForwardIt last,
                        const typename ForwardIt::value_type& value);

template <typename RandomIt>
RandomIt binary_search(RandomIt first,
                       RandomIt last,
                       const typename RandomIt::value_type& value);



/*====================================================================================
 *Implementation
 *====================================================================================*/

template <typename ForwardIt>
ForwardIt linear_search(ForwardIt first, ForwardIt last, const typename ForwardIt::value_type& value)
{
    for(auto current = first; first!=last; ++first)
    {
        if(value == *current)
        {
            return current;
        }
    }
    return last;
}


template <typename RandomIt>
RandomIt binary_search(RandomIt first, RandomIt last, const typename RandomIt::value_type& value)
{
    --last;
    auto center = first + (last-first)/2;
    while(last-first > 1)
    {
        if(*center<value)
        {
            last = center;
        }
        else
        {
            first = center;
        }
        center = first + (last-first)/2;
    }
    if (!(*center==value))
    {
        ++center;
    }
    return center;
}


}
#endif // SEARCH_HPP
