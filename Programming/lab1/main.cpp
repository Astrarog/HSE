#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include "flower.hpp"
#include "sortings.hpp"
#include "tmeasure.hpp"

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& data)
{
//    out << '[';
    bool first = true;
    for (const auto& elem: data)
    {
        if(!first)
        {
            out << '\n';
        }
        first = false;
        out << elem;
    }
//    out << ']';
    return out;
}


int main()
{

    std::vector<size_t> lengs = {200, 400, 600, 800, 1000,
                                 1200, 1400, 1600, 1800, 2000,
                                 2200, 2400, 2600, 2800, 3000,
                                 3200, 3400, 3600, 3800, 4000};
    using Iterator = std::vector<flower::flower>::iterator;

    std::map<std::string, std::vector<double>> times;
    size_t seed = 0;
    times["Quick"] = ral::generate_and_test(ral::QuickSort<Iterator>, lengs, seed);
    std::cout<< "Quick done" << std::endl;
    times["Heap"] = ral::generate_and_test(ral::HeapSort<Iterator>, lengs, seed);
    std::cout<< "Heap done" << std::endl;
    times["Selection"] = ral::generate_and_test(ral::SelectionSort<Iterator>, lengs, seed);
    std::cout<< "Selecion done" << std::endl;

    std::ofstream file("data.csv", std::ios::out);
    for (auto& e: times)
    {
       file << e.first << ';' << e.second << '\n';
    }
    file << "Size" << ';' << lengs;
    return 0;
}
