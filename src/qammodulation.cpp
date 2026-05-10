#include "../include/qammodulation.hpp"

void QAMmodulation::modulate_bits()
{
    if (bits.empty())
        throw std::invalid_argument("Data empty");

    switch (QAMmodulation::mod)
    {
    case ModType::QPSK:
        symb.resize(bits.size() / 2);
        for (size_t i = 0; i < bits.size() / 2; ++i)
        {
            int b0 = bits[2 * i];
            int b1 = bits[2 * i + 1];
            float re = 1.0f - 2.0f * b0;
            float im = 1.0f - 2.0f * b1;
            symb[i] = std::complex(re, im) / std::sqrt(2.0f);
        }
        break;
    
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
            symb[i] = std::complex(re, im) / std::sqrt(10.0f);
        }
        break;


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
            symb[i] = std::complex(re, im) / std::sqrt(42.0f);
        }
        break;
    
    default:
        throw std::invalid_argument("Invalid Mod Type");
    }
}