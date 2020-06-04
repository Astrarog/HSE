#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class SortedStrings {
public:
  void AddString(const string& s) {
        auto position = upper_bound(begin(sorted), end(sorted), s);
        sorted.insert(position, s);
    // добавить строку s в набор
  }
  vector<string> GetSortedStrings() {
      return sorted;
  }
private:
  vector<string> sorted;
};

void PrintSortedStrings(SortedStrings& strings) {
  for (const string& s : strings.GetSortedStrings()) {
    cout << s << " ";
  }
  cout << endl;
}

int main()
{
    SortedStrings strings;

    strings.AddString("first");
    strings.AddString("third");
    strings.AddString("second");
    PrintSortedStrings(strings);

    strings.AddString("second");
    PrintSortedStrings(strings);

    return 0;
}
