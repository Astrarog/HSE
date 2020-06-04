#include <iostream>
#include <string>
#include <tuple>
#include <vector>

template <typename RandomIt>
RandomIt FindUpperBorder(RandomIt range_begin, RandomIt range_end,
                             char prefix)
{
    if(range_begin==range_end)
    {
        return range_end;
    }
    if ((*(range_end-1))[0]<=prefix)
    {
        return range_end;
    }
    RandomIt center = range_begin +(range_end - range_begin) / 2 ;
    while(range_end - range_begin > 1)
    {
        if ((*(center-1))[0]<=prefix)
        {
            if((*center)[0]>prefix)
            {
                return center;
            }
            else
            {
                range_begin = center;
            }
        }
        else
        {
            range_end = center;
        }
        center = range_begin +(range_end - range_begin) / 2 ;
    }
    return range_end-1;
}

template <typename RandomIt>
RandomIt FindLowerBorder(RandomIt range_begin, RandomIt range_end,
                             char prefix)
{
    if(range_begin==range_end)
    {
        return range_end;
    }
    if ((*range_begin)[0]>=prefix)
    {
        return range_begin;
    }
    RandomIt center = range_begin +(range_end - range_begin) / 2 ;
    while(range_end - range_begin > 1)
    {
        if ((*center)[0]<prefix)
        {
            range_begin = center;
        }
        else
        {
           if((*(center-1))[0]<prefix)
           {
               return  center;
           }
           else
           {
               range_end = center;
           }
        }
        center = range_begin +(range_end - range_begin) / 2 ;
    }
    return range_begin+1;

}


template <typename RandomIt>
std::pair<RandomIt, RandomIt> FindStartsWith(
    RandomIt range_begin, RandomIt range_end,
        char prefix)
{
    RandomIt upper = FindUpperBorder(range_begin, range_end, prefix);
    RandomIt lower = FindLowerBorder(range_begin, range_end, prefix);
    return {lower, upper};

}

using namespace std;

int main() {

      const vector<string> sorted_strings;// = {"a", "a", "d", "d"};

      const auto m_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), 'd');
      for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
      }
      cout << endl;

      const auto p_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), 'd');
      cout << (p_result.first - begin(sorted_strings)) << " " <<
          (p_result.second - begin(sorted_strings)) << endl;

      const auto z_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), 'z');
      cout << (z_result.first - begin(sorted_strings)) << " " <<
          (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}
