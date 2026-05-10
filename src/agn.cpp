#include "../include/agn.hpp"

void GausseNoise::set_mx(float mx)
{
    _mx = mx;
    _distribution = std::normal_distribution(_mx, std::sqrt(_dx));
}

void GausseNoise::set_dx(float dx)
{
    _dx = dx;
    _distribution = std::normal_distribution(_mx, std::sqrt(_dx));
}

std::vector<std::complex<float>> GausseNoise::add_noise(const std::vector<std::complex<float>> &data)
{
    if (data.empty())
        throw std::invalid_argument("Data empty");

    std::vector<std::complex<float>> n_data(data.size());
    for (size_t i = 0; i < data.size(); ++i)
    {
        float re = _distribution(_generator);
        float im = _distribution(_generator);
        n_data[i] = data[i] + std::complex(re, im);
    }
    return n_data;
}
