#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <random>
#include <set>
#include "flower.hpp"
#include "sortings.hpp"
#include "search.hpp"
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
            out << ';';
        }
        first = false;
        out << elem;
    }
//    out << ']';
    return out;
}


template <typename ForfardIt>
void eval_linear_search(ForfardIt begin, ForfardIt end)
{
    size_t seed = 0;
    thread_local static std::mt19937 rg(seed);
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, end-begin);

    typename ForfardIt::value_type value_to_search = *(begin+pick(rg));

    ral::linear_search(begin, end, value_to_search);
}

template <typename ForfardIt>
void eval_binary_search(ForfardIt begin, ForfardIt end)
{
    size_t seed = 0;
    thread_local static std::mt19937 rg(seed);
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, end-begin);

    typename ForfardIt::value_type value_to_search = *(begin+pick(rg));

    ral::binary_search(begin, end, value_to_search);
}

template <typename ForfardIt>
void sort_and_search(ForfardIt begin, ForfardIt end)
{
    size_t seed = 0;
    thread_local static std::mt19937 rg(seed);
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, end-begin);

    typename ForfardIt::value_type value_to_search = *(begin+pick(rg));

    ral::QuickSort(begin, end);
    ral::binary_search(begin, end, value_to_search);
}


double mulimap_measure(const std::multimap<std::string, flower::flower>& data)
{
    size_t seed = 0;

    std::vector<std::string> keys;
    for( auto it = data.begin(), end = data.end();
         it!=end;
         it = data.upper_bound(it->first)
      )
    {
        keys.push_back(it->first);
    }

    thread_local static std::mt19937 rg(seed);
    thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, keys.end()-keys.begin());

    std::string value_to_search = *(keys.begin()+pick(rg));

    auto start = std::chrono::steady_clock::now();
    data.find(value_to_search);
    auto end = std::chrono::steady_clock::now();

    return (end-start).count();
}

//template <typename FunctionEval>
std::vector<double> generate_and_test_multimap( std::vector<size_t> lengs, size_t& seed)
{
    ++seed;
    std::vector<double> average_times;
    average_times.reserve(lengs.size());
    for (auto l:lengs)
    {
        std::vector<double> times;
        times.reserve(10);
        for(int i=0;i<10;++i){
            std::vector<flower::flower> data_raw = flower::generate_flowers(l, seed);
            std::multimap<std::string, flower::flower> data;

            for(const auto elem: data_raw)
            {
                data.insert({elem.GetName(), elem});
            }
            times.push_back(mulimap_measure(data));
        }
        //may be meadian is better
        double sum = std::accumulate(times.begin(), times.end(), 0.0);
        double mean = sum / times.size();
        average_times.push_back(mean / 1'000'000'000);
    }
    return average_times;
}

int main()
{

    std::vector<size_t> lengs = {10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000};

    using Iterator = std::vector<flower::flower>::iterator;

    std::map<std::string, std::vector<double>> times;
    size_t seed = 0;

    times["Linear"] = ral::generate_and_test(eval_linear_search<Iterator>, lengs, seed);
    std::cout << "Linear is done" << std::endl;

    times["Binary"] = ral::generate_and_test(eval_binary_search<Iterator>, lengs, seed);
    std::cout<< "Binary is done" << std::endl;

    times["Quic sort and Binary Search"] = ral::generate_and_test(sort_and_search<Iterator>, lengs, seed);
    std::cout<< "Quic sort and Binary Search is done" << std::endl;

    times["multimap"] = generate_and_test_multimap(lengs, seed);

    std::ofstream file("data.csv", std::ios::out);
    for (auto& e: times)
    {
       file << e.first << ';' << e.second << '\n';
    }
    file << "Size" << ';' << lengs;
    return 0;
}
