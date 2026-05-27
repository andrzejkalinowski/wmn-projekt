# Andrzej Kalinowski 2026, Wstęp do Metod Numerycznych

### This script compiles and runs everything:
### Compiles and runs the C numerical solver
### Generates plots using the python plotting script - probably will be handled by the C code in the future
### Compiles the LaTeX report

# Build folder
# mkdir ./build

# Compile and run the C numerical solver
echo
echo "__C Compiler output:__"
echo
gcc ./src/*.c -Wall -o ./build/solver -lm

echo
echo "__C Solver output:__"
echo
./build/solver

# Wywołanie skryptu do rysowania wykresów
python3 ./plotter.py data/data_yx.csv 'x' 'y(x)' 'Trajektoria kulki' equal
python3 ./plotter.py data/data_xt.csv 't' 'x(t)' 'Położenie kulki w osi x'
python3 ./plotter.py data/data_yt.csv 't' 'y(t)' 'Położenie kulki w osi y'
python3 ./plotter.py data/data_vxt.csv 't' 'vx(t)' 'Prędkość kulki w osi x'
python3 ./plotter.py data/data_vyt.csv 't' 'vy(t)' 'Prędkość kulki w osi y'
python3 ./plotter.py data/data_energy.csv 't' 'E(t)' 'Energia mechaniczna kulki'


# Compile LaTeX report
echo
echo "__Compiling LaTeX report:__"
echo
latex -output-format pdf -output-directory ./build raport.tex
cp ./build/raport.pdf ./projekt_raport.pdf

# Delete build files
rm -rf ./build/*