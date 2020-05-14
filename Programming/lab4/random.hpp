#ifndef RANDOM_HPP
#define RANDOM_HPP
#include <algorithm>
#include <vector>
#include <cstdint>

namespace ral {

/**
 * @brief Функция следующего пседвослучаного числа методом серидинных произведений
 * @param[in] x, y -- значения предыдущих двух значений
 * @return следующее пседвослучаное число
 */
template <typename Unsigned= std::uint64_t>
Unsigned dummyRandNext(Unsigned x, Unsigned y)
{
     return (((x * y)>>8) & 0xffff);
}

/**
 * @class dummyRand
 * @brief Класс-функтор реазлиующий метод серидинных произведений
 * Эквивалентно dummyRand(n, x, y)
 * @param[in] n -- Количество генерируемых чисел
 * @param[in] x, y -- начальные значения для генерации чисел
 * @return массив случайных чисел
 */
template <typename Unsigned= std::uint64_t, Unsigned _x = 18181, Unsigned _y = 17971>
struct dummyRand
{
    using elem_type = Unsigned;
    using val_type = std::vector<elem_type>;
    val_type value;
    dummyRand(Unsigned n, Unsigned x = _x, Unsigned y = _y):
        value((*this)(n, x, y)) {}

    operator val_type()
    {
        return value;
    }

    val_type operator()(Unsigned n, Unsigned x = _x, Unsigned y = _y)
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
};


/**
 * @brief Функция следующего пседвослучаного числа методом квадратичного конгруентного метода
 * @param[in] start -- предыдущего значения
 * @return следующее пседвослучаное число
 */
template <typename Unsigned = std::uint64_t, Unsigned k1=8, Unsigned k2=69069, Unsigned b=313>
Unsigned smartRandNext(Unsigned start)
{
    return k1*start*start + k2*start + b;
}


/**
 * @class smartRand
 * @brief Класс-функтор реазлиующий квадратичный конгруентный метод
 * Эквивалентно smartRand(n, start)
 * @param[in] n -- Количество генерируемых чисел
 * @param[in] start -- начальное значение
 * @return массив случайных чисел
 */
template <typename Unsigned = std::uint64_t, Unsigned k1=8, Unsigned k2=69069, Unsigned b=313>
struct smartRand
{
    using elem_type = Unsigned;
    using val_type = std::vector<elem_type>;
    val_type value;
    smartRand(Unsigned n, Unsigned start = 5):
        value((*this)(n, start)) {}

    operator val_type()
    {
        return value;
    }

    val_type operator()(Unsigned n, Unsigned start = 5)
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
};

}
#endif // RANDOM_HPP
