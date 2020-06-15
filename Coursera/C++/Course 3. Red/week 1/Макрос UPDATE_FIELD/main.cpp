#include "airline_ticket.h"
#include "test_runner.h"

using namespace std;
bool operator< (const Date& lhs, const Date& rhs)
{
    return std::tie(lhs.year, lhs.month, lhs.day) < std::tie(rhs.year, rhs.month, rhs.day);
}

bool operator== (const Date& lhs, const Date& rhs)
{
    return std::tie(lhs.year, lhs.month, lhs.day) == std::tie(rhs.year, rhs.month, rhs.day);
}


bool operator< (const Time& lhs, const Time& rhs)
{
    return std::tie(lhs.hours, lhs.minutes) < std::tie(rhs.hours, rhs.minutes);
}

bool operator== (const Time& lhs, const Time& rhs)
{
    return std::tie(lhs.hours, lhs.minutes) == std::tie(rhs.hours, rhs.minutes);
}

ostream& operator<< (ostream& out, const Date& rhs)
{
    out << rhs.day << "." << rhs.month << "." << rhs.year;
    return out;
}

ostream& operator<< (ostream& out, const Time& rhs)
{
    out << rhs.hours << ":" << rhs.minutes;
    return out;
}

istream& operator>> (istream& in, Date& rhs)
{
    bool ok = true;
    char delim;
    ok = ok && (in >> rhs.year);
    ok = ok && (in.get(delim));
    ok = ok && (delim=='-');
    ok = ok && (in >> rhs.month);
    ok = ok && (in.get(delim));
    ok = ok && (delim=='-');
    ok = ok && (in >> rhs.day);
    return in;
}

istream& operator>> (istream& in, Time& rhs)
{
    bool ok = true;
    char delim;
    ok = ok && (in >> rhs.hours);
    ok = ok && (in.get(delim));
    ok = ok && (delim==':');
    ok = ok && (in >> rhs.minutes);
    return in;
}

#define UPDATE_FIELD(ticket, field, values) {   \
    map<string, string>::const_iterator it;     \
    it = values.find(#field);                   \
    if (it != values.end())                     \
    {                                           \
        istringstream is(it->second);           \
        is >> ticket.field;                     \
    }                                           \
}  // Реализуйте этот макрос, а также необходимые операторы для классов Date и Time

void TestUpdate() {
  AirlineTicket t;
  t.price = 0;

  const map<string, string> updates1 = {
    {"departure_date", "2018-2-28"},
    {"departure_time", "17:40"},
  };
  UPDATE_FIELD(t, departure_date, updates1);
  UPDATE_FIELD(t, departure_time, updates1);
  UPDATE_FIELD(t, price, updates1);

  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 0);

  const map<string, string> updates2 = {
    {"price", "12550"},
    {"arrival_time", "20:33"},
  };
  UPDATE_FIELD(t, departure_date, updates2);
  UPDATE_FIELD(t, departure_time, updates2);
  UPDATE_FIELD(t, arrival_time, updates2);
  UPDATE_FIELD(t, price, updates2);

  // updates2 не содержит ключей "departure_date" и "departure_time", поэтому
  // значения этих полей не должны измениться
  ASSERT_EQUAL(t.departure_date, (Date{2018, 2, 28}));
  ASSERT_EQUAL(t.departure_time, (Time{17, 40}));
  ASSERT_EQUAL(t.price, 12550);
  ASSERT_EQUAL(t.arrival_time, (Time{20, 33}));
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestUpdate);
}
