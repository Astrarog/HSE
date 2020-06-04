#include <iostream>
#include <cstdint>
#include <string>
#include <map>
#include <vector>

using namespace std;

enum class Lang {
  DE, FR, IT
};

struct Region {
  string std_name;
  string parent_std_name;
  map<Lang, string> names;
  int64_t population;
};

struct Region;
enum class Lang;

bool operator< (const Region& lhs, const Region& rhs){
    return tie(lhs.std_name, lhs.parent_std_name, lhs.names, lhs.population) <
            tie(rhs.std_name, rhs.parent_std_name, rhs.names, rhs.population);
}

int FindMaxRepetitionCount(const vector<Region>& regions)
{
    int result=0;
    map<Region, int> counts;
    for(const auto& e: regions)
    {
        result=max(result, ++counts[e]);
    }
    return result;
}

int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
