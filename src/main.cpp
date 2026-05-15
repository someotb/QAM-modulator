#include "../include/qamModulation.hpp"
#include "../include/agn.hpp"

#include <iostream>
#include <fstream>
#include <ctime>

int main()
{
    srand(time(nullptr));
    std::vector<uint8_t> bits;
    std::vector<uint8_t> decbits;
    std::vector<std::complex<float>> symb;
    std::vector<std::complex<float>> n_symb;
    std::ofstream BITS("data/bits.tsv");
    std::ofstream QPSK("data/QPSK.tsv");
    std::ofstream QAM16("data/QAM16.tsv");
    std::ofstream QAM64("data/QAM64.tsv");

    if (!BITS.is_open())
    {
        std::cerr << "Failed to open file BITS\n";
        return 1;
    }

    if (!QPSK.is_open())
    {
        std::cerr << "Failed to open file QPSK\n";
        return 1;
    }

    if (!QAM16.is_open())
    {
        std::cerr << "Failed to open file QAM16\n";
        return 1;
    }

    if (!QAM64.is_open())
    {
        std::cerr << "Failed to open file QAM64\n";
        return 1;
    }

    for (int i = 0; i < 1200; ++i)
    {
        uint8_t bit = rand() % 2;
        bits.push_back(bit);
        BITS << +bit << "\t";
    }

    for (int i = 0; i < 3; ++i)
    {
        if (i == 0)
        {
            QAMmodulation mod(ModType::QPSK);
            symb = mod.modulate_bits(bits);

            for (float j = 0.2; j < 20.0; j += 0.2)
            {
                float mx = 0.0f;
                float dx = j;
                float bit_err = 0.0f;
                GausseNoise agn(mx, dx);
                n_symb = agn.add_noise(symb);
                decbits = mod.demodulate_bits(n_symb);
                bit_err = mod.check_bits(bits, decbits);
                QPSK << bit_err << "\t";
            }
        }
        else if (i == 1)
        {
            QAMmodulation mod(ModType::QAM16);
            symb = mod.modulate_bits(bits);

            for (float j = 0.2; j < 20.0; j += 0.2)
            {
                float mx = 0.0f;
                float dx = j;
                float bit_err = 0.0f;
                GausseNoise agn(mx, dx);
                n_symb = agn.add_noise(symb);
                decbits = mod.demodulate_bits(n_symb);
                bit_err = mod.check_bits(bits, decbits);
                QAM16 << bit_err << "\t";
            }
        }
        else
        {
            QAMmodulation mod(ModType::QAM64);
            symb = mod.modulate_bits(bits);

            for (float j = 0.2; j < 20.0; j += 0.2)
            {
                float mx = 0.0f;
                float dx = j;
                float bit_err = 0.0f;
                GausseNoise agn(mx, dx);
                n_symb = agn.add_noise(symb);
                decbits = mod.demodulate_bits(n_symb);
                bit_err = mod.check_bits(bits, decbits);
                QAM64 << bit_err << "\t";
            }
        }
    }
    return 0;
}
