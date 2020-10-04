#include <iostream>
#include <cinttypes>
#include "deblur.hpp"



int main(int argc, char *argv[])
{
    constexpr std::string_view keys =
    "{input i inImg  |input.jpg    | input image name     }"
    "{r radius       |6            | radius               }"
    "{SNR snr        |2100         | signal to noise ratio}"
    "{output o outImg|output.jpg   | output image name    }"
    ;
    cv::CommandLineParser parser(argc, argv, std::string(keys));
    if (parser.has("help"))
    {
        parser.printMessage();
        return 1;
    }

    std::uint32_t r = parser.get<std::uint32_t>("r");
    std::uint32_t snr = parser.get<std::uint32_t>("SNR");

    //string, так как opencv не знает string_view
    std::string takeFromFile = parser.get<std::string>("input");
    std::string writeToFile = parser.get<std::string>("output");

    if (!parser.check())
    {
        parser.printErrors();
        return 0;
    }

    cv::Mat imgIn = imread(takeFromFile, cv::IMREAD_GRAYSCALE);
    if (imgIn.empty()) //проверка на прочтение файла
    {
        std::cerr << "ERROR : Image cannot be loaded.\n";
        return 1;
    }

    deconv::deblur filt(imgIn, r, snr);
    cv::Mat imgOut = filt.filter();

    imgOut.convertTo(imgOut, CV_8U);
    cv::normalize(imgOut, imgOut, 0, 255, cv::NORM_MINMAX);
    cv::imwrite(writeToFile, imgOut);
    return 0;
}
