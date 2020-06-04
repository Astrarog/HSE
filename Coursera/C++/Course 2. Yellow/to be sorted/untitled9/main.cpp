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

// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year); /*{
  string name;  // изначально имя неизвестно

  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}*/

class Person; /*{
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }
  string GetFullName(int year) {
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

    // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

    // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};*/


void TestsIncognito(){
    Person person;
    for (int year : {1900, 1965, 1990}) {
      AssertEqual(person.GetFullName(year), "Incognito", "Incognito person for 1900, 1965, 1990");
    }
    person.ChangeFirstName(1965, "Polina");
    AssertEqual(person.GetFullName(1964), "Incognito", "Polina was Incognito in 1964");
    person.ChangeLastName(1967, "Sergeeva");
    AssertEqual(person.GetFullName(1964), "Incognito", "Polina Sergeeva was Incognito in 1964");

    person.ChangeFirstName(1970, "Appolinaria");

    AssertEqual(person.GetFullName(1964), "Incognito", "Appolinaria (Polina) Sergeeva was Incognito in 1964");

    person.ChangeLastName(1968, "Volkova");

    AssertEqual(person.GetFullName(1964), "Incognito", "Appolinaria Volkova (Polina Sergeeva) was Incognito in 1964");
}

void TestsOnlyName()
{
    Person person;
    person.ChangeFirstName(1965, "Polina");

    for (int year : {1965, 1990}) {
      AssertEqual(person.GetFullName(year), "Polina with unknown last name", "Polina had no last name in 1965, 1990");
    }
    person.ChangeFirstName(1970, "Appolinaria");
    for (int year : {1965, 1969}) {
      AssertEqual(person.GetFullName(year), "Polina with unknown last name", "Appolinaria (Polina) had no last name in 1965, 1969");
    }
    for (int year : {1970, 1990}) {
      AssertEqual(person.GetFullName(year), "Appolinaria with unknown last name", "Appolinaria (Polina) had no last name in 1970, 1990");
    }
    person.ChangeLastName(1973, "Sergeeva");
    for (int year : {1965, 1969}) {
      AssertEqual(person.GetFullName(year), "Polina with unknown last name", "Appolinaria (Polina) Sergeeva had no last name in 1965, 1969");
    }
    for (int year : {1970, 1972}) {
      AssertEqual(person.GetFullName(year), "Appolinaria with unknown last name", "Appolinaria (Polina) Sergeeva had no last name in 1970, 1972");
    }
}

void TestsOnlySurname()
{
    Person person;
    person.ChangeLastName(1965, "Sergeeva");

    for (int year : {1965, 1990}) {
      AssertEqual(person.GetFullName(year), "Sergeeva with unknown first name", "Sergeeva had no first name in 1965, 1990");
    }
    person.ChangeLastName(1970, "Volkova");
    for (int year : {1965, 1969}) {
      AssertEqual(person.GetFullName(year), "Sergeeva with unknown first name", "Volkova (Sergeeva) had no first name in 1965, 1969");
    }
    for (int year : {1970, 1990}) {
      AssertEqual(person.GetFullName(year), "Volkova with unknown first name", "Volkova (Sergeeva) had no first name in 1970, 1990");
    }
    person.ChangeFirstName(1973, "Polina");
    for (int year : {1965, 1969}) {
      AssertEqual(person.GetFullName(year), "Sergeeva with unknown first name", "Polina Volkova (Sergeeva) had no first name in 1965, 1969");
    }
    for (int year : {1970, 1972}) {
      AssertEqual(person.GetFullName(year), "Volkova with unknown first name", "Polina Volkova (Sergeeva) had no first name in 1970, 1972");
    }
}

void TestsInsertNamesInMiddleOfHistory()
{
    Person person;
      person.ChangeFirstName(1965, "Polina");
      person.ChangeLastName(1970, "Sergeeva");
      person.ChangeFirstName(1990, "Appolinaria");
      person.ChangeLastName(1985, "Volkova");

      person.ChangeFirstName(1975, "P");
      person.ChangeLastName(1980, "S");
      for (int year : {1970, 1974}) {
        AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
      }
      for (int year : {1975, 1979}) {
        AssertEqual(person.GetFullName(year), "P Sergeeva", "P Sergeeva");
      }
      for (int year : {1980, 1984}) {
        AssertEqual(person.GetFullName(year), "P S", "P S");
      }
      for (int year : {1985, 1989}) {
        AssertEqual(person.GetFullName(year), "P Volkova", "P Volkova");
      }
      for (int year : {1990, 2000}) {
        AssertEqual(person.GetFullName(year), "Appolinaria Volkova", "Appolinaria Volkova");
      }
}

void TestsInsertNamesInEndOfHistory()
{
    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1970, "Sergeeva");
    person.ChangeFirstName(1975, "P");
    person.ChangeLastName(1980, "S");
    for (int year : {1970, 1974}) {
      AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
    }
    for (int year : {1975, 1979}) {
      AssertEqual(person.GetFullName(year), "P Sergeeva", "P Sergeeva");
    }
    for (int year : {1980, 1990}) {
      AssertEqual(person.GetFullName(year), "P S", "P S");
    }

}
void TestsInsertNamesInBeginnigOfHistory()
{
    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1970, "Sergeeva");
    person.ChangeFirstName(1950, "P");
    person.ChangeLastName(1955, "S");
    for (int year : {1955, 1964}) {
      AssertEqual(person.GetFullName(year), "P S", "P S");
    }
    for (int year : {1965, 1969}) {
      AssertEqual(person.GetFullName(year), "Polina S", "Polina S");
    }
    for (int year : {1970, 1990}) {
      AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
    }
}

void TestsNameAndSurname()
{
      Person person;

      person.ChangeFirstName(1965, "Polina");
      person.ChangeLastName(1970, "Sergeeva");
      for (int year : {1970, 1990}) {
        AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva in 1967, 1990");
      }


      person.ChangeFirstName(1974, "Appolinaria");
      for (int year : {1970, 1973}) {
        AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva (before future last name changes) in 1967, 1973");
      }
      for (int year : {1974, 1980}) {
        AssertEqual(person.GetFullName(year), "Appolinaria Sergeeva", "Appolinaria Sergeeva (was Polina up to 1973) in 1974, 1980");
      }


      person.ChangeLastName(1972, "Volkova");
      for (int year : {1970, 1971}) {
        AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva (before future last name changes) in 1970, 1971");
      }
      for (int year : {1972, 1973}) {
        AssertEqual(person.GetFullName(year), "Polina Volkova", "Polina Volkova (before future first name changes) in 1972, 1973");
      }
      for (int year : {1974, 1980}) {
        AssertEqual(person.GetFullName(year), "Appolinaria Volkova", "Appolinaria Volkova in 1974, 1980");
      }

}

void TestsInsertOnlyNameChange()
{
    Person person;
    person.ChangeFirstName(1965, "Polina");
    person.ChangeLastName(1900, "Sergeeva");
    for (int year : {1965, 1979}) {
      AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
    }
    person.ChangeFirstName(1975, "P");


    for (int year : {1965, 1974}) {
      AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
    }
    for (int year : {1975, 1979}) {
      AssertEqual(person.GetFullName(year), "P Sergeeva", "P Sergeeva");
    }



     person.ChangeFirstName(1955, "Po");



     for (int year : {1955, 1964}) {
       AssertEqual(person.GetFullName(year), "Po Sergeeva", "Po Sergeeva");
     }
     for (int year : {1965, 1974}) {
       AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
     }
     for (int year : {1975, 1979}) {
       AssertEqual(person.GetFullName(year), "P Sergeeva", "P Sergeeva");
     }
}

void TestsInsertOnlySurnameChange()
{
    Person person;
    person.ChangeFirstName(1900, "Polina");
    person.ChangeLastName(1965, "Sergeeva");
    for (int year : {1965, 1979}) {
      AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
    }

    person.ChangeLastName(1975, "S");


    for (int year : {1965, 1974}) {
      AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
    }
    for (int year : {1975, 1979}) {
      AssertEqual(person.GetFullName(year), "Polina S", "Polina S");
    }


     person.ChangeLastName(1955, "Se");

     for (int year : {1955, 1964}) {
       AssertEqual(person.GetFullName(year), "Polina Se", "Polina Se");
     }
     for (int year : {1965, 1974}) {
       AssertEqual(person.GetFullName(year), "Polina Sergeeva", "Polina Sergeeva");
     }
     for (int year : {1975, 1979}) {
       AssertEqual(person.GetFullName(year), "Polina S", "Polina S");
     }
}
int main() {
  TestRunner runner;
    runner.RunTest(TestsIncognito, "TestsIncognito");
    runner.RunTest(TestsOnlyName, "TestsOnlyName");
    runner.RunTest(TestsOnlySurname, "TestsOnlySurname");
    runner.RunTest(TestsInsertNamesInMiddleOfHistory, "TestsInsertNamesInMiddleOfHistory");
    runner.RunTest(TestsInsertNamesInEndOfHistory, "TestsInsertNamesInEndOfHistory");
    runner.RunTest(TestsInsertNamesInBeginnigOfHistory, "TestsInsertNamesInBeginnigOfHistory");
    runner.RunTest(TestsNameAndSurname, "TestsNameAndSurname");
    runner.RunTest(TestsInsertOnlyNameChange, "TestsInsertOnlyNameChange");
    runner.RunTest(TestsInsertOnlySurnameChange, "TestsInsertOnlySurnameChange");

  // добавьте сюда свои тесты
  return 0;
}
