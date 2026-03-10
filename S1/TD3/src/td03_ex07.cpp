#include <iostream>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD03 - EX07 -\n" << std::endl;

    int n;
    int count = 0;
    
    std::cout << "Saisir un entier positif : ";
    std::cin >> n;

    while (n != 1) {
        std::cout << n << " ";
        if (n%2 == 0) {
            n /= 2;
        } else {
            n = 3 * n + 1;
        }
        count++;
    }
    count++;
    std::cout << 1 << std::endl;

    std::cout << "Nombre d'itérations avant d'atteindre 1 : " << count << std::endl;
    return 0;
}