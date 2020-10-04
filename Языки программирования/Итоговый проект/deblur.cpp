#include <cinttypes>
#include "deblur.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>

namespace deconv {

deblur::deblur() : R_(), SNR_(), imgBefore_(), PSF_(), Winner_() { }
deblur::deblur (const cv::Mat& img, std::uint32_t r, std::uint32_t snr) : R_(r), SNR_(snr) { imgBefore_ = img.clone();}

deblur::deblur (const deblur& other) : R_(other.R_), SNR_(other.SNR_), imgBefore_(other.imgBefore_), PSF_(other.PSF_), Winner_(other.Winner_) { }
deblur::deblur (deblur&& other): R_(std::move(other.R_)), SNR_(std::move(other.SNR_)), imgBefore_(std::move(other.imgBefore_)), PSF_(std::move(other.PSF_)), Winner_(std::move(other.Winner_))  {}
deblur& deblur::operator=(const deblur& other) {R_ = other.R_; SNR_=other.SNR_; PSF_=other.PSF_; Winner_=other.Winner_; imgBefore_=other.imgBefore_; imgAfter_=other.imgAfter_; return *this;}
deblur& deblur::operator=(deblur&& other) {R_ = std::move(other.R_); SNR_=std::move(other.SNR_); PSF_=std::move(other.PSF_); Winner_=std::move(other.Winner_); imgBefore_=std::move(other.imgBefore_); imgAfter_=std::move(other.imgAfter_); return *this;}

std::uint32_t deblur::get_r() const { return R_; }
std::uint32_t deblur::get_snr() const {return SNR_; }
cv::Mat deblur::get_img() const { return imgAfter_; }
cv::Mat deblur::get_img_filtered() const { return imgBefore_; }

deblur& deblur::set_r(std::uint32_t r) { R_=r; return *this; }
deblur& deblur::set_snr(std::uint32_t snr) { SNR_=snr; return *this; }
deblur& deblur::set_img(const cv::Mat& fromImg) { imgBefore_ = fromImg.clone(); return *this; }

deblur& deblur::calcPSF()
{
    // PFS needs even width and height
    std::uint32_t width = imgBefore_.cols, height = imgBefore_.rows;
    cv::Mat tmp(cv::Size(width, height), CV_32F, cv::Scalar(0));
    cv::Point point(width / 2, height / 2);
    cv::circle(tmp, point, R_, 255, -1 /*, 8*/);
    cv::Scalar summa = cv::sum(tmp);
    PSF_ = tmp / summa[0];
    return *this;
}


deblur& deblur::calcWinner()
{
    //fft shifts
    cv::Mat PSF_shifted = PSF_;
    {  // to delete tmps
         std::uint32_t cx = PSF_.cols / 2;
         std::uint32_t cy = PSF_.rows / 2;
         cv::Mat q0(PSF_shifted, cv::Rect(0, 0, cx, cy));
         cv::Mat q1(PSF_shifted, cv::Rect(cx, 0, cx, cy));
         cv::Mat q2(PSF_shifted, cv::Rect(0, cy, cx, cy));
         cv::Mat q3(PSF_shifted, cv::Rect(cx, cy, cx, cy));
         cv::Mat tmp;
         q0.copyTo(tmp);
         q3.copyTo(q0);
         tmp.copyTo(q3);
         q1.copyTo(tmp);
         q2.copyTo(q1);
         tmp.copyTo(q2);
    } // to delete tmps

    //cause Opencv Don't nkow how to work with std::array.
    cv::Mat planes [2] = { cv::Mat_<float>(PSF_shifted.clone()), cv::Mat::zeros(PSF_shifted.size(), CV_32F) };
    cv::Mat complexI;
    cv::merge(planes, 2, complexI);
    cv::dft(complexI, complexI);
    cv::split(complexI, planes);
    cv::Mat denom;
    cv::pow(cv::abs(planes[0]), 2, denom);
    denom += 1.0 / SNR_;
    cv::divide(planes[0], denom, Winner_);
    return *this;
}

cv::Mat deblur::filter(){
    calcPSF();
    calcWinner();
    imgBefore_(cv::Rect(0, 0, PSF_.cols, PSF_.rows));
    cv::Mat planes [2] = { cv::Mat_<float>(imgBefore_.clone()), cv::Mat::zeros(imgBefore_.size(), CV_32F) };
    cv::Mat complexI;
    cv::merge(planes, 2, complexI);
    cv::dft(complexI, complexI, cv::DFT_SCALE);
    cv::Mat planesH [2] = { cv::Mat_<float>(Winner_.clone()), cv::Mat::zeros(Winner_.size(), CV_32F) };
    cv::Mat complexH;
    cv::merge(planesH, 2, complexH);
    cv::Mat complexIH;
    cv::mulSpectrums(complexI, complexH, complexIH, 0);
    cv::idft(complexIH, complexIH);
    cv::split(complexIH, planes);
    imgAfter_ = planes[0];
    return imgAfter_;
}

}
