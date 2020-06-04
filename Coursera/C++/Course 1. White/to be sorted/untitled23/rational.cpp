#include <numeric>
#include <iostream>

class Rational {
    int p=0;
    int q=1;
    friend void Beautufy(Rational& dr);
public:
    Rational() {}
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
    if (dr.q<0) {dr.p *= -1; dr.q *= -1;}
}

Rational::Rational(int p, int q)
{
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
    return first * Rational(second.q, second.p);
}

std::ostream& operator<<(std::ostream& out, const Rational& d)
{
    return out << d.p << '/' << d.q;
}
std::istream& operator>>(std::istream& in, Rational& d)
{
    int p = d.Numerator(), q=d.Denominator();
    if (in)
    {
        in >> p;
        in.ignore(1);
        in >> q;
    }
    d = Rational(p, q);
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
