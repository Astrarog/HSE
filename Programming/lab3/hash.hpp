#ifndef HASH_HPP
#define HASH_HPP
#include <cstdint>
#include <array>

namespace ral {

template <typename Collection, typename Usigned = std::uint32_t>
struct dummy_hash{
    using result_type = Usigned;
    using data_type = Collection;
    result_type value;

    dummy_hash(Collection data): value(*this(data)){}
    operator result_type(){
        return value;
    }
    result_type operator()(Collection data){
        size_t n = std::size(data);
        Usigned hash = 0;
        for(size_t i=0; i<n-1; ++i)
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
    smart_hash(Collection data): value(*this(data)){}

    operator result_type(){
        return value;
    }
    result_type operator()(Collection data){
        size_t n = std::size(data);
        Usigned hash = 0;
        Usigned constant_even = 0xAA;
        Usigned constant_odd = 0x55;

        for (size_t i=0; i < sizeof(Usigned); ++i)
        {
            constant_even = (constant_even << 8) ^ 0xAA;
            constant_odd = (constant_odd << 8) ^ 0x55;
        }
        for(size_t i=0; i<n-1; ++i)
        {
            hash += data[i];
            if(data[i] % 2 == 0)
            {
                Usigned even_values = constant_even & hash;
                hash = (even_values >> 2) ^ ((0x2 & even_values) << (sizeof(Usigned)-2));
            }
            else
            {
                Usigned odd_values = constant_even & hash;
                hash = (odd_values >> 2) ^ ((0x2 & odd_values) << (sizeof(Usigned)-2));
            }
        }
        return hash;
    }
}

}


#endif // HASH_HPP
