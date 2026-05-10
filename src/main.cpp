#include "../include/qammodulation.hpp"

#include <iostream>

int main()
{
    std::vector<uint8_t> bits;
    std::vector<std::complex<float>> symb;
    for (int i = 0; i < 1000; ++i)
    {
        uint8_t bit = rand() % 2;
        bits.push_back(bit);
    }

    QAMmodulation qam(bits, ModType::QAM64);
    symb = qam.get_symb();

    for (const auto &e : symb)
        std::cout << "Symbol: " << e << "\n";
}