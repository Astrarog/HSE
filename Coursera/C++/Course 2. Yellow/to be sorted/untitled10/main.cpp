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


int GreatestCommonDivisor(int a, int b); /*{
  if (b == 0) {
    return a;
  } else {
    return GreatestCommonDivisor(b, a % b);
  }
}*/

class Rational; /*{
public:
  Rational() {  // дробь по умолчанию — 0/1
    numerator = 0;
    denominator = 1;
  }
  Rational(int new_numerator, int new_denominator) {
    const int gcd = GreatestCommonDivisor(new_numerator, new_denominator);
    // сократим дробь, разделив числитель и знаменатель на их НОД
    numerator = new_numerator / gcd;
    denominator = new_denominator / gcd;
    // знаменатель должен быть положительным
    if (denominator < 0) {
      denominator = -denominator;
      numerator = -numerator;
    }
  }

  int Numerator() const {
    return numerator;
  }

  int Denominator() const {
    return denominator;
  }

private:
  int numerator;
  int denominator;
};*/

// поскольку дроби сокращены, достаточно сравнить числители и знаменатели
bool operator == (const Rational& lhs, const Rational& rhs); /*{
  return lhs.Numerator() == rhs.Numerator() &&
      lhs.Denominator() == rhs.Denominator();
}*/

// используем обычную формулу сложения дробей, основанную на приведении слагаемых к общему знаменателю
Rational operator + (const Rational& lhs, const Rational& rhs); /*{
  return {
      lhs.Numerator() * rhs.Denominator() + rhs.Numerator() * lhs.Denominator(),
      lhs.Denominator() * rhs.Denominator()
  };
}*/

// вычитание реализуем аналогично сложению
// дублирования кода можно было избежать, определив для класса Rational операцию унарного минуса: тогда разность lhs и rhs можно было бы вычислить           как lhs + (-rhs)
Rational operator - (const Rational& lhs, const Rational& rhs); /*{
  return {
      lhs.Numerator() * rhs.Denominator() - rhs.Numerator() * lhs.Denominator(),
      lhs.Denominator() * rhs.Denominator()
  };
}*/

Rational operator * (const Rational& lhs, const Rational& rhs);/* {
  return {
      lhs.Numerator() * rhs.Numerator(),
      lhs.Denominator() * rhs.Denominator()
  };
}*/

// деление равносильно умножению на обратную («перевёрнутую») дробь
Rational operator / (const Rational& lhs, const Rational& rhs); /*{
  return lhs * Rational(rhs.Denominator(), rhs.Numerator());
}*/

istream& operator >> (istream& is, Rational& r); /*{
  int n, d;
  char c;

  if (is) {
      is >> n >> c >> d;
      if (is && c == '/') {
          r = Rational(n, d);
      }
  }

  return is;
}*/

ostream& operator << (ostream& os, const Rational& r); /*{
  return os << r.Numerator() << '/' << r.Denominator();
}*/

// чтобы сравнить lhs с rhs, сравним их разность с нулём, что равносильно сравнению с нулём числителя
bool operator < (const Rational& lhs, const Rational& rhs); /*{
  return (lhs - rhs).Numerator() < 0;
}*/

bool RatiosAreEual(const Rational& lhs, const Rational& rhs)
{
    return lhs.Numerator() == rhs.Numerator() && lhs.Denominator() == rhs.Denominator();
}

void TestConstructing()
{
    Rational r0(3, 2);
    AssertEqual(r0.Numerator(), 3, "Non-Basic constructing pos/pos Numerator");
    AssertEqual(r0.Denominator(), 2, "Non-Basic constructing pos/pos Denominator");
    Rational r01(-3, 2);
    AssertEqual(r01.Numerator(), -3, "Non-Basic constructing neg/pos Numerator");
    AssertEqual(r01.Denominator(), 2, "Non-Basic constructing neg/pos Denominator");

    Rational r02(-3, -2);
    AssertEqual(r02.Numerator(), 3, "Non-Basic constructing neg/neg Numerator");
    AssertEqual(r02.Denominator(), 2, "Non-Basic constructing neg/neg Denominator");
    Rational r03(3, -2);
    AssertEqual(r03.Numerator(), -3, "Non-Basic constructing pos/neg Numerator");
    AssertEqual(r03.Denominator(), 2, "Non-Basic constructing pos/neg Denominator");

    Rational r1;
    AssertEqual(r1.Numerator(), 0, "Basic constructing Numerator");
    AssertEqual(r1.Denominator(), 1, "Basic constructing Denominator");
    Rational r2(0, 1);
    Rational r3(0, -1);
    Assert(RatiosAreEual(r1,r2), "Comparison non-basic to basic constructing");
    Assert(RatiosAreEual(r3,r1), "Comparison non-basic to basic constructing");
    Rational r4(2, 4);
    Rational r5(1, 2);
    Assert(RatiosAreEual(r4,r5), "2/4 should be 1/2");
    Rational r6(-2, 4);
    Rational r7(1, -2);
    Rational r8(-1, 2);
    Assert(RatiosAreEual(r6,r8), "-2/4 should be -1/2");
    Assert(RatiosAreEual(r7,r8), "1/-2 should be -1/2");
}

int main() {
  TestRunner runner;
  runner.RunTest(TestConstructing, "TestConstructing");
  return 0;
}
