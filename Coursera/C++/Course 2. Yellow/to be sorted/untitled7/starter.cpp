#include <string>
#include <iostream>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  string bus;
  string stop;
  vector<string> stops;
};

istream& operator >> (istream& is, Query& q) {
    string operation_code;
    is >> operation_code;
    QueryType q_type;
    if (operation_code == "NEW_BUS"){
        q_type=QueryType::NewBus;
        is >>  q.bus;
        int stop_count;
        is >> stop_count;
        q.stops.resize(stop_count);
        for (string& stop : q.stops) {
          is >> stop;
        }
    }
    else if (operation_code == "BUSES_FOR_STOP"){
        q_type=QueryType::BusesForStop;
        is >> q.stop;
    }
    else if (operation_code == "STOPS_FOR_BUS"){
        q_type=QueryType::StopsForBus;
        is >> q.bus;
    }
    else if (operation_code == "ALL_BUSES") {
        q_type=QueryType::AllBuses;
    }
    q.type = q_type;


    return is;
}

struct BusesForStopResponse {
    vector<string> busses;
    // Наполните полями эту структуру

};

ostream& operator << (ostream& os, const BusesForStopResponse& r) {

    if(r.busses.empty()){
      os << "No stop" << endl;
    } else {
      for (const string& bus : r.busses) {
        os << bus << " ";
      }
      os << endl;
    }
    return os;
}

struct StopsForBusResponse {
    string bus;
    vector<pair<string, vector<string>>> stops_for_buses;
    // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const StopsForBusResponse& r) {
    if (r.stops_for_buses.empty()) {
      os << "No bus" << endl;
    } else {
      bool first = true;
      for (const auto& stop_and_buses : r.stops_for_buses) {
            if (!first) {
              os << endl;
            }
            first = false;
            os << "Stop " << stop_and_buses.first << ":";
            if (stop_and_buses.second.size() == 1) {
              os << " no interchange";
            } else {
              for (const auto& bus : stop_and_buses.second) {
                if (bus != r.bus) {
                  os << " " << bus;
                }
              }
            }
          }
     }
    return os;
}

struct AllBusesResponse {
    map<string, vector<string>> buses_to_stops;
    // Наполните полями эту структуру
};

ostream& operator << (ostream& os, const AllBusesResponse& r) {
    if (r.buses_to_stops.empty()) {
      cout << "No buses" << endl;
    } else {
      for (const auto& bus_item : r.buses_to_stops) {
        cout << "Bus " << bus_item.first << ": ";
        for (const string& stop : bus_item.second) {
          cout << stop << " ";
        }
        cout << endl;
      }
    }

    // Реализуйте эту функцию
    return os;
}

class BusManager {
    map<string, vector<string>> buses_to_stops, stops_to_buses;
public:
    void AddBus(const string& bus, const vector<string>& stops) {
        buses_to_stops.insert(make_pair(bus, stops));
        for (const string& stop : stops) {
            stops_to_buses[stop].push_back(bus);
        }
        // Реализуйте этот метод
    }

    BusesForStopResponse GetBusesForStop(const string& stop) const {
        if(stops_to_buses.count(stop))
        {
            return BusesForStopResponse{vector<string>()};
        }
        else
        {
            return BusesForStopResponse{stops_to_buses.at(stop)};
        }
        // Реализуйте этот метод
    }

    StopsForBusResponse GetStopsForBus(const string& bus) const {
        vector<pair<string, vector<string>>> result;
        if(buses_to_stops.count(bus)){
            for (const auto& stop : buses_to_stops.at(bus)) {
                    result.push_back(make_pair(stop, stops_to_buses.at(stop)));
            }
        }
        // Реализуйте этот метод
        return  StopsForBusResponse{bus, result};
    }

    AllBusesResponse GetAllBuses() const {
        return AllBusesResponse{buses_to_stops};
      // Реализуйте этот метод
    }
};

// Не меняя тела функции main, реализуйте функции и классы выше

int main() {
  int query_count;
  Query q;

  cin >> query_count;

  BusManager bm;
  for (int i = 0; i < query_count; ++i) {
    cin >> q;
    switch (q.type) {
    case QueryType::NewBus:
      bm.AddBus(q.bus, q.stops);
      break;
    case QueryType::BusesForStop:
      cout << bm.GetBusesForStop(q.stop) << endl;
      break;
    case QueryType::StopsForBus:
      cout << bm.GetStopsForBus(q.bus) << endl;
      break;
    case QueryType::AllBuses:
      cout << bm.GetAllBuses() << endl;
      break;
    }
  }

  return 0;
}
