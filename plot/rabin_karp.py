"""
RabinKarp1 vs RabinKarp2 vs RabinKarp3 execution time
"""
import matplotlib.pyplot as plt

from plot_utils import generate_legend_label

text_lengths = [100000]
pattern_lengths = [25, 50, 100, 300, 500]

algs = ['rabin_karp1', 'rabin_karp2', 'rabin_karp3']

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


plt.title("Alphabet size = 64, Text Length = 100k")
plt.xlabel('Random Pattern Length')
plt.tight_layout()
plt.ylabel('Execution time - log scale (milliseconds)')
plt.yscale('log')
plt.legend(title="Algorithm", loc='best')
plt.show()