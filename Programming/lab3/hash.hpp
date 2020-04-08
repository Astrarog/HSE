#ifndef HASH_HPP
#define HASH_HPP
#include <cstdint>
#include <iterator>
#include <vector>
#include "flower.hpp"
namespace ral {


template <typename Collection, typename Usigned = std::uint32_t>
struct dummy_hash{
    using result_type = Usigned;
    using data_type = Collection;
    result_type value;

    dummy_hash(const Collection& data): value((*this)(data)){}
    operator result_type(){
        return value;
    }
    result_type operator()(const Collection& data){
        std::size_t n = std::size(data);
        Usigned hash = 0;
        for(std::size_t i=0; i<n-1; ++i)
        {
            hash ^= data[i];
            hash = hash<<1;
        }
        hash ^= data[n-1];
        return hash;
    }
};

template <typename Collection, typename Usigned = std::uint32_t>
struct smart_hash{
    using result_type = Usigned;
    using data_type = Collection;
    result_type value;
    smart_hash(const data_type& data): value((*this)(data)){}

    operator result_type(){
        return value;
    }
    result_type operator()(const data_type& data){
        std::size_t n = std::size(data);
        result_type hash = 0;
        result_type constant_even = 0xAA;
        result_type constant_odd = 0x55;

        for (std::size_t i=0; i < sizeof(result_type); ++i)
        {
            constant_even = (constant_even << 8) ^ 0xAA;
            constant_odd = (constant_odd << 8) ^ 0x55;
        }
        for(size_t i=0; i<n-1; ++i)
        {
            hash += data[i];
            if(data[i] % 2 == 0)
            {
                result_type even_values = constant_even & hash;
                hash = (even_values >> 2) ^ ((0x2 & even_values) << (sizeof(Usigned)-2));
            }
            else
            {
                result_type odd_values = constant_even & hash;
                hash = (odd_values >> 2) ^ ((0x2 & odd_values) << (sizeof(Usigned)-2));
            }
        }
        return hash;
    }
};

template<> struct dummy_hash<flower::flower>
{
    using result_type = std::uint32_t;
    using data_type = std::string;
    result_type value;
    dummy_hash(const flower::flower& data): value(dummy_hash<std::string>(data.GetName())){}
};

template<> struct smart_hash<flower::flower>
{
    using result_type = std::uint32_t;
    using data_type = std::string;
    result_type value;
    smart_hash(const flower::flower& data): value(smart_hash<std::string>(data.GetName())){}
};


template <typename T, typename U, template<typename, typename> typename Hasher>
class HashTable
{
    size_t capacity = sizeof(U);
    std::vector<T> elements;
    std::vector<U> hashes;
    HashTable(): elements(capacity), hashes(capacity){}


};


}


#endif // HASH_HPP
