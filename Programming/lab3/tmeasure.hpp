#ifndef TMEASURE_HPP
#define TMEASURE_HPP

#include <vector>
#include <chrono>
#include <numeric>
#include <map>
#include <functional>

#include "flower.hpp"

namespace ral {


template <typename Collection, typename Function>
double measure_time(Collection& data, Function evaluator)
{
    auto start = std::chrono::steady_clock::now();
    evaluator(data.begin(), data.end());
    auto end = std::chrono::steady_clock::now();

    return (end - start).count();
}

template <typename FunctionEval, typename Collection>
std::vector<double> generate_and_test(FunctionEval evaluator,
                                      std::vector<size_t> lengs,
                                      size_t& seed,
                                      typename std::function<Collection(size_t, size_t&)> generator=flower::generate_flowers)
{
    ++seed;
    std::vector<double> average_times;
    average_times.reserve(lengs.size());
    for (auto l:lengs)
    {
        std::vector<double> times;
        times.reserve(10);
        for(int i=0;i<10;++i){
            Collection data = generator(l, seed);
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
