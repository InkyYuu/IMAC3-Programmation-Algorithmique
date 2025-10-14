#include <iostream>
#include <windows.h>

int somme_copie(int a, int b) {
    return a + b;
}

int somme_reference(int & a, int & b) {
    return a + b;
}

int somme_constante(const int & a, const int & b) {
    return a + b;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD05 - EX01 -\n" << std::endl;

    // Avec des variables
    std::cout << "Avec des variables :" << std::endl;
    int a = 5, b = 10;
    std::cout << "somme_copie(a, b) = " << somme_copie(a, b) << std::endl;
    std::cout << "somme_reference(a, b) = " << somme_reference(a, b) << std::endl;
    std::cout << "somme_constante(a, b) = " << somme_constante(a, b) << std::endl;

    // Avec des littéraux
    std::cout << "\nAvec des littéraux :" << std::endl;
    std::cout << "somme_copie(5, 10) = " << somme_copie(5, 10) << std::endl;
    // std::cout << "somme_reference(5, 10) = " << somme_reference(5, 10) << std::endl; // Erreur de compilation car les références doivent référencer des variables modifiables et existantes
    std::cout << "somme_constante(5, 10) = " << somme_constante(5, 10) << std::endl; // Fonctionne car les références sont constantes donc création de variables temporaires non modifiables

    return 0;
}
