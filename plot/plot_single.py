"""
BoyerMoore or Naive or GalilSeiferas execution time
"""
import matplotlib.pyplot as plt

from plot_utils import generate_legend_label

text_lengths = [100000, 1000000, 10000000, 100000000]
pattern_lengths = [5, 10, 25, 50, 100, 300, 500, 750, 1000, 2500, 5000, 10000, 15000, 20000, 50000]

# Either boyer_moore, galil-seiferas or naive
algs = ['galil_seiferas']

for text_len in text_lengths:
    for alg in algs:
        with open('data/tpt/' + str(text_len) + alg + '.txt') as f:

            xs = []
            ys = []
            for line in f:
                s = line.split()[0].split(",")
                xs.append(int(s[0]))
                ys.append(float(s[1]))

            plt.plot([i for i in range(len(pattern_lengths))], ys, label=generate_legend_label(text_len))
            plt.xticks([i for i in range(len(pattern_lengths))], [generate_legend_label(i) for i in pattern_lengths])

plt.title("Alphabet size = 64")
plt.xlabel('Random Pattern length')
plt.tight_layout()
plt.ylabel('Execution time - log scale (microseconds)')
plt.yscale('log')
plt.legend(title="Random Text Length", loc='upper right')
plt.show()
