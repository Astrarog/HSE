#pragma once

#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <string>
#include <memory>

#include "date.h"

using namespace std;


enum struct Comparison
{
  Less,
  LessOrEqual,
  Greater,
  GreaterOrEqual,
  Equal,
  NotEqual
};

enum struct LogicalOperation
{
  Or,
  And
};


class Node
{
public:
    virtual bool Evaluate(const Date& date, const string& event) const = 0;
    virtual ~Node() {}
};

class EmptyNode: public Node
{
public:
    virtual inline bool Evaluate(const Date&, const string&) const override { return true;}

};


class DateComparisonNode: public Node
{
    Comparison _type;
    Date _value;
public:
    DateComparisonNode(Comparison type, const Date& date):
        _type(type), _value(date) {}
    virtual bool Evaluate(const Date& date, const string& event) const override;

};

class EventComparisonNode: public Node
{
    string _value;
    Comparison _type;
public:
    EventComparisonNode(Comparison type, const string& value):
    _value(value), _type(type) {}
    virtual bool Evaluate(const Date& date, const string& event) const override;
};


class LogicalOperationNode: public Node
{
    shared_ptr<Node> _left;
    shared_ptr<Node> _right;
    LogicalOperation _type;
public:
    LogicalOperationNode (LogicalOperation type,
                          shared_ptr<Node> left,
                          shared_ptr<Node> right):
    _left(left), _right(right), _type(type){}
    virtual bool Evaluate(const Date& date, const string& event) const override;

};



#endif // NODE_H
