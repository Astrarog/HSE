#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <cmath>
using namespace std;


class Figure
{
public:
    virtual string Name() = 0;
    virtual double Perimeter() = 0;
    virtual double Area() = 0;
};

class Rect : public Figure
{
private:
    double width;
    double height;
public:
    Rect(double width, double height): width(width), height(height) {}
    virtual string Name() override
    {
        return "RECT";
    }
    virtual double Perimeter() override
    {
        return 2*(width + height);
    }
    virtual double Area() override
    {
        return width*height;
    }
};

class Triangle : public Figure
{
private:
    double a;
    double b;
    double c;
public:
    Triangle(double a, double b, double c): a(a), b(b), c(c) {}
    virtual string Name() override
    {
        return "TRIANGLE";
    }
    virtual double Perimeter() override
    {
        return a+b+c;
    }
    virtual double Area() override
    {
        double p = Perimeter()/2;
        return sqrt(p*(p-a)*(p-b)*(p-c));
    }
};

class Circle : public Figure
{
private:
    double r;
public:
    Circle(double r): r(r) {}
    virtual string Name() override
    {
        return "CIRCLE";
    }
    virtual double Perimeter() override
    {
        // compiler do not support std::numbers::pi_v from <numbers>
        return 2*3.14*r;
    }
    virtual double Area() override
    {
        return 3.14*r*r;
    }
};



enum class FigType
{
    RECT,
    TRIA,
    CIRC
};

shared_ptr<Figure> CreateRect(istringstream& is)
{
    double width, height;
    is >> width >> height;
    return make_shared<Rect>(width, height);
}

shared_ptr<Figure> CreateTriangle(istringstream& is)
{
    double a, b, c;
    is >> a >> b >> c;
    return make_shared<Triangle>(a, b, c);
}

shared_ptr<Figure> CreateCircle(istringstream& is)
{
    double r;
    is >> r;
    return make_shared<Circle>(r);
}

shared_ptr<Figure> CreateFigure(istringstream& is, FigType type)
{
    switch(type)
    {
    case FigType::RECT:
        return CreateRect(is);
    case FigType::TRIA:
        return CreateTriangle(is);
    case FigType::CIRC:
        return CreateCircle(is);
    }
}

shared_ptr<Figure> CreateFigure(istringstream& is)
{
    string type;
    is >> type;

    FigType f;
    if(type=="RECT")
    {
        f = FigType::RECT;
    } else if(type=="TRIANGLE")
    {
        f = FigType::TRIA;
    } else if(type=="CIRCLE")
    {
        f = FigType::CIRC;
    }
    return CreateFigure(is, f);
}


int main() {
  vector<shared_ptr<Figure>> figures;
  for (string line; getline(cin, line); ) {
    istringstream is(line);

    string command;
    is >> command;
    if (command == "ADD") {
      figures.push_back(CreateFigure(is));
    } else if (command == "PRINT") {
      for (const auto& current_figure : figures) {
        cout << fixed << setprecision(3)
             << current_figure->Name() << " "
             << current_figure->Perimeter() << " "
             << current_figure->Area() << endl;
      }
    }
  }
  return 0;
}
