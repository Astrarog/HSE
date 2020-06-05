#include <memory>
#include <stdexcept>
#include <istream>
#include "condition_parser.h"
#include "token.h"
#include "node.h"

using namespace std;


shared_ptr<Node> ParseCondition(istream& is) {
  auto tokens = Tokenize(is);
  auto current = tokens.begin();
  auto top_node = ParseExpression(current, tokens.end(), 0u);

  if (!top_node) {
    top_node = make_shared<EmptyNode>();
  }

  if (current != tokens.end()) {
    throw logic_error("Unexpected tokens after condition");
  }

  return top_node;
}
