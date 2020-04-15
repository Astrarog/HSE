#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include "tmeasure.hpp"
#include "output.hpp"



int main()
{
    size_t seed = 0;

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
