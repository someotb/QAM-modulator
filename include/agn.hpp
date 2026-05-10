#pragma once

#include <random>
#include <complex>

class GausseNoise
{
private:
    float _mx;
    float _dx;
    std::mt19937 _generator;
    std::normal_distribution<float> _distribution;

public:
    float get_mx() { return _mx; }
    float get_dx() { return _dx; }
    void set_mx(float mx);
    void set_dx(float dx);
    std::vector<std::complex<float>> add_noise(const std::vector<std::complex<float>> &data);
    GausseNoise(float mx, float dx) : _mx(mx), _dx(dx), _generator(std::random_device{}()), _distribution(mx, std::sqrt(dx)) {};
    ~GausseNoise() = default;
};