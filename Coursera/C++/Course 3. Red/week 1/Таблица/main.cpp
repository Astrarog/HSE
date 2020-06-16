#include <utility>
#include "test_runner.h"

using namespace std;

template <typename T>
class Table
{
private:
    vector<vector<T>> data;
public:
    Table(size_t first, size_t second): data()
    {
        Resize(first, second);
    }
    vector<T>& operator[](size_t idx) { return data[idx];}
    const vector<T>& operator[](size_t idx) const { return data[idx];}
    pair<size_t,size_t> Size() const { return {data.size(), (data.empty() ? 0 : data[0].size())}; }
    void Resize(size_t first, size_t second)
    {
        data.resize(first);
        for (auto& row: data)
        {
            row.resize(second);
        }
    }


};


void TestTable() {
  Table<int> t(1, 1);
  ASSERT_EQUAL(t.Size().first, 1u);
  ASSERT_EQUAL(t.Size().second, 1u);
  t[0][0] = 42;
  ASSERT_EQUAL(t[0][0], 42);
  t.Resize(3, 4);
  ASSERT_EQUAL(t.Size().first, 3u);
  ASSERT_EQUAL(t.Size().second, 4u);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestTable);
  return 0;
}
