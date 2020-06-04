#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream input("input.txt");
    string line;
    while(getline(input, line))
    {
        cout << line << '\n';
    }
    return 0;
}
