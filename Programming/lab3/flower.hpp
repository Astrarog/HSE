#ifndef FLOWER_HPP
#define FLOWER_HPP
#include <string>
#include <cstdint>
#include <vector>
#include <cassert>
#include <stdexcept>
#include <functional>
#include "hash.hpp"

namespace flower {

    enum class aroma
    {
        WEAK,
        MODERATE,
        STRONG
    };

    struct color
    {
        uint8_t r=0;
        uint8_t g=0;
        uint8_t b=0;
        color(){}
        color(uint32_t c);
        color(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b) {}
    };


    class flower
    {
        std::string name;
        color rgb;
        aroma smell;
        std::string region;
        uint32_t hash;
        uint8_t delimeter = ' ';
    public:
        flower(){}
        flower(const std::string&, const color&, aroma, const std::string&);
        flower(const std::string&, const color&, int, const std::string&);

        std::string GetName() const { return name; }
        color GetColor() const { return rgb; }
        aroma GetSmell() const { return smell; }
        uint8_t GetDelimeter() const { return delimeter; }
        void SetDelimeter(uint8_t d) { delimeter = d;}
        std::string GetRegion() const { return region; }
        uint32_t GetHash() const { return hash; }
        friend std::istream& operator>>(std::istream& in, flower& flwr);
    };

    bool operator<(const color& firts, const color& second);
    bool operator==(const color& firts, const color& second);
    bool operator<=(const color& firts, const color& second);
    bool operator>(const color& firts, const color& second);
    bool operator>=(const color& firts, const color& second);
    std::ostream& operator<<(std::ostream& out, const color& rgb);
    std::istream& operator>>(std::istream& out, color& rgb);

    bool operator<(const flower& firts, const flower& second);
    bool operator==(const flower& firts, const flower& second);
    bool operator<=(const flower& firts, const flower& second);
    bool operator>(const flower& firts, const flower& second);
    bool operator>=(const flower& firts, const flower& second);
    std::ostream& operator<<(std::ostream& out, const flower& rgb);
    std::istream& operator>>(std::istream& out, flower& rgb);

    std::string random_string(std::string::size_type length, size_t& seed);
    color random_color(size_t& seed);
    aroma random_aroma(size_t& seed);
    flower random_flower(size_t& seed);

    template <template<typename ...> typename Collection>
    struct generate_flowers
    {
        using elem_type = flower;
        using val_type = Collection<flower>;
        val_type value;
        generate_flowers(size_t lenght, size_t& seed): value((*this)(lenght, seed)) {}

        operator val_type()
        {
            return value;
        }

        val_type operator()(size_t lenght, size_t& seed)
        {
            val_type answ;
            answ.reserve(lenght);

            while(lenght--)
            {
                answ.push_back(random_flower(seed));
            }

            return answ;
        }
    };

    template <template<typename, typename> typename Hasher>
    struct flower_hash_position
    {
        using Unsigned = uint32_t;
        flower fl;
        Unsigned hash;
        Unsigned position;
        flower_hash_position(const flower& flw): fl(flw)
        {
//            hash = Hasher<std::string, Unsigned>(flw.GetName());
//            position = hash;
        }
    };


}

#endif // FLOWER_HPP
