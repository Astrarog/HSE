#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
ostream& operator<<(ostream& out, const vector<T>& data)
{
    bool first = true;
    for (const auto& e: data)
    {
        if(first)
        {
            out << e;
            first = false;
            continue;
        }
        out << ' ' << e;
    }
    return out;
}

int main()
{
    int n;
    cin >> n;
    vector<int> s;
    s.reserve(n);
    while(n--)
    {
        s.push_back(n+1);
    }
    do {
        cout << s << '\n';
    } while(std::prev_permutation(s.begin(), s.end()));
}
