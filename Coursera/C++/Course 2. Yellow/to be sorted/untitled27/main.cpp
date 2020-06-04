#include <iostream>
#include <string>
#include <deque>

using namespace std;

int main()
{
    int start, n;
    cin >> start >> n;
    deque<char> result;
    for(auto e: to_string(start))
    {
        result.push_back(e);
    }
    char last_opertaion;
    bool first = true;
    while(n--)
    {
        char operation;
        int value;
        cin >> operation >> value;
        if (first){
            result.push_back(' ');
            result.push_back(operation);
            result.push_back(' ');
            first = false;
            last_opertaion = operation;
            for(auto e: to_string(value))
            {
                result.push_back(e);
            }
            continue;
        }
        if ((operation=='*'||operation=='/')
                &&(last_opertaion == '+' || last_opertaion == '-' )){
            result.push_front('(');
            result.push_back(')');
        }
        result.push_back(' ');
        result.push_back(operation);
        result.push_back(' ');
        for(auto e: to_string(value))
        {
            result.push_back(e);
        }
        last_opertaion = operation;
    }
    for(auto e: result)
    {
        cout << e;
    }
    cout << endl;
    return 0;
}
