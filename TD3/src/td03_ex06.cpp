#include <iostream>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD03 - EX06 -\n" << std::endl;

    int n;
    
    do {
        std::cout << "Saisir un entier positif : ";
        std::cin >> n;
    } while (n < 0);

    std::cout << "\nTriangle rectangle de hauteur " << n << " :" << std::endl;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= i; ++j) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    std::cout << "\nSapin de hauteur " << n << " :" << std::endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n - i; j++) {
            std::cout << " ";
        }
        for (int k = 1; k <= (2 * i - 1); k++) {
            std::cout << "*";
        }
        std::cout << std::endl;
    }

    std::cout << "\nContour de carré de côté " << n << " :" << std::endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == 1 || i == n || j == 1 || j == n) {
                std::cout << "*";
            } else {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }

    return 0;
}