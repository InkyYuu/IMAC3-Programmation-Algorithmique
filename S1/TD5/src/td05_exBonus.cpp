#include <iostream>
#include <windows.h>
#include <cmath>

/*
    Voir les explications dans le fichier doc/td05_exBonus_explications.pdf ou doc/td05_exBonus_explications.docx pour comprendre l'énoncé de l'exercice.
*/

long long U(int n) {
    if (n == 0) return 1;
    return 2 * std::pow(4, n) - 1;
}

long long V(int n) {
    if (n == 0) return 2;
    return 2/3 + 4/3 * std::pow(4, n);
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    for (int n = 0; n < 10; n++) {
        std::cout << "U(" << n << ") = " << U(n) << " et V(" << n << ") = " << V(n) << std::endl;
    }

    return 0;
}

