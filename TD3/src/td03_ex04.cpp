#include <iostream>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD03 - EX04 -\n" << std::endl;

    int age;

    do {
        std::cout << "Veuillez saisir votre âge : ";
        std::cin >> age;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(255, '\n');
            std::cout << "Erreur : vous devez saisir un nombre entier pour l'âge." << std::endl;
            return 1;
        }

        if (age < 0) {
            std::cout << "Erreur : l'âge ne peut pas être négatif." << std::endl;
            return 1;
        }
    } while (age < 0);

    std::cout << "Vous êtes " << (age < 18 ? "mineur." : "majeur.") << std::endl;

    return 0;
}