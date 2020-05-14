#ifndef TMEASURE_HPP
#define TMEASURE_HPP

#include <vector>
#include <chrono>
#include <numeric>

#include "flower.hpp"

namespace ral {


/**
 * @brief Функция для подсчёта времени выполнения 1ой итерации функции evaluator
 * @param[in] data -- передаваемые данные
 * @param[in] evaluator -- функция, принимающая итератор на начало и конец данных, время работы которой необходимо измерить
 * @return время работы функции evaluator
 */
template <typename Collection, typename Function>
double measure_time(Collection& data, Function evaluator)
{
    auto start = std::chrono::steady_clock::now();
    evaluator(data.begin(), data.end());
    auto end = std::chrono::steady_clock::now();

    return (end - start).count();
}



/**
 * @brief Функция генерации данных и для подсчёта среднего времени выполнения функции evaluator
 * @param[in] evaluator -- функция, принимающая итератор на начало и конец данных, время работы которой необходимо измерить
 * @param[in] lengs -- длины массивов, которые надо генерировать и над которыми надо производить замер времени.
 * @param[in] seed -- начальное значение для генератора случайных чисел
 * @return среднее время работы функции evaluator
 */
template <typename Function>
std::vector<double> generate_and_test(Function evaluator, std::vector<size_t> lengs, size_t& seed)
{
    ++seed;
    std::vector<double> average_times;
    average_times.reserve(lengs.size());
    for (auto l:lengs)
    {
        std::vector<double> times;
        times.reserve(10);
        for(int i=0;i<10;++i){
            std::vector<flower::flower> data = flower::generate_flowers(l, seed);
            times.push_back(measure_time(data, evaluator));
        }
        //may be meadian is better
        double sum = std::accumulate(times.begin(), times.end(), 0.0);
        double mean = sum / times.size();
        average_times.push_back(mean / 1'000'000'000);
    }
    return average_times;
}

}
#endif // TMEASURE_HPP
