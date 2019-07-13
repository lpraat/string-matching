import matplotlib.pyplot as plt

alphabet_lengths = [2, 64]
pattern_lengths = [5, 10, 25, 50, 100, 300, 500, 750, 1000, 2500, 5000, 10000, 15000, 20000, 50000]
algs = ['boyer_moore_simple', 'boyer_moore']


def generate_legend_label(i):

    if int(i) * 1e-6 >= 1:
        return str(int(i * 1e-6)) + "M"

    if int(i) * 1e-3 >= 1:
        return str(int(i * 1e-3)) + "k"

    return str(i)


for alphabet_len in alphabet_lengths:
    for alg in algs:
        with open('data/diff/' + str(alphabet_len) + alg + '.txt') as f:

            xs = []
            ys = []
            for line in f:
                s = line.split()[0].split(",")
                xs.append(int(s[0]))
                ys.append(float(s[1]))

            plt.plot([i for i in range(len(pattern_lengths))], ys, label=alg + "-" + str(alphabet_len))
            plt.xticks([i for i in range(len(pattern_lengths))], [generate_legend_label(i) for i in pattern_lengths])


plt.title("Random Text size = 100M")
plt.xlabel('Random Pattern length')
plt.tight_layout()
plt.ylabel('Execution time - log scale (microseconds)')
plt.yscale('log')
plt.legend(title="Algorithm-Alphabet Size", loc='upper right')
plt.show()