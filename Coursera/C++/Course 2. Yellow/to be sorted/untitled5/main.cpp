#include <iostream>
#include <vector>
#include <map>
#include <tuple>


using namespace std;


template <typename T>
T Sqr(T x);

template <typename T>
vector<T> Sqr(const vector<T>& cont);

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& cont);

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p);

//template <typename Collection, typename T>
//Collection<typename T> Sqr(const Collection<typename T>& cont);

template <typename T>
T Sqr(T x)
{
    return x * x;
}

template <typename T>
vector<T> Sqr(const vector<T>& cont){
    vector<T> answ = cont;
    for (auto& e:answ)
    {
        e=Sqr(e);
    }
    return answ;
}

template <typename First, typename Second>
pair<First, Second> Sqr(const pair<First, Second>& p){
    First f = Sqr(p.first);
    Second s = Sqr(p.second);
    return {f,s};
}

template <typename Key, typename Value>
map<Key, Value> Sqr(const map<Key, Value>& cont){
    map<Key, Value> answ = cont;
    for (auto& [key, value] : answ)
    {
        value=Sqr(value);
    }
    return answ;
}



//template <typename Collection>
//Collection Sqr(const Collection& cont){
//    Collection answ = cont;
//    for (auto& e:answ)
//    {
//        e=Sqr(e);
//    }
//    return answ;
//}


int main()
{
    vector<int> v = {1, 2, 3};
    cout << "vector:";
    for (int x : Sqr(v)) {
      cout << ' ' << x;
    }
    cout << endl;

    map<int, pair<int, int>> map_of_pairs = {
      {4, {2, 2}},
      {7, {4, 3}}
    };
    cout << "map of pairs:" << endl;
    for (const auto& x : Sqr(map_of_pairs)) {
      cout << x.first << ' ' << x.second.first << ' ' << x.second.second << endl;
    }
}
