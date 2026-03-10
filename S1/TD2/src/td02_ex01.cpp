#include <windows.h> // Pour SetConsoleOutputCP et SetConsoleCP
#include <iostream>

int main() {
    // Pour que la console Windows puisse afficher les accents
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD 02 - Ex 01 -\n" << std::endl;

    int a = 5;
    std::cout << "a = " << a << std::endl;

    a++; // Incrémentation
    std::cout << "a = " << a << " \t(Incrémentation)" << std::endl;

    a = a*3; // Multiplication
    std::cout << "a = " << a << " \t(Multiplication par 3)" << std::endl;

    a = a/2; // Division
    std::cout << "a = " << a << " \t(Division par 2)" << std::endl;
    return 0;
}