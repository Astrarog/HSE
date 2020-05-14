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
