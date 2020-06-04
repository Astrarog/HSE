#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

int main()
{
    ifstream input("input.txt");

    int n, m;
    input >> n >> m;

    while(n){
        int i = m-1;
        int val;
        input >> val;
        cout  << setw(10) << right << val;
        while(i){
            input.ignore(1);
            input >> val;
            cout << ' ' << setw(10) << right << val;
            --i;
        }
        cout  << '\n';
        --n;
    }
    return 0;
}
