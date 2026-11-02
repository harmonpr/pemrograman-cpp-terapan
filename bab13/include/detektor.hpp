// detektor.hpp - keluarga class detektor
#pragma once

#include <memory>
#include <string>
#include <vector>
#include <opencv2/core.hpp>

class Detektor {
public:
    Detektor(const std::string& nama, const cv::Scalar& garis);
    virtual ~Detektor() {}

    std::string nama() const;
    cv::Scalar warnaGaris() const;
    virtual bool cocok(const cv::Vec3b& p) const = 0;
    virtual std::string keterangan() const = 0;

private:
    std::string nama_;
    cv::Scalar garis_;
};

class DetektorWarna : public Detektor {
public:
    DetektorWarna(const std::string& nama, int r, int g, int b,
                  int toleransi);
    bool cocok(const cv::Vec3b& p) const override;
    std::string keterangan() const override;

private:
    int r_, g_, b_, tol_;
};

class DetektorTerang : public Detektor {
public:
    explicit DetektorTerang(int batas);
    bool cocok(const cv::Vec3b& p) const override;
    std::string keterangan() const override;

private:
    int batas_;
};

class DetektorGelap : public Detektor {
public:
    explicit DetektorGelap(int batas);
    bool cocok(const cv::Vec3b& p) const override;
    std::string keterangan() const override;

private:
    int batas_;
};

using DaftarDetektor = std::vector<std::unique_ptr<Detektor>>;
