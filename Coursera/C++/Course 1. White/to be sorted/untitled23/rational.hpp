#ifndef RATIONAL_HPP
#define RATIONAL_HPP
#include <iostream>

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
#endif // RATIONAL_HPP
