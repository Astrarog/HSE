#include "node.h"


using namespace std;


bool DateComparisonNode::Evaluate(const Date& date, const string& event) const
{
    switch (this->_type) {
    case Comparison::Less:
        return date < this->_value;
    case Comparison::LessOrEqual:
        return date <= this->_value;
    case Comparison::Greater:
        return date > this->_value;
    case Comparison::GreaterOrEqual:
        return date >= this->_value;
    case Comparison::Equal:
        return date == this->_value;
    case Comparison::NotEqual:
        return date != this->_value;
    }
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const
{
    switch (this->_type) {
    case Comparison::Less:
        return event < this->_value;
    case Comparison::LessOrEqual:
        return event <= this->_value;
    case Comparison::Greater:
        return event > this->_value;
    case Comparison::GreaterOrEqual:
        return event >= this->_value;
    case Comparison::Equal:
        return event == this->_value;
    case Comparison::NotEqual:
        return event != this->_value;
    }
}


bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const
{
    switch (this->_type) {
    case LogicalOperation::Or:
        return this->_right->Evaluate(date, event) || this->_left->Evaluate(date, event);
    case LogicalOperation::And:
        return this->_right->Evaluate(date, event) && this->_left->Evaluate(date, event);

    }
}

