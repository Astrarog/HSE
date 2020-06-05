#include <sstream>
#include <iomanip>
#include <vector>

#include "date.h"

using namespace std;

Date::Date(int new_year, int new_month, int new_day)
{
    year = new_year;
    if (new_month > 12 || new_month < 1) {
        throw logic_error("Month value is invalid: " + to_string(new_month));
    }
    month = new_month;
    if (new_day > 31 || new_day < 1) {
        throw logic_error("Day value is invalid: " + to_string(new_day));
    }
    day = new_day;
}

Date ParseDate(istream& date_stream)
{
    bool ok = true;

    int year;
    ok = ok && (date_stream >> year);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int month;
    ok = ok && (date_stream >> month);
    ok = ok && (date_stream.peek() == '-');
    date_stream.ignore(1);

    int day;
    ok = ok && (date_stream >> day);
//    ok = ok && date_stream.eof();

    if (!ok) {
        throw logic_error("Wrong date format");
    }
    return Date(year, month, day);
}

ostream& operator<<(ostream& stream, const Date& date)
{
  stream << setw(4) << setfill('0') << date.GetYear()  <<
     "-" << setw(2) << setfill('0') << date.GetMonth() <<
     "-" << setw(2) << setfill('0') << date.GetDay();
  return stream;
}

Date::operator string () const
{
    stringstream out("");
    out << *this;

    string date;
    getline(out, date);
    return date;
}

bool operator<(const Date& lhs, const Date& rhs)
{
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator<=(const Date& lhs, const Date& rhs)
{
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <=
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator==(const Date& lhs, const Date& rhs)
{
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} ==
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator!=(const Date& lhs, const Date& rhs)
{
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} !=
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>=(const Date& lhs, const Date& rhs)
{
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >=
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

bool operator>(const Date& lhs, const Date& rhs)
{
  return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} >
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}
