# Andrzej Kalinowski 2026, Wstęp do Metod Numerycznych
# This script is used for plot generation using the data generated in the C numerical solver

# Importy potrzebnych bibliotek
import matplotlib.pyplot as plt
import sys
import csv

# Tu pakujemy dane zczytane z pliku
x = []
y = []

# int manin() { XDDDD
if __name__ == "__main__":

    # Otowrzenie pliku i zaladowanie danych do tablic
    with open(sys.argv[1], newline='') as data_file:
        reader = csv.reader(data_file, delimiter=',')
        for row in reader:
            x.append(float(row[0]))
            y.append(float(row[1]))

    # Jakies tam ustawienia wizualne wykresow
    plt.rcParams.update({
        'font.family': 'serif',
        'mathtext.fontset': 'cm',
        'font.size': 11,
        'axes.labelsize': 12,
        'axes.titlesize': 13,
        'axes.linewidth': 0.8,
        'axes.spines.top': False,
        'axes.spines.right': False,
        'xtick.direction': 'in',
        'ytick.direction': 'in',
        'xtick.major.size': 4,
        'ytick.major.size': 4,
        'figure.dpi': 120,
        'savefig.dpi': 300,
        'savefig.bbox': 'tight',
        'pdf.fonttype': 42,
        'ps.fonttype': 42,
    })
    equal_axes = len(sys.argv) > 5 and sys.argv[5] == 'equal'
    fig, ax = plt.subplots(figsize=(12.0, 4.0) if equal_axes else (6.4, 4.0))
    ax.plot(x, y, color='#1f4e79', linewidth=1.4)   # Utowrzneie wykrsu
    ax.set_xlabel(sys.argv[2])
    ax.set_ylabel(sys.argv[3])
    ax.set_title(sys.argv[4])
    ax.grid(True, linestyle='--', linewidth=0.5, alpha=0.6)
    ax.set_axisbelow(True)
    ax.margins(x=0.03, y=0.08)

    #  warunkowe wlacznie rownych osi
    if equal_axes:
        ax.set_aspect('equal', adjustable='datalim')
    fig.tight_layout()

    # Zapisnie wykresu 
    fig.savefig(f"plots/{sys.argv[4]}.pdf")
