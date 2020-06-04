#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

int GetDistinctRealRootCount(double A, double B, double C);

void TestLinear()
{
    AssertEqual(GetDistinctRealRootCount(0, 1, 0), 1, "x=0");
    AssertEqual(GetDistinctRealRootCount(0, 1, 1), 1, "x+1=0");
    AssertEqual(GetDistinctRealRootCount(0, 1, -1), 1, "x-1=0");
}

void TestConstant()
{
    AssertEqual(GetDistinctRealRootCount(0, 0, 1), 0, "1=0");
    AssertEqual(GetDistinctRealRootCount(0, 0, -1), 0, "-1=0");
}

void TestSquareWithOneRoot()
{
    AssertEqual(GetDistinctRealRootCount(1, -6, 9), 1, "expected one root for x^2 - 6x + 9 =0");
    AssertEqual(GetDistinctRealRootCount(1, 12, 36), 1, "expected one root for x^2 + 12x + 36 =0");
}

void TestSquareWithNoRoot()
{
    AssertEqual(GetDistinctRealRootCount(1, 12, 37), 0, "expected no roots for x^2 + 12x + 37 =0");
}

void TestSquareWithTwoRoot()
{
    AssertEqual(GetDistinctRealRootCount(1, 12, 35), 2, "expected two roots for x^2 + 12x + 35 =0");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestConstant, "TestConstant");

  runner.RunTest(TestLinear, "TestLinear");

  runner.RunTest(TestSquareWithOneRoot, "TestSquareWithOneRoot");

  runner.RunTest(TestSquareWithNoRoot, "TestSquareWithNoRoot");

  runner.RunTest(TestSquareWithTwoRoot, "TestSquareWithTwoRoot");

  // добавьте сюда свои тесты
  return 0;
}
