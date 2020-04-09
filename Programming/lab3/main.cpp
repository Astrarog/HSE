#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include "tmeasure.hpp"
#include "hash.hpp"
#include "flower.hpp"
#include "output.hpp"


template<> struct ral::dummy_hash<flower::flower, std::uint16_t>
{
    using result_type = std::uint16_t;
    using data_type = flower::flower;
    result_type value;

    dummy_hash(const flower::flower& data): value((*this)(data)){}
    operator result_type(){
        return value;
    }
    result_type operator()(const flower::flower& data)
    {
        return result_type(dummy_hash<std::string, std::uint16_t>(data.GetName()));
    }
};

template<> struct ral::smart_hash<flower::flower, std::uint16_t>
{
    using result_type = std::uint16_t;
    using data_type = flower::flower;
    result_type value;

    smart_hash(const flower::flower& data): value((*this)(data)){}
    operator result_type(){
        return value;
    }
    result_type operator()(const flower::flower& data)
    {
        return result_type(smart_hash<std::string, std::uint16_t>(data.GetName()));
    }
};

template <template<typename, typename> typename Hasher, typename T>
double evaluate_hashtable_search(const std::vector<T>& data)
{
    ral::HashTable<std::string, T, Hasher> table;
    std::vector<double> times;
    times.reserve(10);
    for (const auto& elem: data)
    {
        table.insert_element(elem);
    }
    for (const auto& elem: data)
    {
        auto start = std::chrono::steady_clock::now();
        table.find_element_by_key(elem.GetName());
        auto end = std::chrono::steady_clock::now();
        times.push_back((end - start).count());
    }
    std::nth_element(times.begin(),
                     times.begin() + times.size()/2,
                     times.end());
    auto median = times[times.size()/2];
    return median;
}

int main()
{
    size_t seed = 0;

    std::vector<size_t> lengs = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};
    flower::flower a = flower::random_flower(seed);

    std::map<std::string, std::vector<double>> times;

    auto dummy = evaluate_hashtable_search<ral::dummy_hash, flower::flower>;
    auto smart = evaluate_hashtable_search<ral::smart_hash, flower::flower>;

    std::cout << "Starting dummy hash searching test..." << std::endl;
    times["Dummy"] = ral::generate_and_test(dummy, lengs, seed);
    std::cout << "Done!" << std::endl;

    std::cout << "Starting smart hash searching test..." << std::endl;
    times["Smart"] = ral::generate_and_test(smart, lengs, seed);
    std::cout << "Done!" << std::endl;

    std::ofstream file("data.csv", std::ios::out);
    for(const auto& [key, value]: times)
    {
       file << key << ';' << value << '\n';
       std::cout << key << ';' << value << '\n';
    }

    std::cout << std::endl;
    return 0;
}
