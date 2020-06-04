#include <iostream>

using namespace std;

class Animal {
public:
    // ваш код
    Animal(const string& n): Name(n) {}
    const string Name;
};


class Dog: public Animal {
public:
    // ваш код
    Dog(const string& n): Animal(n){}
    void Bark() {
        cout << Name << " barks: woof!" << endl;
    }
};

//int main()
//{
//    Dog d("Mike");
//    d.Bark();
//    return 0;
//}
