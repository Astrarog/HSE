#pragma once

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <stdexcept>
#include <istream>

#include "node.h"
#include "token.h"
#include "date.h"

using namespace std;

template <typename It>
shared_ptr<Node> ParseComparison(It& current, It end) {
  if (current == end) {
    throw logic_error("Expected column name: date or event");
  }

  Token& column = *current;
  if (column.type != TokenType::COLUMN) {
    throw logic_error("Expected column name: date or event");
  }
  ++current;

  if (current == end) {
    throw logic_error("Expected comparison operation");
  }

  Token& op = *current;
  if (op.type != TokenType::COMPARE_OP) {
    throw logic_error("Expected comparison operation");
  }
  ++current;

  if (current == end) {
    throw logic_error("Expected right value of comparison");
  }

  Comparison cmp;
  if (op.value == "<") {
    cmp = Comparison::Less;
  } else if (op.value == "<=") {
    cmp = Comparison::LessOrEqual;
  } else if (op.value == ">") {
    cmp = Comparison::Greater;
  } else if (op.value == ">=") {
    cmp = Comparison::GreaterOrEqual;
  } else if (op.value == "==") {
    cmp = Comparison::Equal;
  } else if (op.value == "!=") {
    cmp = Comparison::NotEqual;
  } else {
    throw logic_error("Unknown comparison token: " + op.value);
  }

  const string& value = current->value;
  ++current;

  if (column.value == "date") {
    istringstream is(value);
    return make_shared<DateComparisonNode>(cmp, ParseDate(is));
  } else {
    return make_shared<EventComparisonNode>(cmp, value);
  }
}

template <typename It>
shared_ptr<Node> ParseExpression(It& current, It end, unsigned precedence) {
  if (current == end) {
    return shared_ptr<Node>();
  }

  shared_ptr<Node> left;

  if (current->type == TokenType::PAREN_LEFT) {
    ++current; // consume '('
    left = ParseExpression<It>(current, end, 0u);
    if (current == end || current->type != TokenType::PAREN_RIGHT) {
      throw logic_error("Missing right paren");
    }
    ++current; // consume ')'
  } else {
    left = ParseComparison(current, end);
  }

  const map<LogicalOperation, unsigned> precedences = {
      {LogicalOperation::Or, 1}, {LogicalOperation::And, 2}
  };

  while (current != end && current->type != TokenType::PAREN_RIGHT) {
    if (current->type != TokenType::LOGICAL_OP) {
      throw logic_error("Expected logic operation");
    }

    const auto logical_operation = (current->value == "AND" ? LogicalOperation::And
                                                           : LogicalOperation::Or);
    const auto current_precedence = precedences.at(logical_operation);
    if (current_precedence <= precedence) {
      break;
    }

    ++current; // consume op

    left = make_shared<LogicalOperationNode>(
        logical_operation, left, ParseExpression(current, end, current_precedence)
    );
  }

  return left;
}

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();
