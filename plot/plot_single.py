import matplotlib.pyplot as plt

text_lengths = [100000, 1000000, 10000000, 100000000]
pattern_lengths = [5, 10, 25, 50, 100, 300, 500, 750, 1000, 2500, 5000, 10000, 15000, 20000, 50000]

# Either boyer_moore, galil-seiferas or karp rabin
algs = ['galil_seiferas']


def generate_legend_label(i):

    if int(i) * 1e-6 >= 1:
        return str(int(i * 1e-6)) + "M"

    if int(i) * 1e-3 >= 1:
        return str(int(i * 1e-3)) + "k"

    return str(i)


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
plt.xlabel('Pattern length')
plt.tight_layout()
plt.ylabel('Execution time - log scale (microseconds)')
plt.yscale('log')
plt.legend(title="Text Length", loc='upper right')
plt.show()