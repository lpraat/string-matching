def generate_legend_label(i):

    if int(i) * 1e-6 >= 1:
        return str(int(i * 1e-6)) + "M"

    if int(i) * 1e-3 >= 1:
        return str(int(i * 1e-3)) + "k"

    return str(i)
