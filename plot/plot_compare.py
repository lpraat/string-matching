"""
BoyerMoore vs Naive vs GalilSeiferas execution time
"""
import matplotlib.pyplot as plt

from plot_utils import generate_legend_label

text_lengths = [100000000]
pattern_lengths = [5, 10, 25, 50, 100, 300, 500, 750, 1000, 2500, 5000, 10000, 15000, 20000, 50000]

algs = ['boyer_moore', 'naive',  'galil_seiferas']

for text_len in text_lengths:
    for alg in algs:
        with open('data/tpt/' + str(text_len) + alg + '.txt') as f:

            xs = []
            ys = []
            for line in f:
                s = line.split()[0].split(",")
                xs.append(int(s[0]))
                ys.append(float(s[1]))

            plt.plot([i for i in range(len(pattern_lengths))], ys, label=alg)
            plt.xticks([i for i in range(len(pattern_lengths))], [generate_legend_label(i) for i in pattern_lengths])


plt.title("Alphabet size = 64, Random Text Length = 100M")
plt.xlabel('Random Pattern Length')
plt.tight_layout()
plt.ylabel('Execution time - log scale (microseconds)')
plt.yscale('log')
plt.legend(title="Text Length", loc='upper right')
plt.show()