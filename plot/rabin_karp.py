import matplotlib.pyplot as plt

text_lengths = [100000]
pattern_lengths = [25, 50, 100, 300, 500]

algs = ['rabin_karp1', 'rabin_karp2', 'rabin_karp3']


def generate_legend_label(i):

    if int(i) * 1e-6 >= 1:
        print(i * 1e-6)
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

            plt.plot([i for i in range(len(pattern_lengths))], ys, label=alg)
            plt.xticks([i for i in range(len(pattern_lengths))], [generate_legend_label(i) for i in pattern_lengths])


plt.title("Alphabet size = 64, Text Size = 100k, Rabin karp")
plt.xlabel('Pattern length')
plt.tight_layout()
plt.ylabel('Execution time - log scale (milliseconds)')
plt.yscale('log')
plt.legend(title="Algorithm - Text Length", loc='best')
plt.show()