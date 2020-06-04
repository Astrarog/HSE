#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <set>
#include <numeric>
using namespace std;

vector<string> SplitIntoWords(const string& s)
{
    vector<string> ans;
    auto prev = s.cbegin(),
            pos = find(prev, s.cend(), ' ');
    for(;pos!=s.cend(); pos=find(pos, s.cend(), ' '))
    {
        ans.push_back(string(prev, pos));
        prev = ++pos;
    }
    ans.push_back(string(prev, pos));
    return ans;

}

int main() {
  string s = "C Cpp Java Python";

  vector<string> words = SplitIntoWords(s);
  cout << words.size() << " ";
  for (auto it = begin(words); it != end(words); ++it) {
    if (it != begin(words)) {
      cout << "/";
    }
    cout << *it;
  }
  cout << endl;

  return 0;
}
