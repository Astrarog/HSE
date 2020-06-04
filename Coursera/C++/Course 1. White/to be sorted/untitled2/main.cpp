#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    vector <bool> A;
    int n, a, k;
    cin >> n;
    string s;
    for (int i=0; i<n; i++)
    {
        cin >> s;
        if (s == "WORRY")
        {
            cin >>  a;
            A[a] = 1;
        }
        if (s == "QUIET")
        {
            cin >>  a;
            A[a] = 0;
        }
        if (s == "COME")
        {
            cin >>  a;
            if (a >=  0)
            {
                for (int j=0; j<a; j++)
                {
                    A.push_back(0);
                }
            }
            else
            {
                cout << A.size();
                for (int j=0; j<a; j++)
                {
                    A.resize(A.size());
                }
                cout << A.size();
            }
        }
        if (s == "WORRY_COUNT")
        {
            k = 0;
            for (int j=0; j<A.size(); j++)
            {
                if (A[j] == 1)
                {
                    k++;
                }
            }
            cout << k;
        }

    }

}
