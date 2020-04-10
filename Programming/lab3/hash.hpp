#ifndef HASH_HPP
#define HASH_HPP
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <vector>
#include <list>
#include "flower.hpp"

namespace ral {


template <typename Collection, typename Usigned = std::uint16_t>
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



template <typename Collection, typename Usigned = std::uint16_t>
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

        for(size_t i=0; i<n-1; ++i)
        {
            hash += data[i];
            hash -= (hash << 13) | (hash >> 19);
        }
        return hash;
    }
};



template <typename Key, typename Value,
          template <typename, typename> typename Hasher = smart_hash,
          typename U=uint16_t>
class HashTable
{
    size_t capacity = (size_t(U(-1))+1);
    std::vector<std::list<Value>> elements;

public:

    size_t collisions_by_hash(U hash)
    {
        return elements[hash].size();
    }

    size_t collisions_by_key(const Key& key)
    {
        U hash = Hasher<Key, U>(key);
        return  elements[hash].size();
    }

    HashTable(): elements(capacity){}

    Value& find_element_by_key(const Key& key)
    {
        U hash = Hasher<Key, U>(key);
        for (Value& s: elements[hash])
        {
            if (s.getKey()==key){
                return s;
            }
        }
        Value empty_element;
        return empty_element;
    }



    U insert_element(const Value& elem)
    {
        U hash = Hasher<Value, U>(elem);
        elements[hash].push_back(elem);
        return hash;
    }

};


}


#endif // HASH_HPP
