#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

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

bool IsPalindrom(const string& s);/*{
    for (int i = 0; i < s.size() / 2; ++i) {
        if (s[i] != s[s.size() - i - 1]) {
            return false;
        }
    }
    return true;
}*/

void TestTruePlaindroms()
{
    Assert(IsPalindrom(""), "\"\"  => true");
    Assert(IsPalindrom("a"), "\"a\"  => true");
    Assert(IsPalindrom("aa"), "\"aa\"  => true");
    Assert(IsPalindrom("aba"), "\"aba\"  => true");
    Assert(IsPalindrom("a b a"), "\"a b a\"  => true");
    Assert(IsPalindrom(" aba "), "\" aba \"  => true");
    Assert(IsPalindrom(" ab   c   ba "), "\" ab   c   ba \"  => true");
    Assert(IsPalindrom(" a b      b a "), "\" a b      b a \"  => true");
    Assert(IsPalindrom("a\tb \n  \n b\ta"), "\"a\tb \n  \n b\ta\"  => true");
}

void TestAlmostPlaindroms()
{
    Assert(!IsPalindrom(" a"), "\" a\"  => false");
    Assert(!IsPalindrom(" aa"), "\" aa\"  => false");
    Assert(!IsPalindrom(" aba"), "\" aba\"  => false");
    Assert(!IsPalindrom(" a b a"), "\" a b a\"  => false");
    Assert(!IsPalindrom("  aba "), "\"  aba \"  => false");
    Assert(!IsPalindrom("  ab   c   ba "), "\"  ab   c   ba \"  => false");
    Assert(!IsPalindrom("  a b      b a "), "\"  a b      b a \"  => false");
    Assert(!IsPalindrom(" a\tb \n  \n b\ta"), "\" a\tb \n  \n b\ta\"  => false");

    Assert(!IsPalindrom("a "), "\"a \"  => false");
    Assert(!IsPalindrom("aa "), "\"aa \"  => false");
    Assert(!IsPalindrom("aba "), "\"aba \"  => false");
    Assert(!IsPalindrom("a b a "), "\"a b a \"  => false");
    Assert(!IsPalindrom(" aba  "), "\" aba  \"  => false");
    Assert(!IsPalindrom(" ab   c   ba  "), "\" ab   c   ba  \"  => false");
    Assert(!IsPalindrom(" a b      b a  "), "\" a b      b a  \"  => false");
    Assert(!IsPalindrom("a\tb \n  \n b\ta "), "\"a\tb \n  \n b\ta \"  => false");

    Assert(!IsPalindrom("ea"), "\"ea\"  => false");
    Assert(!IsPalindrom("eaa"), "\"eaa\"  => false");
    Assert(!IsPalindrom("eaba"), "\"eaba\"  => false");
    Assert(!IsPalindrom("ea b a"), "\"ea b a\"  => false");
    Assert(!IsPalindrom("e aba "), "\"e aba \"  => false");
    Assert(!IsPalindrom("e ab   c   ba "), "\"e ab   c   ba \"  => false");
    Assert(!IsPalindrom("e a b      b a "), "\"e a b      b a \"  => false");
    Assert(!IsPalindrom("ea\tb \n  \n b\ta"), "\"ea\tb \n  \n b\ta\"  => false");

    Assert(!IsPalindrom("ae"), "\"ae\"  => false");
    Assert(!IsPalindrom("aae"), "\"aae\"  => false");
    Assert(!IsPalindrom("abae"), "\"abae\"  => false");
    Assert(!IsPalindrom("a b ae"), "\"a b ae\"  => false");
    Assert(!IsPalindrom(" aba e"), "\" aba e\"  => false");
    Assert(!IsPalindrom(" ab   c   ba e"), "\" ab   c   ba e\"  => false");
    Assert(!IsPalindrom(" a b      b a e"), "\" a b      b a e\"  => false");
    Assert(!IsPalindrom("a\tb \n  \n b\tae"), "\"a\tb \n  \n b\tae\"  => false");


    Assert(!IsPalindrom("abab"), "\"abab \"  => false");
    Assert(!IsPalindrom("a b a b"), "\"a b a b\"  => false");
    Assert(!IsPalindrom(" bababaa "), "\" bababaa \"  => false");

    Assert(!IsPalindrom(" b\t"), "\" b\t\"  => false");
    Assert(!IsPalindrom(" b  "), "\" b  \"  => false");
    Assert(!IsPalindrom("      ab   c   ba "), "\"      ab   c   ba \"  => false");
    Assert(!IsPalindrom("abbcddefedbcbba"), "\"abbcddefedbcbba\"  => false");
    Assert(!IsPalindrom("abb    asda aba svaa    bba"), "\"abb    asda aba svaa    bba\"  => false");
    Assert(!IsPalindrom("ab       a"), "\"ab       a\"  => false");
    Assert(!IsPalindrom("a                            bbbbb           a"), "\"a                            bbbbb           a\"  => false");
}

void NotPalindroms()
{
    Assert(!IsPalindrom("asdasfasfasfasf\t"), "\"asdasfasfasfasf\t\"  => false");
    Assert(!IsPalindrom("--123asfas da "), "\"--123asfas da \"  => false");
    Assert(!IsPalindrom("123456789"), "\"123456789\"  => true");
    Assert(!IsPalindrom("abbcdde231234fedbcbba"), "\"abbcdde231234fedbcbba\"  => false");
}


int main() {
  TestRunner runner;
  runner.RunTest(TestTruePlaindroms, "TestTruePlaindroms");
  runner.RunTest(NotPalindroms, "NotPalindroms");
  runner.RunTest(TestAlmostPlaindroms, "TestAlmostPlaindroms");
  return 0;
}
