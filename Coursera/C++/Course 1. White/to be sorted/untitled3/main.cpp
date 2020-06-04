#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main()
{
        map<vector<string>, int> m;

        int q;
        cin >> q;
        while(q)
        {
            size_t i;
            cin >> i;
            vector<string> line;
            line.reserve(i);
            while(i)
            {
                string s;
                cin >> s;
                line.push_back(s);
                --i;
            }
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
