#include <iomanip>
#include <iostream>
#include <utility>
#include <queue>
#include <map>
#include <set>
#include <cstdint>

using namespace std;

class HotelManager {
public:
  HotelManager()
      {}
  void Book(int64_t time, const string& hotel_name, uint64_t client_id, size_t room_count)
  {
      current_time = time;

      clients_set[hotel_name].insert(client_id);
      clients_[hotel_name].push({time, {client_id, room_count}});

      count_rooms[hotel_name] += room_count;
      rooms_[hotel_name].push({time, room_count});

      clients_and_rooms[hotel_name][client_id] += room_count;
  }

  size_t Clients(const string& hotel_name)
  {
      if (clients_.count(hotel_name)==0)
      {
          return 0;
      }
      AdujustClients(hotel_name);
      return clients_set[hotel_name].size();
  }

  size_t Rooms(const string& hotel_name)
  {
      if (rooms_.count(hotel_name)==0)
      {
          return 0;
      }
      AdujustRooms(hotel_name);
      return count_rooms.at(hotel_name);
  }
private:

  void AdujustClients(const string& hotel_name)
  {
      if(clients_.count(hotel_name)==0)
      {
          return;
      }
      auto & hotel_queue = clients_[hotel_name];
      while (!(hotel_queue.empty()) && !(current_time - 86400 < hotel_queue.front().first))
      {
          uint64_t client = hotel_queue.front().second.first;
          size_t rooms = hotel_queue.front().second.second;
          clients_and_rooms[hotel_name][client] -= rooms;
          if (clients_and_rooms[hotel_name][client] == 0)
          {
              clients_set[hotel_name].erase(client);
          }
          hotel_queue.pop();
      }
  }

  void AdujustRooms(const string& hotel_name)
  {
      if(rooms_.count(hotel_name)==0)
      {
          return;
      }
      auto & hotel_queue = rooms_[hotel_name];
      while (!(hotel_queue.empty()) && !(current_time - 86400 < hotel_queue.front().first))
      {
          size_t rooms = hotel_queue.front().second;
          count_rooms[hotel_name] -= rooms;
          hotel_queue.pop();
      }
  }

  map<string, queue<pair<int64_t, pair<uint64_t, size_t>>>> clients_;
  map<string, queue<pair<int64_t, size_t>>> rooms_;
  int64_t current_time;
  map<string, size_t> count_rooms;
  map<string, set<uint64_t>> clients_set;
  map<string, map<uint64_t, size_t>> clients_and_rooms;

};


int main()
{
  ios::sync_with_stdio(false);
//  cin.tie(nullptr);

  HotelManager manager;

  size_t query_count;
  cin >> query_count;

  for (size_t query_id = 0; query_id < query_count; ++query_id)
  {
    string query_type;
    cin >> query_type;
    if (query_type == "BOOK")
    {
      int64_t time;
      cin >> time;

      string hotel_name;
      cin >> hotel_name;

      uint64_t client_id;
      cin >> client_id;

      size_t room_count;
      cin >> room_count;

      manager.Book(time, hotel_name, client_id, room_count);
    } else
    {
        string hotel_name;
        cin >> hotel_name;
        if (query_type == "CLIENTS")
        {
            cout << manager.Clients(hotel_name) << "\n";
        }
        else if(query_type == "ROOMS")
        {
            cout << manager.Rooms(hotel_name) << "\n";
        }
    }
  }

  return 0;
}
