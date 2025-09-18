#include <windows.h>
#include <iostream> // faute de frappe

int main()
{
    float const pi {3.141592}; // ; était manquante
    float a {pi*3}; // je veux le résultat de pi (environ 3.141592) fois 3 - float au lieu de int pour avoir la partie décimale
    int b {8}; // enlever le const car je veux modifier la valeur de b plus tard

    a += 20;  // je veux ajouter le nombre 20 à la valeur de a "" est un string

    b = b * 15; // je veux modifier la valeur de b en la multipliant par 15

    std::cout << "a: " << a << std::endl; // il manquait le < pour faire <<

    std::cout << "b: " << b << std::endl; // il manquait le ; à la fin de la ligne

    return 0;
}