#pragma once

#include <stdexcept>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:

  using Iterator = typename std::array<T, N>::iterator;
  using cIterator = typename std::array<T, N>::const_iterator;


  explicit StackVector(size_t a_size = 0)
    { if(! (a_size <= N)){throw std::invalid_argument("");}
        _size = a_size; }

  T& operator[](size_t index) { return _data[index]; }
  const T& operator[](size_t index) const { return _data.at(index); }

  Iterator begin() { return _data.begin(); }
  Iterator end() { return next(_data.begin(), _size); }
  cIterator begin() const { return _data.begin(); }
  cIterator end() const { return next(_data.begin(), _size); }

  size_t Size() const { return _size; }
  size_t Capacity() const { return N; }

  void PushBack(const T& value)
  {
      if(Size() == Capacity()){ throw std::overflow_error("");}
      _data[_size++] = value;
  }
  T PopBack()
  {
      if(Size() == 0){ throw std::underflow_error("");}
      return _data[(--_size)];
  }

private:
  std::array<T, N> _data;
  size_t _size;
};

