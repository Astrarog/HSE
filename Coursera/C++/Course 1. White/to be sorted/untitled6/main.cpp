#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;

enum class argumets
{
    ADD,
    COUNT,
    CHECK
};

int main()
{
    int q;
    cin >> q;
    map<string, set<string>> slov;
    while(q)
    {
        string arg;
        cin >> arg;
        if(arg == "ADD")
        {
            string wrd1, wrd2;
            cin >> wrd1 >> wrd2;
            slov[wrd1].insert(wrd2);
            slov[wrd2].insert(wrd1);
        }else if (arg == "CHECK")
        {
            string wrd1, wrd2;
            cin >> wrd1 >> wrd2;
            if(slov.count(wrd1))
            {
                if(slov[wrd1].count(wrd2)) {
                    cout << "YES" << endl;
                }
                else {cout << "NO" << endl;}
            }
            else{
                cout << "NO" << endl;
            }
        }else if (arg == "COUNT")
        {
            string wrd;
            cin >> wrd;
            if(slov.count(wrd))
            {
                cout << slov[wrd].size() << endl;
            }
            else{
                cout << 0 << endl;
            }
        }
        --q;
    }
}
