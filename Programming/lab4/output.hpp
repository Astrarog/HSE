#ifndef OUTPUT_HPP
#define OUTPUT_HPP
#include <iostream>
#include <vector>


/**
 * @brief Функция вывода массива
 * @param[in] out -- поток вывода
 * @param[in] data -- массив значений
 * @return поток вывода
 */
template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& data)
{
//    out << '[';
    bool first = true;
    for (const auto& elem: data)
    {
        if(!first)
        {
            out << ';';
        }
        first = false;
        out << elem;
    }
//    out << ']';
    return out;
}

#endif // OUTPUT_HPP
