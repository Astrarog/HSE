#include "database.h"
#include "test_runner.h"
#include "condition_parser.h"

void TestDatabase() {
  istringstream empty_is("");
  auto empty_condition = ParseCondition(empty_is);
  auto empty_predicate = [empty_condition](const Date& date, const string& event) {
    return empty_condition->Evaluate(date, event);
  };

  // Add 2 - Del 1 - Add deleted again
  {
    Database db;
    Date d(2019, 1, 1);
    db.Add(d, "e1");
    db.Add(d, "e2");
    istringstream is(R"(event == "e1")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.RemoveIf(predicate), 1, "Db Add2-Del-Add 1");
    db.Add(d, "e1");
    AssertEqual(db.FindIf(empty_predicate).size(), 2, "Db Add2-Del-Add 2");
  }

  // Add
  {
    Database db;
    Date d(2019, 1, 1);
    db.Add(d, "e1");
    db.Add(d, "e1");
    istringstream is("date == 2019-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.FindIf(predicate).size(), 1, "Db Add Duplicates 1");
  }

  // Last
  {
    Database db;
    Date d(2019, 1, 1);
    Date d1(2019, 1, 2);
    Date d2(2018, 12, 22);
    db.Add(d1, "e1");
    db.Add(d2, "e2");
    AssertEqual(db.Last(d), "2018-12-22 e2", "Db Last 1");
    Date d3(2018, 12, 24);
    db.Add(d3, "e3");
    AssertEqual(db.Last(d), "2018-12-24 e3", "Db Last 2");

    // Get last event for date before first event
    try {
      Date d4(2017, 2, 2);
      db.Last(d4);
      Assert(false, "Db Last 3");
    } catch (invalid_argument e) {
      // Pass
    }

    // Delete event and get last
    istringstream is("date == 2018-12-24");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    db.RemoveIf(predicate);
    AssertEqual(db.Last(d), "2018-12-22 e2", "Db Last 4");

    AssertEqual(db.Last(d1), "2019-01-02 e1", "Db Last 5");
    db.Add(d2, "e4");
    AssertEqual(db.Last(d2), "2018-12-22 e4", "Db Last 6");
  }

  // Del
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date == 2018-01-07");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.RemoveIf(predicate), 2, "Db Del 1");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.RemoveIf(predicate), 4, "Db Del 2");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    AssertEqual(db.RemoveIf(empty_predicate), 4, "Db Del 3");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.RemoveIf(predicate), 1, "Db Del 4");
  }

  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1" OR date == 2019-01-01)");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.RemoveIf(predicate), 2, "Db Del 5");
  }

  // Find
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date == 2018-01-07");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.FindIf(predicate).size(), 2, "Db Find 1");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is("date >= 2018-01-07 AND date <= 2020-01-01");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.FindIf(predicate).size(), 4, "Db Find 2");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    AssertEqual(db.FindIf(empty_predicate).size(), 4, "Db Find 3");
  }
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1")");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.FindIf(predicate).size(), 1, "Db Find 4");
  }

  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    db.Add({2018, 1, 7}, "e3");
    db.Add({2018, 1, 7}, "e4");
    istringstream is(R"(event == "e1" OR date == 2019-01-01)");
    auto condition = ParseCondition(is);
    auto predicate = [condition](const Date& date, const string& event) {
      return condition->Evaluate(date, event);
    };
    AssertEqual(db.FindIf(predicate).size(), 2, "Db Find 5");
  }

  // Add - Del - Add - Del
  {
    Database db;
    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");

    db.Add({2019, 1, 1}, "e1");
    db.Add({2019, 1, 1}, "e2");
    AssertEqual(db.RemoveIf(empty_predicate), 2, "Db Add-Del-Add-Del 1");
  }
}
