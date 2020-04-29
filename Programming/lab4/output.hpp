#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <iostream>
#include <vector>

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& data)
{
//    out << '[';
    bool first = true;
    for (auto& elem: data)
    {
        if(!first)
        {
            out << ";";
        }
        first = false;
        out << elem;
    }
//    out << ']';
    return out;
}

#endif // OUTPUT_HPP
