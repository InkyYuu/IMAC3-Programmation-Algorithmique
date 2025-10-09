#include <iostream>
#include <vector>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD04 - EX05 -\n" << std::endl;

    const int SIZE = 10;
    std::vector<int> tab(SIZE);

    std::cout << "Entrez 10 entiers entre 0 et 5 :" << std::endl;
    for (int i = 0; i < SIZE; ++i) {
        int val;
        do {
            std::cout << "Entier " << i + 1 << " : ";
            std::cin >> val;
        } while (val < 0 || val > 5);
        tab[i] = val;
    }

    std::cout << "Tableau avant : [";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << tab[i];
        if (i != SIZE - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    int writeIndex = 0;
    for (int readIndex = 0; readIndex < SIZE; ++readIndex) {
        if (tab[readIndex] != 3) {
            tab[writeIndex] = tab[readIndex];
            ++writeIndex;
        }
    }   

    for (int i = writeIndex; i < SIZE; ++i) {
        tab[i] = 0;
    }

    std::cout << "Tableau après : [";
    for (int i = 0; i < SIZE; ++i) {
        std::cout << tab[i];
        if (i != SIZE - 1) std::cout << ", ";
    }
    std::cout << "]" << std::endl;

    return 0;
}