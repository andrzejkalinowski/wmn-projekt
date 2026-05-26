# Andrzej Kalinowski 2026, Wstęp do Metod Numerycznych

### This script compiles and runs everything:
### Compiles and runs the C numerical solver
### Generates plots using the python plotting script - probably will be handled by the C code in the future
### Compiles the LaTeX report

# Compile and run the C numerical solver
echo
echo "__C Compiler output:__"
echo
gcc ./src/*.c -Wall -o ./build/solver -lm

echo
echo "__C Solver output:__"
echo
./build/solver

# # Compile LaTeX report
# echo
# echo "__Compiling LaTeX report:__"
# echo
# latex -output-format pdf -output-directory ./build raport.tex
# cp ./build/raport.pdf ./projekt_raport.pdf

