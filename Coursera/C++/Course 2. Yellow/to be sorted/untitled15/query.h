#ifndef QUERY_H
#define QUERY_H
#pragma once
#include <string>
#include <vector>
#include <istream>

enum class QueryType {
  NewBus,
  BusesForStop,
  StopsForBus,
  AllBuses
};

struct Query {
  QueryType type;
  std::string bus;
  std::string stop;
  std::vector<std::string> stops;
};

std::istream& operator >> (std::istream& is, Query& q);

#endif // QUERY_H
