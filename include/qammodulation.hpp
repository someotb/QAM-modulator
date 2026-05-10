#pragma once

#include <vector>
#include <complex>
#include <cstdint>

enum class ModType
{
    QPSK,
    QAM16,
    QAM64,
};

class QAMmodulation
{
    private:
        std::vector<uint8_t> bits;
        std::vector<std::complex<float>> symb;
        ModType mod;
        void modulate_bits();

    public:
        void set_bits(std::vector<uint8_t> data) { bits = data; }
        std::vector<uint8_t> get_bits() { return bits; }
        std::vector<std::complex<float>> get_symb() { return symb; }
        QAMmodulation(std::vector<uint8_t> data, ModType modt) : bits(data), mod(modt) { modulate_bits(); }
        ~QAMmodulation() = default;
};