#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    cin >> n ;
    vector<int> v;
    v.reserve(n);
    while (n) {
        int val;
        cin >> val;
        v.push_back(val);
        --n;
    }

    sort(v.begin(), v.end(), [](int a, int b){return abs(a)<abs(b);});
    for (int a: v){
        cout << a << ' ';
    }


    return 0;
}
