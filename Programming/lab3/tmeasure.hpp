#ifndef TMEASURE_HPP
#define TMEASURE_HPP
#include <iterator>
#include <chrono>
#include <numeric>
#include <map>
#include <functional>
#include "flower.hpp"

namespace ral {

/*====================================================================================
 *Interfaces
 *====================================================================================*/
template <typename Collection, typename Function>
double measure_time(Collection& data, Function evaluator);


//template <typename FunctionEval,
//          typename Generator=flower::generate_flowers<std::vector>>
//std::vector<double> generate_and_test(FunctionEval evaluator,
//                                      std::vector<size_t> lengs,
//                                      size_t& seed,
//                                      size_t count_samples = 10);

/*====================================================================================
 *Implementation
 *====================================================================================*/


template <typename Collection, typename Function>
double measure_time(Collection& data, Function evaluator)
{
    auto start = std::chrono::steady_clock::now();
    evaluator(data.begin(), data.end());
    auto end = std::chrono::steady_clock::now();

    return (end - start).count();
}



template <typename FunctionEval,
          typename Generator=flower::generate_flowers<std::vector>>
std::vector<double> generate_and_test(FunctionEval evaluator,
                                      std::vector<size_t> lengs,
                                      size_t& seed,
                                      size_t count_samples = 10)
{
    ++seed;
    using val_type = typename Generator::val_type;
    std::vector<double> average_times;
    average_times.reserve(lengs.size());
    for (auto l:lengs)
    {
        std::vector<double> times;
        times.reserve(10);
        for(size_t i=0;i<count_samples;++i)
        {
            val_type data = Generator(l, seed);
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
