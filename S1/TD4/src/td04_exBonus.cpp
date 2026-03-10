#include <iostream>
#include <vector>
#include <windows.h>
#include <string>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD04 - EXBonus -\n" << std::endl;

    const int SIZE = 16;

    std::string card_number;
    
    do {
        std::cout << "Entrez un numéro de carte bancaire (16 chiffres sans espace) : ";
        std::cin >> card_number;
    } while (card_number.length() != SIZE);

    int sum_Luhn = 0;
    for (int i = 0; i < SIZE; ++i) {
        int digit = card_number[i] - '0';
        if (i % 2 == 1) {
            digit *= 2;
            if (digit > 9) {
                digit -= 9;
            }
        }
   
        sum_Luhn += digit;
    }

    std::cout << "Le numéro de carte bancaire est " << (sum_Luhn % 10 == 0 ? "valide." : "invalide.") << std::endl;
}