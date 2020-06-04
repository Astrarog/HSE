#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <set>
using namespace std;
// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int year) {
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
}


string FindNameByYearWithHistory(const map<int, string>& names, int year) {
  vector<string> hist;
  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  string name;
  for (const auto& [key, value] : names) {
    // если очередной год не больше данного, обновляем имя
    if (key <= year) {
        if(!(name==value)){
            hist.push_back(value);
        }
        name = value;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }
  if (!(hist.size()<=1)){
    bool first_time = true;
    stringstream to_name;
    for (auto pos = next(hist.rbegin()); pos!=hist.rend(); pos=next(pos)){
        if(first_time){
            to_name << " (" << *pos;
            first_time = false;
        }
        else
        {
            to_name << ", " << *pos;
        }
    }
    to_name << ')';
    name+=to_name.str();
  }
  return name;
}



class Person {
public:
    Person() = delete;
    Person(string name, string surname, int year):
        first_names({{year, name}}), last_names({{year, surname}}), birthday_year(year) {}
  void ChangeFirstName(int year, const string& first_name) {
      if (year<birthday_year){
          return;
      }
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
      if (year<birthday_year){
          return;
      }
    last_names[year] = last_name;
  }
  string GetFullName(int year) const {
    if (year<birthday_year){
        return "No person";
    }
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

  string GetFullNameWithHistory(int year) const {
      if (year<birthday_year){
          return "No person";
      }
      const string first_name = FindNameByYearWithHistory(first_names, year);
      const string last_name = FindNameByYearWithHistory(last_names, year);

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
    // получить все имена и фамилии по состоянию на конец года year
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
  int birthday_year;
};


int main() {

  const Person person("Polina", "Sergeeva", 1960);
  for (int year : {1959, 1960}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

//  person.ChangeFirstName(1965, "Appolinaria");
//  person.ChangeLastName(1967, "Ivanova");
  for (int year : {1965, 1967}) {
    cout << person.GetFullNameWithHistory(year) << endl;
  }

  return 0;
}
