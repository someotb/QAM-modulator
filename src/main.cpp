#include "../include/qamModulation.hpp"
#include "../include/agn.hpp"

#include <iostream>

int main()
{
    std::vector<uint8_t> bits;
    std::vector<uint8_t> decbits;
    std::vector<std::complex<float>> symb;
    std::vector<std::complex<float>> n_symb;
    for (int i = 0; i < 1000; ++i)
    {
        uint8_t bit = rand() % 2;
        bits.push_back(bit);
    }

    QAMmodulation mod(ModType::QAM64);
    symb = mod.modulate_bits(bits);
    decbits = mod.demodulate_bits(symb);

    float mx = 0.0f;
    float dx = 0.6f;
    GausseNoise agn(mx, dx);

    n_symb = agn.add_noise(symb);

    std::cout << "First 10 bits vs decbits:\n";
    for (size_t i = 0; i < 10; ++i)
        std::cout << "Bit: " << +bits[i] << " | " << "Decbit: " << +decbits[i] << "\n";

    std::cout << "\nFirst 10 symbols:\n";
    for (size_t i = 0; i < 10; ++i)
        std::cout << "Symbols: " << n_symb[i] << "\n";
}