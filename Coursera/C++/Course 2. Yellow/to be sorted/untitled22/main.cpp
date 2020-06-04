#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

template <typename RandomIt>
void MergeSort(RandomIt range_begin, RandomIt range_end)
{
    if (range_end - range_begin < 2)
    {
        return;
    }
    vector<typename RandomIt::value_type> elements(range_begin, range_end);
    RandomIt firts_third = elements.begin() + (elements.end() - elements.begin())/3;
    RandomIt second_third = elements.begin() + 2* (elements.end() - elements.begin())/3;
    MergeSort(elements.begin(), firts_third);
    MergeSort(firts_third, second_third);
    MergeSort(second_third, elements.end());
    vector<typename RandomIt::value_type> tmp;
    merge(elements.begin(), firts_third, firts_third, second_third, back_inserter(tmp));
    merge(tmp.begin(), tmp.end(), second_third, elements.end(), range_begin);
}


int main() {
  vector<int> v = {6, 4, 7, 6, 4, 4, 0, 1};
  MergeSort(begin(v), end(v));
  for (int x : v) {
    cout << x << " ";
  }
  cout << endl;
  return 0;
}
