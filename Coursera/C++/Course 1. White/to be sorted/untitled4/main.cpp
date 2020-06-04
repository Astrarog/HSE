#include <iostream>
#include <set>
#include <vector>

using namespace std;

int main()
{
    int q;
    cin >> q;
    set <string> s;
    while (q){
        string st;
        cin >> st;
        s.insert(st);
        --q;
    }
    cout << s.size();
    return 0;
}
