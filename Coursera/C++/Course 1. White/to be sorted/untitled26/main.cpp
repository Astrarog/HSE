#include <numeric>
#include <iostream>
#include <stdexcept>

class Rational {
    int p=0;
    int q=1;
    friend void Beautufy(Rational& dr);
public:
    Rational(){}
    Rational(int numerator, int denominator);

    int Numerator() const {return p;}
    int Denominator() const {return q;}
    friend bool operator==(const Rational&, const Rational&);
    friend bool operator<(const Rational&, const Rational&);
    friend bool operator<=(const Rational&, const Rational&);
    friend bool operator>(const Rational&, const Rational&);
    friend bool operator>=(const Rational&, const Rational&);
    friend Rational operator+(const Rational&, const Rational&);
    friend Rational operator-(const Rational&, const Rational&);
    friend Rational operator/(const Rational&, const Rational&);
    friend Rational operator*(const Rational&, const Rational&);
    friend std::ostream& operator<<(std::ostream&, const Rational&);
    friend std::istream& operator>>(std::istream&, Rational&);
};


void Beautufy(Rational& dr)
{
    int gcd = std::gcd(dr.p, dr.q);
    dr.q = dr.q / gcd;
    dr.p = dr.p / gcd;
    if (dr.q<0) {dr.p = -dr.p; dr.q = -dr.q;}
}

Rational::Rational(int p, int q)
{
    if (q == 0) {
          throw std::invalid_argument("Invalid argument");
        }
    this->q = q;
    this->p = p;
    Beautufy(*this);
}


Rational operator+(const Rational& first, const Rational& second)
{
    int denom = std::lcm(first.q, second.q);
    int num = (first.p)*(denom/first.q) +(second.p)*(denom/second.q);
    return Rational(num, denom);
}

Rational operator-(const Rational& first, const Rational& second)
{
    int denom = std::lcm(first.q, second.q);
    int num = (first.p)*(denom/first.q) - (second.p)*(denom/second.q);
    return Rational(num, denom);
}

Rational operator*(const Rational& first, const Rational& second)
{
    int num = first.p * second.p;
    int denom = first.q * second.q;
    return Rational(num, denom);
}

Rational operator/(const Rational& first, const Rational& second)
{
    if (second.Numerator() == 0) {
          throw std::domain_error("Division by zero");
        }
    return first * Rational(second.q, second.p);
}

std::ostream& operator<<(std::ostream& out, const Rational& d)
{
    return out << d.p << '/' << d.q;
}
std::istream& operator>>(std::istream& in, Rational& d)
{
    if (!(in.eof()))
    {
        int p, q;
        in >> p;
        in.ignore(1);
        in >> q;
        d = Rational(p, q);
    }
    return in;
}

bool operator==(const Rational& first, const Rational& second)
{
    return first.p == second.p && first.q == second.q;
}

bool operator<(const Rational& first, const Rational& second)
{
    return (first-second).Numerator()<0;
}

bool operator>(const Rational& first, const Rational& second)
{
    return !(first==second || first< second);
}

bool operator<=(const Rational& first, const Rational& second)
{
    return first==second || first< second;
}

bool operator>=(const Rational& first, const Rational& second)
{
    return !(first< second);
}


using namespace std;

int main()
{
    try {
        Rational r1, r2;
        char operation;
        cin >> r1 >> operation >> r2;
        switch (operation) {
            case '+': cout << r1+r2 << endl; break;
            case '-': cout << r1-r2 << endl; break;
            case '*': cout << r1*r2 << endl; break;
            case '/': cout << r1/r2 << endl; break;
        }
    } catch (invalid_argument& e) {
        cout << e.what() << endl;
    } catch (domain_error& e) {
        cout << e.what() << endl;
    }
    return 0;
}
