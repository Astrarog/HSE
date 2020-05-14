/**
  * @file
  * @brief Содержит реализации функций, описанных в flower.hpp
  */
#include <cassert>
#include <tuple>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include "flower.hpp"

namespace flower {
    color::color(uint32_t c){
        r = static_cast<uint8_t>(c / 256 / 256);
        g = static_cast<uint8_t>((c / 256) % 256);
        b = static_cast<uint8_t>(c % 256);
    }

    bool operator<(const color& firts, const color& second)
    {
        return 256*256*firts.r + 256*firts.g + firts.b < 256*256*second.r + 256*second.g + second.b;
    }
    bool operator==(const color& firts, const color& second)
    {
        return firts.r==second.r && firts.g==second.g && firts.b==second.b;
    }
    bool operator!=(const color& firts, const color& second)  { return !(firts == second);}
    bool operator<=(const color& firts, const color& second) { return firts<second || firts==second;}
    bool operator>(const color& firts, const color& second) { return !(firts<=second);}
    bool operator>=(const color& firts, const color& second) { return firts>second || firts==second;}

    std::ostream& operator<<(std::ostream& out, const color& rgb)
    {
        out << '#'  << std::hex << std::uppercase << std::right << std::setw(2) << std::setfill('0');
        out << int(rgb.r);
        out << std::setw(2) << std::setfill('0') << int(rgb.g);
        out << std::setw(2) << std::setfill('0') << int(rgb.b);
        out << std::dec;
        return out;
    }


    bool checkHex(uint8_t x)
    {
       return (x>='0' && x<='9')||(x>='A' && x<='F');
    }

    uint8_t parseHex(uint8_t f, uint8_t s){
        f = f>='0'&&f<='9'?f-'0':(f-'A')+10;
        s = s>='0'&&s<='9'?s-'0':(s-'A')+10;
        return f*16 + s;
    }

    std::istream& operator>>(std::istream& input, color& rgb)
    {
        std::string format;
        input >> format;
        std::istringstream in(format);
        bool parse_is_good = true;
        uint8_t stratring_char=0;
        parse_is_good = parse_is_good && (in >> stratring_char);
        parse_is_good = parse_is_good && (stratring_char == '#');


        color to_rgb;
        uint8_t f=0, s=0;
        parse_is_good = parse_is_good && (in >> f);
        f = uint8_t(std::toupper(f));
        parse_is_good = parse_is_good && (checkHex(f));

        parse_is_good = parse_is_good && (in >> s);
        s = uint8_t(std::toupper(s));
        parse_is_good = parse_is_good && (checkHex(s));
        to_rgb.r = parseHex(f, s);

        f=0; s=0;
        parse_is_good = parse_is_good && (in >> f);
        f = uint8_t(std::toupper(f));
        parse_is_good = parse_is_good && (checkHex(f));

        parse_is_good = parse_is_good && (in >> s);
        s = uint8_t(std::toupper(s));
        parse_is_good = parse_is_good && (checkHex(s));
        to_rgb.g = parseHex(f, s);

        f=0; s=0;
        parse_is_good = parse_is_good && (in >> f);
        f = uint8_t(std::toupper(f));
        parse_is_good = parse_is_good && (checkHex(f));

        parse_is_good = parse_is_good && (in >> s);
        s = uint8_t(std::toupper(s));
        parse_is_good = parse_is_good && (checkHex(s));
        to_rgb.b = parseHex(f, s);
        in.peek();
        parse_is_good = parse_is_good && in.eof();

        if (!parse_is_good){
            throw std::logic_error("Wrong color format: "+format);
        }
        rgb = to_rgb;
        return input;
    }

    flower::flower(const std::string& n, const color& c, aroma a, const std::string& r): name(n), rgb(c), smell(a), region(r){}

    flower::flower(const std::string& n, const color& c, int a, const std::string& r)
    {
        assert(a>=0&&a<=2);
        if (!(a>=0 && a<=2))
        {
            throw std::domain_error("Aroma should be 0, 1 or 2");
        }
        aroma smell = static_cast<aroma>(a);
        flower(n, c, smell, r);
    }

    bool operator<(const flower& firts, const flower& second)
    {
        return std::tuple(firts.GetName(), firts.GetColor(), firts.GetSmell(), firts.GetRegion())
                < std::tuple(second.GetName(), second.GetColor(), second.GetSmell(), second.GetRegion());
    }

    bool operator==(const flower& firts, const flower& second)
    {
        return std::tuple(firts.GetName(), firts.GetColor(), firts.GetSmell(), firts.GetRegion()) ==
                std::tuple(second.GetName(), second.GetColor(), second.GetSmell(), second.GetRegion());
    }
    bool operator!=(const flower& firts, const flower& second) { return !(firts == second);}
    bool operator<=(const flower& firts, const flower& second) { return firts<second || firts==second;}
    bool operator>(const flower& firts, const flower& second) { return !(firts<=second);}
    bool operator>=(const flower& firts, const flower& second) { return firts>second || firts==second;}

    std::ostream& operator<<(std::ostream& out, const flower& flwr)
    {
        uint8_t d = flwr.GetDelimeter();
        out << flwr.GetName() << d << flwr.GetColor() << d;
        out << static_cast<int>(flwr.GetSmell()) << d << flwr.GetRegion();
        return out;
    }

    std::istream& operator>>(std::istream& input, flower& flwr)
    {
        std::string format;
        std::getline(input, format, '-');

        std::istringstream in(format);

        char d = flwr.GetDelimeter();

        std::string name, smell_str, rgb_str, region;
        int smell=0;
        color rgb;

        bool parse_is_good = true;

        std::getline(in, name, d);
        parse_is_good = parse_is_good && (in);

        std::getline(in, rgb_str, d);
        std::istringstream rgb_stream(rgb_str);
        parse_is_good = parse_is_good &&(rgb_stream >> rgb);

        std::getline(in, smell_str, d);
        std::istringstream smell_stream(smell_str);
        parse_is_good = parse_is_good &&(smell_stream >> smell);

        std::getline(in, region);
        parse_is_good = parse_is_good &&(in);
        parse_is_good = parse_is_good && in.eof();


        if (!parse_is_good){
            throw std::logic_error("Wrong flower format: "+format);
        }

        flower to_flower(name, rgb, smell, region);

        flwr = to_flower;
        return input;
    }


    std::string random_string(std::string::size_type length, size_t& seed)
    {
        static auto& chrs = "0123456789"
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        ++seed;
        thread_local static std::mt19937 rg(seed);
        thread_local static std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

        std::string s;

        s.reserve(length);

        while(length--){
            s += chrs[pick(rg)];
        }

        return s;
    }

    color random_color(size_t& seed)
    {
        ++seed;
        thread_local static std::mt19937 rg(seed);
        thread_local static std::uniform_int_distribution<uint8_t> pick(0, 255);

        return color(pick(rg), pick(rg), pick(rg));

    }

    aroma random_aroma(size_t& seed)
    {
        ++seed;
        thread_local static std::mt19937 rg(seed);
        thread_local static std::uniform_int_distribution<uint8_t> pick(0, 2);

        return static_cast<aroma>(pick(rg));

    }

    flower random_flower(size_t& seed)
    {
        ++seed;
        thread_local static std::mt19937 rg(seed);
        thread_local static std::uniform_int_distribution<std::string::size_type> pick(3, 20);

        std::string name = random_string(pick(rg), seed);
        color clr = random_color(seed);
        aroma smell = random_aroma(seed);
        std::string region = random_string(pick(rg), seed);

        return flower(name, clr, smell, region);

    }



}
