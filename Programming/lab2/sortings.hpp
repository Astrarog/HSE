#ifndef SORTINGS_HPP
#define SORTINGS_HPP
#include <cmath>
#include <cstdint>
#include <stdexcept>
#include <algorithm>

namespace ral {


/**
 * @brief Функция поиска минимального элемента в массиве
 * @param[in] first, last -- итераторы на начало и пост конец искомых данных
 * @return позиция на минимальный элемент в массиве
 */
template<class ForwardIt >
ForwardIt find_min_element(ForwardIt first, ForwardIt last)
{
    ForwardIt min_position = first;
    for(auto current = first; current!=last; current=next(current))
    {
        if (*current < *min_position)
        {
            min_position = current;
        }
    }
    return min_position;
}


/**
 * @brief Функция селективной сортировки массива
 * @param[in] first, last -- итераторы на начало и пост конец сортируемых данных
 */
template<typename RandomIt>
void SelectionSort(RandomIt first,  RandomIt last)
{
    for(auto it = first; it!=last; ++it)
    {
        RandomIt min_position = find_min_element(it, last);
        std::iter_swap(min_position, it);
    }
}

/**
 * @brief Функция разделения массива на 2 части: меньше центрального и больше
 * @param[in] first, last -- итераторы на начало и пост конец разделяемых данных
 * @return точку разделения
 */
template <typename RandomIt>
RandomIt partition(RandomIt first, RandomIt last){
    --last;
    auto central = first + (last-first)/2;
    while (last - first >= 0)
    {
        while(*first < *central)
        {
            ++first;
        }
        while(*central < *last)
        {
            --last;
        }
        if (!(last - first>0))
        {
            break;
        }
        std::iter_swap(first++, last--);
    }
    return last+1;
}


/**
 * @brief Функция быстрой сортировки массива
 * @param[in] first, last -- итераторы на начало и пост конец сортируемых данных
 */
template<typename RandomIt>
void QuickSort(RandomIt first,  RandomIt last)
{
    if(last - first > 1)
    {
        auto pivot  =  partition(first, last);
        QuickSort(first, pivot);
        QuickSort(pivot, last);
    }
}

/**
 * @brief Функция просейки элемента вверх
 * @param[in] first, last -- итераторы на начало и пост конец кучи
 * @param[in] current -- итератор на просеиваемый элемент
 */
template<typename RandomIt>
void ShiftUp(RandomIt first,  RandomIt last, RandomIt current)
{
    if (!(current - first >= 0 && last - current >= 0))
    {
        throw std::out_of_range("Node is not in range");
    }

    auto parent = current + (current-first - 1)/2;
    while( *current < *parent )
    {
        std::iter_swap(current, parent);
        current = parent;
        parent = current + (current-first - 1)/2;
    }
}

/**
 * @brief Функция просейки элемента вниз
 * @param[in] first, last -- итераторы на начало и пост конец кучи
 * @param[in] current -- итератор на просеиваемый элемент
 */
template<typename RandomIt>
void ShiftDown(RandomIt first,  RandomIt last, RandomIt current){
    size_t size = last - first;
    while(2*(current - first) + 1 < size)
    {
        auto left = current + (current - first) + 1;
        auto right = current + (current - first) + 2;
        auto max_child = left;

        //check if right exists
        if (right - first < size)
        {
            if (*right > *left)
            {
                max_child = right;
            }
        }

        if (*current > *max_child){
            break;
        }
        std::iter_swap(current, max_child);
        current = max_child;
    }
}

/**
 * @brief Функция построения кучи над массивом
 * @param[in] first, last -- итераторы на начало и пост конец данных для построения кучи
 */
template<typename RandomIt>
void BuildHeap(RandomIt first,  RandomIt last)
{
    size_t size = last - first;
    auto center = first + size/2;
    for (auto currnet = center; currnet!=first; --currnet)
    {
        ShiftDown(currnet, last, currnet);
    }
    ShiftDown(first, last, first);
}

/**
 * @brief Функция пирамидальной сортировки массива
 * @param[in] first, last -- итераторы на начало и пост конец сортируемых данных
 */
template<typename RandomIt>
void HeapSort(RandomIt first,  RandomIt last)
{
    BuildHeap(first, last);

    for (auto current=std::prev(last); current!=first; --current)
    {
         std::iter_swap(first, current);
         ShiftDown(first, current, first);
    }
}

}
#endif // SORTINGS_HPP
