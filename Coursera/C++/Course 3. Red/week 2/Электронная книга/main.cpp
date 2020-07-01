#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

using namespace std;


class ReadingManager {
public:
  ReadingManager()
      : users_and_pages_(),
        rating (1001) {}

  void Read(int user_id, int page_count) {
    if (users_and_pages_.count(user_id) == 0) {
      AddUser(user_id);
    }
    int last_value=users_and_pages_[user_id];
    users_and_pages_[user_id] = page_count;

    for (int i=(last_value + 1); i<=page_count; ++i)
    {
        ++ (rating[i]);
    }
  }

  double Cheer(int user_id) const {
    if (users_and_pages_.count(user_id) == 0) {
      return 0;
    }
    const int user_count = GetUserCount();
    if (user_count == 1) {
      return 1;
    }
    const int page_count = users_and_pages_.at(user_id);

    return (user_count - rating[page_count]) * 1.0 / (user_count - 1);
  }

private:
  map<int, int> users_and_pages_; // позиции в векторе sorted_users_

  vector<int> rating;

  int GetUserCount() const {
      return users_and_pages_.size();
    }
  void AddUser(int user_id) {
    users_and_pages_[user_id] = 0;
  }

};


int main() {
  // Для ускорения чтения данных отключается синхронизация
  // cin и cout с stdio,
  // а также выполняется отвязка cin от cout
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  ReadingManager manager;

  int query_count;
  cin >> query_count;

  for (int query_id = 0; query_id < query_count; ++query_id) {
    string query_type;
    cin >> query_type;
    int user_id;
    cin >> user_id;

    if (query_type == "READ") {
      int page_count;
      cin >> page_count;
      manager.Read(user_id, page_count);
    } else if (query_type == "CHEER") {
      cout << setprecision(6) << manager.Cheer(user_id) << "\n";
    }
  }

  return 0;
}
