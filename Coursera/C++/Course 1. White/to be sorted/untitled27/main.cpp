#include <iostream>
#include <stdexcept>

using namespace std;

string AskTimeServer();

class TimeServer {
public:
    string GetCurrentTime(){
        try {
            string to_write =  AskTimeServer();
            last_fetched_time = to_write;
            return last_fetched_time;
        } catch (system_error&) {
            return last_fetched_time;
        }
    }
private:
  string last_fetched_time = "00:00:00";
};


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
