#include "../include/qammodulation.hpp"
#include "../include/agn.hpp"

#include <iostream>

int main()
{
    std::vector<uint8_t> bits;
    std::vector<std::complex<float>> symb;
    std::vector<std::complex<float>> n_symb;
    for (int i = 0; i < 1000; ++i)
    {
        uint8_t bit = rand() % 2;
        bits.push_back(bit);
    }

    QAMmodulation qam(bits, ModType::QAM64);
    symb = qam.get_symb();

    float mx = 0.0f;
    float dx = 5.0f;
    GausseNoise agn(mx, dx);

    n_symb = agn.add_noise(symb);

    for (const auto &e : n_symb)
        std::cout << "Symbol: " << e << "\n";
}