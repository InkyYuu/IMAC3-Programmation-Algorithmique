#include <iostream>
#include <windows.h>

int factorielle(int n) {
    if (n == 0) {
        return 1;
    } else {
        return n * factorielle(n - 1);
    }
}

int factorielle_iterative(int n) {
    int resultat = 1;
    for (int i = 1; i <= n; ++i) {
        resultat *= i;
    }
    return resultat;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD05 - EX02 -\n" << std::endl;

    int n;
    std::cout << "Entrez un entier positif : ";
    std::cin >> n;
    if (n < 0) {
        std::cout << "Erreur : l'entier doit être positif." << std::endl;
    } else if (n > 12) {
        std::cout << "Erreur : l'entier est trop grand (doit être ≤ 12 pour éviter le dépassement de capacité)." << std::endl;
    } else {
        std::cout << "La factorielle de " << n << " (récursive) est " << factorielle(n) << std::endl;
        std::cout << "La factorielle de " << n << " (itérative) est " << factorielle_iterative(n) << std::endl;
    }

    return 0;
}