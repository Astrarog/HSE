#include <iostream>
#include <map>
#include <tuple>
#include <algorithm>
using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
  NEW,          // новая
  IN_PROGRESS,  // в разработке
  TESTING,      // на тестировании
  DONE          // завершена
};

using TasksInfo = map<TaskStatus, int>;

class TeamTasks {
    map<string, TasksInfo> data;
public:
  // Получить статистику по статусам задач конкретного разработчика
    const TasksInfo& GetPersonTasksInfo(const string& person) const
    {
        return data.at(person);
    }

  // Добавить новую задачу (в статусе NEW) для конкретного разработчитка
    void AddNewTask(const string& person)
    {
        ++data[person][TaskStatus::NEW];
    }

  // Обновить статусы по данному количеству задач конкретного разработчика,
  // подробности см. ниже
  tuple<TasksInfo, TasksInfo> PerformPersonTasks(
          const string& person, int task_count){
      try {
        TasksInfo current_tasks = data.at(person);
        TasksInfo updated, untouched=data.at(person);
        for(const auto& [key, value]:  data.at(person)){
            if (key == TaskStatus::DONE){
                continue;
            };
            int n_values = std::min<int>(value, task_count);

            current_tasks[key] -= n_values;
            untouched[key] -= n_values;

            auto next_key = static_cast<TaskStatus>(static_cast<int>(key)+1);
            current_tasks[next_key] +=n_values;
            updated[next_key] = n_values;
            task_count -= n_values;

        }
        data.at(person) = current_tasks;
        for (auto it = updated.begin(); it!=updated.end();) {
            if(it->second==0){
                it = updated.erase(it);
            }
            else{
                it=next(it);
            }
        }
        for (auto it = untouched.begin(); it!=untouched.end();) {
            if(it->second==0||it->first==TaskStatus::DONE){
                it = untouched.erase(it);
            }
            else{
                it=next(it);
            }
        }
        return tuple<TasksInfo, TasksInfo>(updated, untouched);
      } catch (std::out_of_range&) {
          return tuple<TasksInfo, TasksInfo>();
      }
  }
};

void PrintTasksInfo(TasksInfo tasks_info) {
  cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
      ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
      ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
      ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}


int main() {
  TeamTasks tasks;
  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Alice");
  }
  cout << "Alice's tasks: ";
  PrintTasksInfo(tasks.GetPersonTasksInfo("Alice"));

  TasksInfo updated_tasks, untouched_tasks;

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alice", 5);
  cout << "Updated Alice's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice's tasks: ";
  PrintTasksInfo(untouched_tasks);

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alice", 5);
  cout << "Updated Alice's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice's tasks: ";
  PrintTasksInfo(untouched_tasks);


  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alice", 1);
  cout << "Updated Alice's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice's tasks: ";
  PrintTasksInfo(untouched_tasks);

  for (int i = 0; i < 5; ++i) {
    tasks.AddNewTask("Alice");
  }

  tie(updated_tasks, untouched_tasks) =
      tasks.PerformPersonTasks("Alice", 2);
  cout << "Updated Alice's tasks: ";
  PrintTasksInfo(updated_tasks);
  cout << "Untouched Alice's tasks: ";
  PrintTasksInfo(untouched_tasks);


}

