#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;


void PrintVectorPart(const vector<int>& numbers)
{
    auto pos = find_if(numbers.begin(), numbers.end(), [](int x){ return  x<0;});
    for (auto it = pos; it != numbers.begin(); ) {
      cout << *(--it) << " ";
    }
}


int main() {
  PrintVectorPart({6, 1, 8, -5, 4});
  cout << endl;
  PrintVectorPart({-6, 1, 8, -5, 4});  // ничего не выведется
  cout << endl;
  PrintVectorPart({6, 1, 8, 5, 4});
  cout << endl;
  return 0;
}

