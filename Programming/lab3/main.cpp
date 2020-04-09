#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "flower.hpp"
#include "tmeasure.hpp"
#include "hash.hpp"
#include "output.hpp"


template <template<typename, typename> typename Hasher>
double evaluate_hashtable_search(const std::vector<flower::flower>& data)
{
    ral::HashTable<std::string, flower::flower, Hasher> table;
    for (const auto& elem: data)
    {
        table.insert_element(elem.GetName(), elem);
    }
    auto start = std::chrono::steady_clock::now();
    for (const auto& elem: data)
    {
        table.find_element_by_key(elem.GetName());

    }
    auto end = std::chrono::steady_clock::now();
    return (end - start).count();
}

int main()
{
    size_t seed = 0;

    std::vector<size_t> lengs = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    flower::flower a = flower::random_flower(seed);

    std::map<std::string, std::vector<double>> times;

    auto dummy = evaluate_hashtable_search<ral::dummy_hash>;
    auto smart = evaluate_hashtable_search<ral::smart_hash>;

    std::cout << "Starting dummy hash searching test..." << std::endl;
    times["Dummy"] = ral::generate_and_test(dummy,lengs, seed);
    std::cout << "Done!" << std::endl;

    std::cout << "Starting smart hash searching test..." << std::endl;
    times["Smart"] = ral::generate_and_test(smart,lengs, seed);
    std::cout << "Done!" << std::endl;

    std::ofstream file("data.csv", std::ios::out);
    for(const auto& [key, value]: times)
    {
       file << key << ';' << value << '\n';
    }

    std::cout << std::endl;
    return 0;
}
