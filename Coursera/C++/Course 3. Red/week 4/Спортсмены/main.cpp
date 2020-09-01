#include <iostream>
#include <list>
#include <cstdint>
#include <algorithm>
#include <vector>
using namespace std;


int main()
{
    uint64_t n;
    cin >> n;

    list<uint64_t> quee;
    vector<list<uint64_t>::iterator> positions(100'000 + 1, quee.end());
    while(n--)
    {
        uint64_t who, before_whom;
        cin >> who >> before_whom;
        auto pos = quee.insert(positions[before_whom], who);
        positions[who] = pos;
    }
    for(const auto s : quee)
    {
        cout << s << '\n';
    }
    return 0;
}
