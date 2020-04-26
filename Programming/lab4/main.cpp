#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <numeric>
#include <cmath>
//#include <boost/math/distributions/chi_squared.hpp>
#include "random.hpp"
#include "tmeasure.hpp"
#include "output.hpp"


struct uniform_gen_test
{
    double mean;
    double stdev;
    std::size_t count_boxes;
    bool is_uniform=false;
    uniform_gen_test(std::vector<std::uint64_t> data)
    {
        double sum = std::accumulate(data.begin(), data.end(), 0.0);
        mean = sum / data.size();

        double sq_sum = std::inner_product(data.begin(), data.end(), data.begin(), 0.0);
        stdev = std::sqrt(sq_sum / data.size() - mean * mean);
        count_boxes = 1 + log2(data.size());


    }
};


int main()
{
    size_t seed = 0;
    std::vector<std::uint64_t> v;


    std::vector<size_t> lengs = {10000, 20000, 30000, 40000, 50000,
                                 60000, 70000, 80000, 90000, 100000,
                                 110000, 120000, 130000, 140000, 150000,
                                 160000, 170000, 180000, 190000, 200000};
    flower::flower a = flower::random_flower(seed);

    std::map<std::string, std::vector<double>> times;

//    std::cout << "Starting dummy hash searching test..." << std::endl;
//    times["DummySearch"] = ral::generate_and_test(dummy, lengs, seed);
//    std::cout << "Done!" << std::endl;

//    std::cout << "Starting smart hash searching test..." << std::endl;
//    times["SmartSearch"] = ral::generate_and_test(smart, lengs, seed);
//    std::cout << "Done!" << std::endl;

//    std::cout << "Starting dummy hash collisions test..." << std::endl;
//    times["DummyCollisions"] = ral::generate_and_test(dummy_col, lengs, seed);
//    std::cout << "Done!" << std::endl;

//    std::cout << "Starting smart hash collisions test..." << std::endl;
//    times["SmartCollisions"] = ral::generate_and_test(smart_col, lengs, seed);
//    std::cout << "Done!" << std::endl;

    std::ofstream file("data.csv", std::ios::out);
    for(const auto& [key, value]: times)
    {
       file << key << ';' << value << '\n';
       std::cout << key << ';' << value << '\n';
    }
    return 0;
}
