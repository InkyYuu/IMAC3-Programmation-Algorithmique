#include <iostream>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD03 - EX02 -\n" << std::endl;

    int somme = 0;
    int compteur = 0;
    int nombre;

    std::cout << "Entrez des entiers positifs (un entier négatif pour arrêter) :" << std::endl;

    do {
        std::cout << "Entier : ";
        std::cin >> nombre;
        if (nombre >= 0) {
            somme += nombre;
            compteur++;
        }
    } while (nombre >= 0);

    std::cout << "Somme des entiers saisis : " << somme << std::endl;
    if (compteur > 0) {
        float moyenne = static_cast<float>(somme) / compteur;
        std::cout << "Moyenne des entiers saisis : " << moyenne << std::endl;
    } else {
        std::cout << "Aucun entier positif saisi." << std::endl;
    }

    return 0;
}