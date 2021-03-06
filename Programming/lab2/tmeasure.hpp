#ifndef TMEASURE_HPP
#define TMEASURE_HPP

#include <vector>
#include <chrono>
#include <numeric>
#include <map>
#include <functional>

#include "flower.hpp"

namespace ral {


/**
 * @brief Функция генерации данных и для подсчёта среднего времени выполнения функции evaluator
 * @param[in] evaluator -- функция, принимающая массив данных, время работы которой необходимо измерить
 * @param[in] lengs -- длины массивов, которые надо генерировать и над которыми надо производить замер времени.
 * @param[in] seed -- начальное значение для генератора случайных чисел
 * @param[in] count_samples -- количество образцов по которым будет браться среднее значение
 * @return среднее время работы функции evaluator
 */
template <typename Evaluator,
          typename OutputType = double,
          typename Generator=flower::generate_flowers<std::vector>>
std::vector<OutputType> generate_and_test(Evaluator evaluator, std::vector<size_t> lengs,
                                      size_t& seed,
                                      size_t count_samples = 10)
{
    ++seed;
    using val_type = typename Generator::val_type;
    std::vector<OutputType> average_output;
    average_output.reserve(lengs.size());
    for (auto l:lengs)
    {
        std::vector<OutputType> outs;
        outs.reserve(10);
        for(size_t i=0;i<count_samples;++i)
        {
            val_type data = Generator(l, seed);
            outs.push_back(evaluator(data));
        }

        std::nth_element(outs.begin(),
                         outs.begin() + outs.size()/2,
                         outs.end());
        auto median = outs[outs.size()/2];
        average_output.push_back(median);
    }
    return average_output;
}



}
#endif // TMEASURE_HPP
