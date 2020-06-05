#pragma once

#ifndef DATE_H
#define DATE_H

#include <iostream>
#include <string>

using namespace std;

class Date {
public:

    Date(int new_year, int new_month, int new_day);

    inline int GetYear() const { return year;  }
    inline int GetMonth() const { return month; }
    inline int GetDay() const { return day; }
    operator string () const;
private:
    int year;
    int month;
    int day;
};

Date ParseDate(istream& in);

ostream& operator<<(ostream& out, const Date& date);

bool operator<(const Date& lhs, const Date& rhs);
bool operator<=(const Date& lhs, const Date& rhs);
bool operator==(const Date& lhs, const Date& rhs);
bool operator!=(const Date& lhs, const Date& rhs);
bool operator>=(const Date& lhs, const Date& rhs);
bool operator>(const Date& lhs, const Date& rhs);

#endif // DATE_H
