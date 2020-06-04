#include <iostream>
#include <cstdint>

using namespace std;

int main()
{
    int n;
    uint64_t r;
    cin >> n >> r;
    uint64_t answ = 0;
    for( ;n; --n){
        int w, h, d;
        cin >> w >> h >> d;
        answ+= r*w*h*d;
    }
    cout << answ;
    return 0;
}
