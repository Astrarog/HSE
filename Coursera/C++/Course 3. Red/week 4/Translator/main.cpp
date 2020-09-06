#include <string>
#include <vector>
#include <map>
#include <set>

#include "test_runner.h"

using namespace std;

class Translator {
public:
    void Add(string_view source, string_view target)
    {
        source = *(known_words_first.insert(string(source)).first);
        target = *(known_words_second.insert(string(target)).first);

        forward[source] = target;
        backward[target] = source;
    }
    string_view TranslateForward(string_view source) const
    {
        auto position = forward.find(source);
        if(position != forward.end())
        {
            return position->second;
        }
        return "";
    }
    string_view TranslateBackward(string_view target) const
    {
        auto position = backward.find(target);
        if(position != backward.end())
        {
            return position->second;
        }
        return "";
    }

private:
  set<string> known_words_first;
  set<string> known_words_second;
  map<string_view, string_view> forward;
  map<string_view, string_view> backward;
};

void TestSimple() {
  Translator translator;
  translator.Add(string("okno"), string("window"));
  translator.Add(string("stol"), string("table"));

  ASSERT_EQUAL(translator.TranslateForward("okno"), "window");
  ASSERT_EQUAL(translator.TranslateBackward("table"), "stol");
  ASSERT_EQUAL(translator.TranslateBackward("stol"), "");
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestSimple);
  return 0;
}
