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

//template <typename FunctionEval,
//          typename OutputType = double,
//          typename Generator=flower::generate_flowers<std::vector>>
//std::vector<OutputType> generate_and_test(FunctionEval evaluator,
//                                      std::vector<size_t> lengs,
//                                      size_t& seed,
//                                      size_t count_samples = 10);

/*====================================================================================
 *Implementation
 *====================================================================================*/



template <typename FunctionEval,
          typename OutputType = double,
          typename Generator=flower::generate_flowers<std::vector>>
std::vector<OutputType> generate_and_test(FunctionEval evaluator,
                                      std::vector<size_t> lengs,
                                      size_t& seed,
                                      size_t count_samples = 10,
                                      bool only_averages = true)
{
    ++seed;
    using val_type = typename Generator::val_type;
    std::vector<OutputType> average_output;
    average_output.reserve(lengs.size());
    for (auto l:lengs)
    {
        std::vector<OutputType> outs;
        outs.reserve(count_samples);
        for(size_t i=0;i<count_samples;++i)
        {
            val_type data = Generator(l, seed);
            outs.push_back(evaluator(data));
        }
        if (only_averages)
        {
            std::nth_element(outs.begin(),
                             outs.begin() + outs.size()/2,
                             outs.end());
            auto median = outs[outs.size()/2];
            average_output.push_back(median);
        }
        else
        {
            for(const auto & e: outs)
            {
                average_output.push_back(e);
            }
        }
    }
    return average_output;
}



}
#endif // TMEASURE_HPP
