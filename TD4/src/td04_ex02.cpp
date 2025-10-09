#include <iostream>
#include <windows.h>
#include <string>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD04 - EX02 -\n" << std::endl;

    std::string mot;
    std::cout << "Entrez un mot : ";
    std::cin >> mot;

    bool palindrome = true;
    int n = mot.length();
    for (int i = 0; i < n / 2; ++i) {
        if (mot[i] != mot[n - 1 - i]) {
            palindrome = false;
            break;
        }
    }

    std::cout << "Le mot " << (palindrome ? "est" : "n'est pas") << " un palindrome." << std::endl;

    return 0;
}