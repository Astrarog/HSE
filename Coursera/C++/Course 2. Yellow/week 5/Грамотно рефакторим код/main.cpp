#include <iostream>
#include <string>
#include <vector>

using namespace std;


class Person
{
public:
    Person(const string& name, const string& personType = "Person"): _Name(name), _PersonType (personType) {}

    virtual string TellAbout() const { return _PersonType+": "+_Name; }
    virtual void Walk(const string& destination) const {
        cout << this->TellAbout() << " walks to: " << destination << endl;
    }


    virtual ~Person() = default;
    Person(const Person&) = default;

public:
    const string _PersonType;
    const string _Name;



};

class Student: public Person {

public:

    Student(const string& name, const string& favouriteSong):
        Person(name, "Student"), _FavouriteSong(favouriteSong) {}

    void Walk(const string& destination) const override {
        Person::Walk(destination);
        cout << this->TellAbout() << " walks to: " << destination << endl;
        this->SingSong();
    }

    void Learn() const {
        cout << this->TellAbout() << " learns" << endl;
    }

    void SingSong() const {
        cout << this->TellAbout() << " sings a song: " << _FavouriteSong << endl;
    }

    virtual ~Student() override  = default;
    Student(const Student&) = default;

public:
     const string _FavouriteSong;
};


class Teacher: public Person {

public:

    Teacher(const string& name, const string& subject):
        Person(name, "Teacher"), _Subject(subject) {}

    void Teach() const
    {
        cout << this->TellAbout() << " teaches: " << _Subject << endl;
    }

    virtual ~Teacher() override  = default;
    Teacher(const Teacher&) = default;

public:
    const string _Subject;

};


class Policeman: public Person {
public:
    Policeman(const string& name): Person(name, "Policeman") {}


    void Check(const Person& person) const {
        cout << this->TellAbout() << " checks " << person._PersonType << ". " << person._PersonType
             << "'s name is: " << person._Name << endl;
    }
    virtual ~Policeman() override  = default;
    Policeman(const Policeman&) = default;
};


void VisitPlaces(const Person& person, vector<string> places) {
    for (auto place : places) {
        person.Walk(place);
    }
}


int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
