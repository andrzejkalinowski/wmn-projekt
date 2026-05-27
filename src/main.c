#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "rk4.h"

// Stałe fizyczne
#define g 9.81      // Przyspieszenie grawitacyjne [m/s^2]
#define rho 1.225   // Gęstość powietrza [kg/m^3]
#define PI 3.1415

// Stałe zadania
#define c 0.3       // opór powietrza
#define m 0.1       // Masa kulki [kg]
#define R 0.1       // promień kulki
#define x0 10       // warunewk początkowy, polozenie x
#define y0 10       // warunek początkowy, wysokosc z ktorej spada kulka
#define vx0 0      // warunek początkowy, prędkość początkowa w osi x
#define vy0 0       // warunek początkowy, prędkość początkowa w osi y
#define wmax 25      // maksymalna predkosc wiatru (na 'dole')
#define dt 0.001     // krok czasowy
#define T 10        // maksymalny czas 'symulacji'
#define S (PI * R * R) // Pole przekroju poprzecznego kulki [m^2]
#define k 0.5*rho*S*c

// pozioma predkosc wiatru od poloznia y
double w(double y){
    return (wmax/y0)*y - wmax;
}

// Moduł wektora predkosci kulki wzgledem powietrza
double vp_m(double x_prim, double y_prim, double y) {
    return sqrt(pow(x_prim + w(y), 2) + pow(y_prim, 2));
}

// Funkcja prawych stron, do rozwiazywania rozniczkowego rownaia ruchu
void vrhs(double t0, double* z0, double* z1) {
    z1[0] = z0[1];
    z1[1] = (k * vp_m(z0[1], z0[3], z0[2]) * (z0[1] + w(z0[2]))) / m;
    z1[2] = z0[3];
    z1[3] = ((k * vp_m(z0[1], z0[3], z0[2]) * z0[3]) - m * g) / m;
}

// Calkowita energia mechaniczna kulki
double energia(double x_prim, double y_prim, double y) {
    double v = sqrt(pow(x_prim, 2) + pow(y_prim, 2));
    return 0.5 * m * v * v + m * g * y;
}

int main() {

    // Otowrzenie ploikow na ktorych postaniw powstana wykrsey
    FILE *f_yx = fopen("data/data_yx.csv", "w");
    FILE *f_xt = fopen("data/data_xt.csv", "w");
    FILE *f_yt = fopen("data/data_yt.csv", "w");
    FILE *f_vxt = fopen("data/data_vxt.csv", "w");
    FILE *f_vyt = fopen("data/data_vyt.csv", "w");
    FILE *f_energy = fopen("data/data_energy.csv", "w");

    double z0[4] = {x0, vx0, y0, vy0}; // zapisanie warunkow poczatkowych
    double z1[4];

    // iterujemy sobie po czasie
    for(double t = 0;  t <= T; t += dt) {
        if(z1[2] < 0){
            printf("Kulka dotarla do ziemi w czasie t = %f s \n", t);
            break; // kulka dotarla do ziemi   
        }

        // Rozwiazanie
        vrk4(t, z0, dt, 4, vrhs, z1);

        // Zapisamy wyniki do plikow
        fprintf(f_yx, "%f, %f \n", z1[0], z1[2]);
        fprintf(f_xt, "%f, %f \n", t, z1[0]);
        fprintf(f_yt, "%f, %f \n", t, z1[2]);
        fprintf(f_vxt, "%f, %f \n", t, z1[1]);
        fprintf(f_vyt, "%f, %f \n", t, z1[3]);
        fprintf(f_energy, "%f, %f \n", t, energia(z1[1], z1[3], z1[2]));
        z0[0] = z1[0];
        z0[1] = z1[1];
        z0[2] = z1[2];
        z0[3] = z1[3];
    }
    
    // Zamknięcie plikow
    fclose(f_yx);
    fclose(f_xt);
    fclose(f_yt);
    fclose(f_vxt);
    fclose(f_vyt);
    fclose(f_energy);
    // Wywołanie skryptu do rysowania wykresów
    system("python3 ./plotter.py data/data_yx.csv 'x' 'y(x)' 'Trajektoria kulki' equal");
    system("python3 ./plotter.py data/data_xt.csv 't' 'x(t)' 'Położenie kulki w osi x'");
    system("python3 ./plotter.py data/data_yt.csv 't' 'y(t)' 'Położenie kulki w osi y'");
    system("python3 ./plotter.py data/data_vxt.csv 't' 'vx(t)' 'Prędkość kulki w osi x'");
    system("python3 ./plotter.py data/data_vyt.csv 't' 'vy(t)' 'Prędkość kulki w osi y'");\
    system("python3 ./plotter.py data/data_energy.csv 't' 'E(t)' 'Energia mechaniczna kulki'");

    return 0;
}