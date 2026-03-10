#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD 02 - Ex 02 -\n" << std::endl;

    float a, b, c;

    // Demander à l'utilisateur d'entrer trois valeurs flottantes
    std::cout << "Entrez la première valeur flottante : ";
    std::cin >> a;
    std::cout << "Entrez la deuxième valeur flottante : ";
    std::cin >> b;
    std::cout << "Entrez la troisième valeur flottante : ";
    std::cin >> c;

    // Calculer la somme et la moyenne
    float somme = a + b + c;
    float moyenne = somme / 3.0f;

    // Afficher les résultats
    std::cout << "La somme des trois valeurs est : " << somme << std::endl;
    std::cout << "La moyenne des trois valeurs est : " << moyenne << std::endl;

    return 0;
}