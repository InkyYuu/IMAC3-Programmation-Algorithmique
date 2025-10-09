#include <iostream>
#include <windows.h>
#include <vector>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD04 - EX03 -\n" << std::endl;

    long long number;
    do {
        std::cout << "Entrez un nombre entier positif (> 1 000 000) : ";
        std::cin >> number;
    } while (number <= 1000000);

    std::vector<int> digits;
    long long temp = number;
    while (temp > 0) {
        digits.push_back(temp % 10);
        temp /= 10;
    }

    int counts[10] = {0};
    for (int digit : digits) {
        counts[digit]++;
    }

    int max_digit = 0, max_count = counts[0];
    for (int i = 1; i < 10; ++i) {
        if (counts[i] > max_count) {
            max_count = counts[i];
            max_digit = i;
        }
    }

    std::cout << "Le chiffre le plus fréquent est : " << max_digit << " (apparait " << max_count << " fois)" << std::endl;
    return 0;
}