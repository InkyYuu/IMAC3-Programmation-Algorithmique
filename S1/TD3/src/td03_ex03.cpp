#include <iostream> 
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD03 - EX03 -\n" << std::endl;

    int n;
    do {
        std::cout << "Saisir un entier positif : ";
        std::cin >> n;
    } while (n < 0);

    int modulo = n % 2;

    std::cout << "L'entier est " << (modulo == 0 ? "pair" : "impair") << std::endl;

    std::cout << "Les entiers " << (modulo == 0 ? "pairs" : "impairs") << " positifs inférieur à " << n << " sont :" << std::endl;

    for (int i = 1; i < n; ++i) {
        if (i % 2 == modulo) {
            std::cout << i << ", ";
        }
    }
    std::cout << std::endl;

    return 0;
}