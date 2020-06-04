#include <iostream>
#include <cstdint>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    uint32_t n;
    cin >> n;

    vector<int32_t> v;
    v.reserve(n);

    int64_t summ=0;
    for (uint32_t i=0; i<n; ++i)
    {
        int32_t value;
        cin >> value;
        summ+=value;
        v.push_back(value);
    }
    double sr = (summ+.0) / n;
    cout<< count_if(v.begin(), v.end(), [sr](int32_t x){ return x>sr;}) << endl;
    for (size_t i=0; i<v.size(); ++i)
    {
        if(v[i]>sr){
            cout << i << ' ';
        }
    }
    return 0;
}
