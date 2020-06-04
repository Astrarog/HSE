#include <iostream>
#include <functional>
#include <vector>
#include <set>


std::set<int>::const_iterator FindNearestElement(
    const std::set<int>& numbers,
        int border)
{
    if(numbers.empty())
    {
        return end(numbers);
    }

    int left, right;
    left = right = 0;
    while((!numbers.count(border+left))&&(!numbers.count(border+right)))
    {
        --left;
        ++right;
    }
    auto test = numbers.count(border+left);
    if(test)
    {
        return numbers.find(border+left);
    } else
    {
        return numbers.find(border+right);
    }

}

int main()
{
    std::set<int> numbers = {1, 4, 6};
      std::cout <<
          *FindNearestElement(numbers, 0) << " " <<
          *FindNearestElement(numbers, 3) << " " <<
          *FindNearestElement(numbers, 5) << " " <<
          *FindNearestElement(numbers, 6) << " " <<
          *FindNearestElement(numbers, 100) << std::endl;

      std::set<int> empty_set;

      std::cout << (FindNearestElement(empty_set, 8) == end(empty_set)) << std::endl;
      return 0;
}
