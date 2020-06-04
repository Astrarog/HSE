#ifndef RESPONSES_H
#define RESPONSES_H
#pragma once
#include <string>
#include <vector>
#include <map>
#include <tuple>
#include <ostream>

struct BusesForStopResponse {
  std::vector<std::string> buses;
};

struct StopsForBusResponse {
  std::string bus;
  std::vector<std::pair<std::string, std::vector<std::string>>> stops_for_buses;
};

struct AllBusesResponse {
  std::map<std::string, std::vector<std::string>> buses_to_stops;
};


std::ostream& operator << (std::ostream& os, const BusesForStopResponse& r);

std::ostream& operator << (std::ostream& os, const StopsForBusResponse& r);

std::ostream& operator << (std::ostream& os, const AllBusesResponse& r) ;

#endif // RESPONSES_H
