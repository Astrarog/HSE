#include <vector>
#include <iostream>
#include <deque>
#include <algorithm>
#include <stdexcept>

#include "database.h"


using namespace std;


void Database::Add(const Date& date, const string& event)
{
    auto& [eventsOnDate, order] = this->database[date];
    if(eventsOnDate.count(event)==0)
    {
        auto position = eventsOnDate.insert(event);
        order.push_back(position.first);
    }
}

void Database::Print(ostream& out) const
{
    for (const auto& item : this->database) {
        for (const auto& event : item.second.second) {
            out << item.first << " " << (*event) << endl;
        }
    }
}


string Database::Last(const Date& date) const
{
    auto iter_after = this->database.upper_bound(date);
    string event;
    string eventDate;
    if (iter_after != this->database.begin())
    {
        auto& events = (--iter_after)->second.second;
        event = *(events[events.size()-1]);
        eventDate = (iter_after)->first;
    }

    if(event.size()==0)
    {
        throw invalid_argument("No entries");
    }
    return eventDate+" "+event;
}

vector<string> Database::FindIf(function<bool (const Date&, const string&)> condition) const
{
    vector<string> entries;
    for (const auto& item : this->database) {
        for (const auto& event : item.second.second) {
            if(condition(item.first, *event))
            {
                entries.push_back(string(item.first)+" "+(*event));
            }
        }
    }
    return entries;
}

int Database::RemoveIf(function<bool (const Date&, const string&)> condition)
{
    int removedAll=0;
    for (auto it = this->database.begin(); it != this->database.end(); )
    {
        auto& [date, events] = *it;
        int removed = events.second.size();
        auto newEnd = std::stable_partition(events.second.begin(), events.second.end(),
                                     [&, date=date ](const set<string>::iterator& event){ return !condition(date, *event);}
        );
        for(auto del = newEnd; del!=events.second.end();)
        {
            events.first.erase(*(del++));
        }
        events.second.erase(newEnd, events.second.end());
        removed -= events.second.size();
        removedAll += removed;
        if(events.second.size()==0)
        {
            this->database.erase(it++);
        }
        else
        {
            ++it;
        }
    }

    return removedAll;
}

