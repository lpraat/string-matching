"""
BoyerMoore execution time with varying alphabet size
"""
import matplotlib.pyplot as plt

from plot_utils import generate_legend_label

alphabet_lengths = [2, 4, 8, 16, 32, 64]
pattern_lengths = [5, 10, 25, 50, 100, 300, 500, 750, 1000, 2500, 5000, 10000, 15000, 20000, 50000]
algs = ['boyer_moore']

for alphabet_len in alphabet_lengths:
    for alg in algs:
        with open('data/alpha/' + str(alphabet_len) + alg + '.txt') as f:

            xs = []
            ys = []
            for line in f:
                s = line.split()[0].split(",")
                xs.append(int(s[0]))
                ys.append(float(s[1]))

            plt.plot([i for i in range(len(pattern_lengths))], ys, label=alphabet_len)
            plt.xticks([i for i in range(len(pattern_lengths))], [generate_legend_label(i) for i in pattern_lengths])


plt.title("Random Text Length = 100M")
plt.xlabel('Random Pattern Length')
plt.tight_layout()
plt.ylabel('Execution time - log scale (microseconds)')
plt.yscale('log')
plt.legend(title="Alphabet Size", loc='upper right')
plt.show()