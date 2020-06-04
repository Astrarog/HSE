#include <iostream>
#include <string>
#include <tuple>
#include <vector>

template <typename RandomIt>
RandomIt FindUpperBorder(RandomIt range_begin, RandomIt range_end,
                             const std::string& prefix)
{
    if (prefix.empty())
    {
        return range_begin;
    }
    if(range_begin==range_end)
    {
        return range_end;
    }
    std::string prefix_end = prefix;
    ++prefix_end[prefix_end.size()-1];
    if ((*(range_end-1))<=prefix_end)
    {
        return range_end;
    }


    RandomIt center = range_begin +(range_end - range_begin) / 2 ;
    while(range_end - range_begin > 1)
    {
        if ((*(center-1))<prefix_end)
        {
            if((*center)>=prefix_end)
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
                             const std::string& prefix)
{
    if(range_begin==range_end || prefix.empty())
    {
        return range_begin;
    }
    if ((*range_begin)>=prefix)
    {
        return range_begin;
    }

    RandomIt center = range_begin +(range_end - range_begin) / 2 ;
    while(range_end - range_begin > 1)
    {
        if ((*center)<prefix)
        {
            range_begin = center;
        }
        else
        {
           if((*(center-1))<prefix)
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
        const std::string& prefix)
{
    RandomIt upper = FindUpperBorder(range_begin, range_end, prefix);
    RandomIt lower = FindLowerBorder(range_begin, range_end, prefix);
    return {lower, upper};

}

using namespace std;

int main() {

      const vector<string> sorted_strings = {"aa", "aa", "aaa", "aaaa", "aaaaaaa", "aab", "zaaa", "zaab", "zab", "zzzz"};

      const auto m_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), "zzz");
      for (auto it = m_result.first; it != m_result.second; ++it) {
        cout << *it << " ";
      }
      cout << endl;

      const auto p_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), "zzz");
      cout << (p_result.first - begin(sorted_strings)) << " " <<
          (p_result.second - begin(sorted_strings)) << endl;

      const auto z_result =
          FindStartsWith(begin(sorted_strings), end(sorted_strings), "b");
      cout << (z_result.first - begin(sorted_strings)) << " " <<
          (z_result.second - begin(sorted_strings)) << endl;

    return 0;
}
