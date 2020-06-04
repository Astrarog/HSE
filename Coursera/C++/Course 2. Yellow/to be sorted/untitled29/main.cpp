#include <iostream>

class A
{
public:
    A(int value = 5)
        : x(value)
    {

    }

    A(double z, std::string s = "abc", std::string t = "def")
        : x(15)
    {

    }

    A& operator=(const A& other)
    {
        std::cout << "AAA\n";
        x = other.x;
        return *this;
    }

    void f() throw();

    int operator+(const A& rhs)
    {
        return x + rhs.x;
    }

    int x;
};

class B : public A
{
    int y;
};

int main()
{
    A(1.1);
    A(10);

    B a, b;
    a + b;
    a = b;

    return 0;
}
