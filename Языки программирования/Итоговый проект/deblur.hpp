#ifndef DEBLUR_HPP
#define DEBLUR_HPP
#include <cinttypes>
#include<opencv2/opencv.hpp>

namespace deconv {

class deblur {
private:
    std::uint32_t R_;
    std::uint32_t SNR_;
    cv::Mat imgBefore_;
    cv::Mat imgAfter_;
    cv::Mat PSF_;
    cv::Mat Winner_;

    deblur& calcWinner();
    deblur& calcPSF();


public:
    deblur ();
    deblur (const cv::Mat&, std::uint32_t, std::uint32_t);
    deblur (const deblur&);
    deblur (deblur&&);
    ~deblur () = default;
    deblur& operator=(const deblur&);
    deblur& operator=(deblur&&);


    std::uint32_t get_r() const;
    std::uint32_t get_snr() const;
    cv::Mat get_img() const;
    cv::Mat get_img_filtered() const;

    deblur& set_r(std::uint32_t);
    deblur& set_snr(std::uint32_t);
    deblur& set_img(const cv::Mat&);

    cv::Mat filter();
};


}

#endif // DEBLUR_HPP
