#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

#include "test_runner.h"

using namespace std;

template <class T>
class ObjectPool {
public:
  T* Allocate()
  {
      T* attempt = TryAllocate();
      if(attempt!=nullptr)
      {
          return attempt;
      }
      T* newObj = new T;
      all.insert(newObj);
      return newObj;
  }

  T* TryAllocate()
  {
      if(free.empty()){ return nullptr;}

      T* ret = free.front();
      free.pop();
      free_set.erase(ret);
      return ret;

  }

  void Deallocate(T* object)
  {
      if(object==nullptr){ return; }
      if(all.count(object)==0 || free_set.count(object)==1) { throw invalid_argument("error"); }
      free.push(object);
      free_set.insert(object);
  }

  ~ObjectPool()
  {
      for(T* obj: all)
      {
          delete obj;
      }
  }

private:
  queue<T*> free;
  set<T*> free_set;
  set<T*> all;
  // Добавьте сюда поля
};

void TestObjectPool() {
  ObjectPool<string> pool;

  auto p1 = pool.Allocate();
  auto p2 = pool.Allocate();
  auto p3 = pool.Allocate();

  *p1 = "first";
  *p2 = "second";
  *p3 = "third";

  pool.Deallocate(p2);
  ASSERT_EQUAL(*pool.Allocate(), "second");

  pool.Deallocate(p3);
  pool.Deallocate(p1);
  ASSERT_EQUAL(*pool.Allocate(), "third");
  ASSERT_EQUAL(*pool.Allocate(), "first");

  pool.Deallocate(p1);
}

int main() {
  TestRunner tr;
  RUN_TEST(tr, TestObjectPool);
  return 0;
}
