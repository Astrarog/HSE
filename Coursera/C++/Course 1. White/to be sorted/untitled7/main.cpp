#include <iostream>
#include <set>
#include <string>
#include <map>
#include <vector>

using namespace std;

int main()
{
        map<set<string>, int> m;

        int q;
        cin >> q;
        while(q)
        {
            size_t i;
            cin >> i;
            vector<string> lline;
            lline.reserve(i);
            while(i)
            {
                string s;
                cin >> s;
                lline.push_back(s);
                --i;
            }
            set<string> line(begin(lline), end(lline));
            if(m.count(line))
            {
                cout << "Already exists for " << m[line] << endl;
            } else
            {
                int new_value = m.size()+1;
                m[line] = new_value;
                cout << "New bus "  << new_value << endl;
            }
            --q;
    }
    return 0;
}
