/**
 * @file
 * @brief Содержит описание классов запаха, цветов, а так же инетрфейсов взаимодействия
 * @date May 2020
 */

#ifndef FLOWER_HPP
#define FLOWER_HPP
#include <string>
#include <cstdint>
#include <vector>
namespace flower {


    /**
     * @class aroma
     * @brief Класс типа запаха
     */
    enum class aroma
    {
        WEAK,
        MODERATE,
        STRONG
    };


    /**
     * @class color
     * @brief Класс, содержащий цвет в формате rgb
     */
    struct color
    {
        uint8_t r=0;
        uint8_t g=0;
        uint8_t b=0;
        color(){}
        color(uint32_t c);
        color(uint8_t r, uint8_t g, uint8_t b): r(r), g(g), b(b) {}
    };


    /**
     * @class flower
     * @brief Класс, содержащий имя цветка, его цвет, запах и место обитания.
     */
    class flower
    {
        std::string name;
        color rgb;
        aroma smell;
        std::string region;
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


    /**
     * @brief Генератор случайной строки
     * @param[in] length -- Длина генерируемой строки
     * @param[in] seed -- начальное значение для генератора случайных чисел
     * @return случайная строка
     */
    std::string random_string(std::string::size_type length, size_t& seed);

    /**
     * @brief Генератор случайного цвета
     * @param[in] seed -- начальное значение для генератора случайных чисел
     * @return случайный цвет
     */
    color random_color(size_t& seed);

    /**
     * @brief Генератор случайного запаха
     * @param[in] seed -- начальное значение для генератора случайных чисел
     * @return случайный запах
     */
    aroma random_aroma(size_t& seed);


    /**
     * @brief Генератор массива случайных цветков
     * @param[in] length -- Длина генерируемого массива
     * @param[in] seed -- начальное значение для генератора случайных чисел
     * @return массив случайных цветков
     */
    std::vector<flower> generate_flowers(size_t lenght, size_t& seed);

}

#endif // FLOWER_HPP
