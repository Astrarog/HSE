#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <cmath>
#include <chrono>
#include <boost/math/distributions/chi_squared.hpp>
#include <boost/cstdint.hpp>
#include "random.hpp"
#include "tmeasure.hpp"
#include "output.hpp"

using boost::math::chi_squared;
using boost::math::quantile;

struct uniform_gen_test
{
    double mean;
    double stdev;
    std::size_t count_boxes;
    double statistics_value;
    double quantile_value;
    bool is_uniform=false;
    uniform_gen_test(std::vector<std::uint64_t> data, double alpha = 0.05)
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        mean = sum / data.size();

        double sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0);
        stdev = std::sqrt(sq_sum / data.size() - mean * mean);
        size_t s =data.size();
        count_boxes = 1 + log2(data.size());
        chi_squared theoretical_dist(count_boxes - 1);
        quantile_value = quantile(theoretical_dist, 1-alpha);
        statistics_value = 0;
        for(int j=0; j < count_boxes; ++j)
        {
            std::size_t count_drops_in_box = std::count_if(data.begin(), data.end(),
                          [&](std::uint64_t x)
            {   double size_of_box = double(data.size()) / count_boxes;
                return size_of_box*j <= x && x<size_of_box*(j+1);});
            statistics_value+=count_drops_in_box*count_drops_in_box;
        }
        statistics_value = statistics_value / data.size() * count_boxes - data.size();
        is_uniform = statistics_value < quantile_value;
    }
};

bool operator< (const uniform_gen_test& a, const uniform_gen_test& b)
{
    return a.mean < b.mean;
}

std::ostream& operator<<(std::ostream& out, const uniform_gen_test& data)
{
    out << "The mean is: " << data.mean << std::endl;
    out << "The standart deviation is: " << data.stdev << std::endl << std::endl;
    out << "The chi-squared test information follows."<< std::endl;
    out << "The number of boxes (degrees of freedom + 1) is: " << data.count_boxes << std::endl;
    out << "The statistics value is: " << data.statistics_value << std::endl;
    out << "The quantile value of theoretical distribution is: " << data.quantile_value << std::endl;
    if(data.is_uniform)
    {
        out << "+++TEST SUCCEEDED+++" << std::endl;
    } else
    {
        out << "---DON'T PASS---" << std::endl;
    }

    return out;
}

std::ostream& operator<<(std::ostream& out, const std::vector<uniform_gen_test>& data)
{
    bool first = true;
    size_t testNo = 1;
    for (auto& elem: data)
    {

        if(!first)
        {
            out << "\n\n";
        }
        first = false;
        out << "TEST #" << testNo++ << std::endl;
        out << elem;
    }
    return out;
}


template <typename Randomer>
struct generate_random_values
{
    using elem_type = std::uint64_t;
    using val_type = std::vector<elem_type>;
    val_type value;
    generate_random_values(size_t lenght, size_t& seed):
        value((*this)(lenght, seed)) {}

    operator val_type()
    {
        return value;
    }

    val_type operator()(size_t lenght, size_t& seed)
    {
        ++seed;
        return Randomer(lenght, 73, 17);
    }
};


//struct check_stats
//{
//    uniform_gen_test value;
//    check_stats(const std::vector<std::uint64_t>& data):
//        value((*this)(data)) {}

//    operator uniform_gen_test()
//    {
//        return value;
//    }

//    uniform_gen_test operator()(const std::vector<std::uint64_t>& data)
//    {
//        return uniform_gen_test(data);
//    }
//};

uniform_gen_test check_stats(const std::vector<std::uint64_t>& data)
{
    return uniform_gen_test(data);
}


struct generate_data_for_time_measure
{
    using elem_type = std::uint64_t;
    using val_type = std::vector<elem_type>;
    val_type value;
    generate_data_for_time_measure(size_t lenght, size_t& seed):
        value((*this)(lenght, seed)) {}

    operator val_type()
    {
        return value;
    }

    val_type operator()(size_t lenght, size_t& seed)
    {
        ++seed;
        return {lenght};
    }
};

template <typename Rand>
double check_time_gen(std::vector<std::uint64_t>& lenght)
{
    size_t seed=0;
    auto start = std::chrono::steady_clock::now();
    std::vector<std::uint64_t> s = generate_random_values<Rand>(lenght[0], seed);
    auto end = std::chrono::steady_clock::now();
    return (end-start).count();
}

int main()
{
    size_t seed = 0;
    std::vector<std::uint64_t> v;
    std::vector<size_t> lengs = {10000, 20000, 30000, 40000, 50000,
                                 60000, 70000, 80000, 90000, 100000,
                                 110000, 120000, 130000, 140000, 150000,
                                 160000, 170000, 180000, 190000, 200000};
    std::map<std::string, std::vector<uniform_gen_test>> stats;
    std::map<std::string, std::vector<double>> times;

    using dum_type = ral::dummyRand<std::uint64_t>;

    using eval_type_stats = uniform_gen_test(const std::vector<std::uint64_t>&);
    using gen_type_dummy_stats = generate_random_values<dum_type>;
    stats["DummyRand"] =
            ral::generate_and_test
<eval_type_stats, uniform_gen_test, dum_type>(check_stats, lengs, seed, 1, false);


    using eval_type_dummy_time = double(std::vector<std::uint64_t>&);
    using gen_type_dummy_time = generate_data_for_time_measure;
    times["DummyRand"] =
            ral::generate_and_test
<eval_type_dummy_time, double, gen_type_dummy_time>(check_time_gen<dum_type>, lengs, seed);

        std::cout << stats["DummyRand"];
//    std::ofstream file("data.csv", std::ios::out);
//    for(const auto& [key, value]: stats)
//    {
//       file << key << ';' << value << '\n';
//       std::cout << key << "    \n" << value << '\n';
//    }
    return 0;
}
