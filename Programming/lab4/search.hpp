#ifndef SEARCH_HPP
#define SEARCH_HPP


namespace ral {

/**
 * @brief Функция линейного поиска по массиву
 * @param[in] first, last -- итераторы на начало и пост конец разделяемых данных
 * @param[in] value -- искомое значение
 * @return позиция в массиве искомого элемента
 */
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

/**
 * @brief Функция бинарного поиска по массиву
 * @param[in] first, last -- итераторы на начало и пост конец разделяемых данных
 * @param[in] value -- искомое значение
 * @return позиция в массиве искомого элемента
 */
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
