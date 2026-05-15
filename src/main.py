import numpy as np
from matplotlib import pyplot as plt

with open("data/bits.tsv", "r") as f:
    BITS = np.array(f.read().strip().split("\t"), dtype=int)

with open("data/QPSK.tsv", "r") as f:
    QPSK_BIT_ERR = np.array(f.read().strip().split("\t"), dtype=float)

with open("data/QAM16.tsv", "r") as f:
    QAM16_BIT_ERR = np.array(f.read().strip().split("\t"), dtype=float)

with open("data/QAM64.tsv", "r") as f:
    QAM64_BIT_ERR = np.array(f.read().strip().split("\t"), dtype=float)

dx = np.arange(0.2, 20, 0.2)

plt.figure(label="Сгенерированные биты")
plt.plot(BITS, label="Bits")
plt.xlabel("Bits")
plt.ylabel("Bit value")

plt.figure(label="Зависимость вероятности ошибки на бит от дисперсии шума")
plt.plot(dx, QPSK_BIT_ERR, label="QPSK", marker="o")
plt.plot(dx, QAM16_BIT_ERR, label="QAM16", marker="o")
plt.plot(dx, QAM64_BIT_ERR, label="QAM64", marker="o")
plt.xlabel("Дисперсия шума")
plt.ylabel("Вероятность ошибки на бит")

plt.legend()
plt.show()
