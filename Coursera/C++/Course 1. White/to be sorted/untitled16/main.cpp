#include <iostream>

using namespace std;

struct Specialization
{
    string s;
    explicit Specialization(const string& ss) {s = ss;}
};

struct Course
{
    string s;
    explicit Course(const string& ss){
        s = ss;
    }
};
struct Week
{
    string s;
     explicit Week(const string& ss) {s = ss;}
};


struct LectureTitle {

  string specialization;
  string course;
  string week;
  explicit LectureTitle(const Specialization& s, const Course& c,  const Week& w){
specialization = s.s;
course = c.s;
week = w.s;
  }
};


int main()
{
    cout << "Hello World!" << endl;
    return 0;
}
