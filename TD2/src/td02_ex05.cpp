#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD 02 - Ex 05 -\n" << std::endl;

    int n;
    while (n < 1 || n > 26) {
        std::cout << "Entrez un nombre entre 1 et 26 : ";
        std::cin >> n;

        if (n < 1 || n > 26) {
            std::cout << "Nombre invalide. Veuillez entrer un nombre entre 1 et 26." << std::endl;
        }
    }

    char lettre = 'A' + n - 1;
    std::cout << "La lettre correspondante est : " << lettre << std::endl;

    return 0;
}