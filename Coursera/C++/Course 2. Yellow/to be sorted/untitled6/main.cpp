#include <iostream>
#include <map>
using namespace std;

template <typename T, typename U>
U& GetRefStrict(const map<T,U>& m, const T& key)
{
    if (m.count(key)){
        return const_cast<U&>(m.at(key));
    }
    else{
        throw runtime_error("");
    }
}

int main()
{
    map<int, string> m = {{0, "value"}};
    string& item = GetRefStrict(m, 0);
    item = "newvalue";
    cout << m[0] << endl;
}
