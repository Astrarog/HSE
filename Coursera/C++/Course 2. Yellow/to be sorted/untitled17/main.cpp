#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <set>

using namespace std;


template <typename T>
vector<T> FindGreaterElements(const set<T>& elements, const T& border)
{
    auto pos = find_if(elements.cbegin(), elements.cend(), [border](const T& x){ return border<x;});
    return {pos, elements.end()};
}

int main() {
  for (int x : FindGreaterElements(set<int>{1, 5, 7, 8}, 5)) {
    cout << x << " ";
  }
  cout << endl;

  string to_find = "Python";
  cout << FindGreaterElements(set<string>{"C", "C++"}, to_find).size() << endl;
  return 0;
}

