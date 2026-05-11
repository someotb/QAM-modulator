#include "../include/qamModulation.hpp"

std::vector<std::complex<float>> QAMmodulation::modulate_bits(const std::vector<uint8_t> &bits)
{
    if (bits.empty())
        throw std::invalid_argument("Data empty");

    std::vector<std::complex<float>> symb;

    switch (_mod)
    {
    case ModType::QPSK:
        symb.resize(bits.size() / 2);
        for (size_t i = 0; i < bits.size() / 2; ++i)
        {
            int b0 = bits[2 * i];
            int b1 = bits[2 * i + 1];

            float re = 1.0f - 2.0f * b0;
            float im = 1.0f - 2.0f * b1;

            symb[i] = std::complex<float>(re, im) / std::sqrt(2.0f);
        }
        return symb;

    case ModType::QAM16:
        symb.resize(bits.size() / 4);
        for (size_t i = 0; i < bits.size() / 4; ++i)
        {
            int b0 = bits[4 * i];
            int b1 = bits[4 * i + 1];
            int b2 = bits[4 * i + 2];
            int b3 = bits[4 * i + 3];

            float re = (1.0f - 2.0f * b0) * (2.0f * b1 + 1.0f);
            float im = (1.0f - 2.0f * b2) * (2.0f * b3 + 1.0f);

            symb[i] = std::complex<float>(re, im) / std::sqrt(10.0f);
        }
        return symb;

    case ModType::QAM64:
        symb.resize(bits.size() / 6);
        for (size_t i = 0; i < bits.size() / 6; ++i)
        {
            int b0 = bits[6 * i];
            int b1 = bits[6 * i + 1];
            int b2 = bits[6 * i + 2];
            int b3 = bits[6 * i + 3];
            int b4 = bits[6 * i + 4];
            int b5 = bits[6 * i + 5];

            float re = (1.0f - 2.0f * b0) * (4.0f * b1 + 2.0f * b2 + 1.0f);
            float im = (1.0f - 2.0f * b3) * (4.0f * b4 + 2.0f * b5 + 1.0f);

            symb[i] = std::complex<float>(re, im) / std::sqrt(42.0f);
        }
        return symb;

    default:
        throw std::invalid_argument("Invalid Mod Type");
    }
}

std::vector<uint8_t> QAMmodulation::demodulate_bits(const std::vector<std::complex<float>> &symb)
{
    if (symb.empty())
        throw std::invalid_argument("Data empty");

    std::vector<uint8_t> decbits;

    switch (_mod)
    {
    case ModType::QPSK:
        decbits.resize(symb.size() * 2);
        for (size_t i = 0; i < symb.size(); ++i)
        {
            float re = symb[i].real();
            float im = symb[i].imag();

            int b0 = re > 0.0f ? 0 : 1;
            int b1 = im > 0.0f ? 0 : 1;

            decbits[2 * i] = b0;
            decbits[2 * i + 1] = b1;
        }
        return decbits;

    case ModType::QAM16:
    {
        decbits.resize(symb.size() * 4);
        float sqrt10 = std::sqrt(10.0f);
        for (size_t i = 0; i < symb.size(); ++i)
        {
            float re = symb[i].real() * sqrt10;
            float im = symb[i].imag() * sqrt10;

            int b0 = (re < 0.0f) ? 1 : 0;
            int b1 = (std::abs(re) > 2.0f) ? 1 : 0;
            int b2 = (im < 0.0f) ? 1 : 0;
            int b3 = (std::abs(im) > 2.0f) ? 1 : 0;

            decbits[4 * i] = b0;
            decbits[4 * i + 1] = b1;
            decbits[4 * i + 2] = b2;
            decbits[4 * i + 3] = b3;
        }
        return decbits;
    }

    case ModType::QAM64:
    {
        decbits.resize(symb.size() * 6);
        float sqrt42 = std::sqrt(42.0f);
        for (size_t i = 0; i < symb.size(); ++i)
        {
            float re = symb[i].real() * sqrt42;
            float im = symb[i].imag() * sqrt42;
            float abs_re = std::abs(re);
            float abs_im = std::abs(im);

            int b0 = (re < 0.0f) ? 1 : 0;
            int b1 = (abs_re > 4.0f) ? 1 : 0;
            int b2 = ((abs_re > 2.0f) && (abs_re <= 6.0f)) ? 1 : 0;
            int b3 = (im < 0.0f) ? 1 : 0;
            int b4 = (abs_im > 4.0f) ? 1 : 0;
            int b5 = ((abs_im > 2.0f) && (abs_im <= 6.0f)) ? 1 : 0;

            decbits[6 * i] = b0;
            decbits[6 * i + 1] = b1;
            decbits[6 * i + 2] = b2;
            decbits[6 * i + 3] = b3;
            decbits[6 * i + 4] = b4;
            decbits[6 * i + 5] = b5;
        }
        return decbits;
    }

    default:
        throw std::invalid_argument("Invalid Mod Type");
    }
    return decbits;

}