#ifndef HASH_HPP
#define HASH_HPP
#include <cstdint>
#include <iterator>
#include <stdexcept>
#include <vector>

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
        result_type constant_even = 0xAA;
        result_type constant_odd = 0x55;

        for (std::size_t i=0; i < sizeof(result_type); ++i)
        {
            constant_even = (constant_even << 8) ^ 0xAA;
            constant_odd = (constant_odd << 8) ^ 0x55;
        }
        for(size_t i=0; i<n-1; ++i)
        {
            hash ^= data[i];
            result_type even_values = constant_even & hash;
            result_type odd_values = constant_odd & hash;
            switch (data[i] % 4) {
                case 0:
                    hash = (even_values >> 2) ^ ((0x2 & even_values) << (8*sizeof(Usigned)-2));
                    break;
                case 1:
                    hash = (odd_values >> 2) ^ ((0x2 & odd_values) << (8*sizeof(Usigned)-2));
                    break;
                case 2:
                    hash = (even_values << 2) ^
                            (((0x2<<(8*sizeof(Usigned)-2)) & even_values) >> (8*sizeof(Usigned)-2));
                    break;
                case 3:
                    hash = (odd_values << 2) ^
                        (((0x2<<(8*sizeof(Usigned)-2)) & odd_values) >> (8*sizeof(Usigned)-2));
                    break;
            }

        }
        return hash;
    }
};



template <typename Key, typename Value,
          template <typename, typename> typename Hasher = smart_hash,
          typename U=uint16_t>
class HashTable
{
    size_t capacity = (size_t(U(-1)));
    std::vector<Value> elements;
    std::vector<Key> keys;
    Key empty_key;
public:
    HashTable(): elements(capacity), keys(capacity){}

    Value& find_element_by_key(const Key& key)
    {
        U hash = Hasher<Key, U>(key);
        U ind = 1;

        while(ind!=0&&keys[hash]!=key)
        {
            ++hash;
        }
        return elements[hash];
    }

    Value& find_element_by_hash(U hash)
    {
                return elements[hash];
    }

    U insert_element(const Key& key, const Value& elem)
    {
        U hash = Hasher<Key, U>(key);
        U ind = 1;
        while(ind!=0&&keys[hash]!=empty_key)
        {
            ++hash;
        }
        if(ind==0&&keys[hash]!=empty_key)
        {
            throw std::length_error("Attemt to insert element into full table");
        }
        keys[hash] = key;
        elements[hash] = elem;
        return hash;
    }

};


}


#endif // HASH_HPP
