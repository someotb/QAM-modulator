#pragma once

#include "modulationType.hpp"

#include <vector>
#include <complex>
#include <cstdint>

class QAMmodulation
{
private:
    ModType _mod;

public:
    ModType get_mod() { return _mod; }
    void set_mod(ModType mod) { _mod = mod; }
    std::vector<std::complex<float>> modulate_bits(const std::vector<uint8_t> &bits);
    std::vector<uint8_t> demodulate_bits(const std::vector<std::complex<float>> &symb);
    QAMmodulation(ModType modt) : _mod(modt) {};
    ~QAMmodulation() = default;
};