#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;

int main()
{
    ifstream input("input.txt");
    double d;
    while(input >> d)
    {
        cout << fixed << setprecision(3) << d << '\n';
    }
    return 0;
}
