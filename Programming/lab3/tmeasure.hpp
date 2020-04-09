#ifndef TMEASURE_HPP
#define TMEASURE_HPP
#include <iterator>
#include <chrono>
#include <numeric>
#include <map>
#include <functional>
#include <algorithm>
#include "flower.hpp"

namespace ral {

/*====================================================================================
 *Interfaces
 *====================================================================================*/
//template <typename Collection, typename Function>
//double measure_time(Collection& data, Function evaluator);


//template <typename FunctionEval,
//          typename Generator=flower::generate_flowers<std::vector>>
//std::vector<double> generate_and_test(FunctionEval evaluator,
//                                      std::vector<size_t> lengs,
//                                      size_t& seed,
//                                      size_t count_samples = 10);

/*====================================================================================
 *Implementation
 *====================================================================================*/


//template <typename Collection, typename Function>
//double measure_time(Collection& data, Function evaluator)
//{
//    auto start = std::chrono::steady_clock::now();
//    evaluator(data.begin(), data.end());
//    auto end = std::chrono::steady_clock::now();

//    return (end - start).count();
//}



template <typename EvaluatorType,
          typename Generator=flower::generate_flowers<std::vector>>
std::vector<double> generate_and_test(EvaluatorType evaluator, std::vector<size_t> lengs,
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
            times.push_back(evaluator(data));
        }

        std::nth_element(average_times.begin(),
                         average_times.begin() + average_times.size()/2,
                         average_times.end());
        auto median = average_times[average_times.size()/2];
        average_times.push_back(median / 1'000'000'000);
    }
    return average_times;
}



}
#endif // TMEASURE_HPP
