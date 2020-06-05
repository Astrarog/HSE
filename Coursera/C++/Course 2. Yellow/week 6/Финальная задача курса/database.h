#pragma once

#ifndef DATABASE_H
#define DATABASE_H
#include <set>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <functional>
#include <utility>

#include "date.h"

class Database
{
    map<Date, pair<set<string>, vector<set<string>::iterator>>> database;

public:
    Database(){}
    void Add(const Date& date, const string& event);
    void Print(ostream& out) const;
    int RemoveIf(function<bool (const Date&, const string&)>);
    vector<string> FindIf(function<bool (const Date&, const string&)>) const;
    string Last(const Date& date) const;
};

void TestDatabase();

#endif // DATABASE_H
