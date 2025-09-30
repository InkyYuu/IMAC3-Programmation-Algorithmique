#include <windows.h>
#include <iostream>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD03 - EX01 -\n" << std::endl;

    std::cout << "Saisir un entier : ";
    int entier;
    std::cin >> entier;

    std::cout << entier << " est " << (entier > 0 ? "positif" : (entier < 0 ? "négatif" : "nul")) << std::endl;
    
    return 0;
}