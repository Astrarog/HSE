#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

int main()
{
    map<int, int> m;
    cout << m.size() << endl;
    m[1];
    cout << m.size() << endl;
    /*int n;
    cin >> n;
    vector<string> ans;
    ans.reserve(n);
    while(n){
        string c;
        cin >> c;
        ans.push_back(c);
        --n;
    }
    sort(ans.begin(), ans.end(), [](string a, string b){
        transform(a.begin(), a.end(), a.begin(), [](unsigned char x){
            return std::tolower(x);
        });

        transform(b.begin(), b.end(), b.begin(), [](unsigned char x){
            return std::tolower(x);
        });

        return a < b;
    } );

    for(string s:ans)
    {
        cout << s << ' ';
    }*/
    return 0;
}
