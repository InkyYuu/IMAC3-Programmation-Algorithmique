#include <iostream>
#include <windows.h>
#include <string>

void inverser_casse(std::string & str) {
    for (char & c : str) {
        if (std::islower(c)) {
            c = std::toupper(static_cast<unsigned char>(c));
        } else if (std::isupper(c)) {
            c = std::tolower(static_cast<unsigned char>(c));
        }
    }
}

int nombre_voyelles(const std::string & str) {
    int count = 0;
    for (char c : str) {
        char lower = std::tolower(static_cast<unsigned char>(c));
        if (lower == 'a' || lower == 'e' || lower == 'i' || lower == 'o' || lower == 'u' || lower == 'y') {
            count++;
        }
    }
    return count;
}

int nombre_mots(const std::string & str) {
    int count = 0;
    bool in_word = false;
    for (char c : str) {
        if (std::isspace(static_cast<unsigned char>(c))) {
            in_word = false;
        } else {
            if (!in_word) {
                count++;
                in_word = true;
            }
        }
    }
    return count;
}

void reverse_string(std::string & str) {
    int n = str.length();
    for (int i = 0; i < n / 2; i++) {
        char temp = str[i];
        str[i] = str[n - i - 1];
        str[n - i - 1] = temp;
    }
}

bool est_entier(const std::string & str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!std::isdigit(static_cast<unsigned char>(c))) {
            return false;
        }
    }
    return true;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD05 - EX06 -\n" << std::endl;

    std::string str;
    std::cout << "Entrez une chaîne de caractères : ";
    std::getline(std::cin, str);

    inverser_casse(str);
    std::cout << "Chaîne après inversion de casse : " << str << std::endl;
    std::cout << "Nombre de voyelles dans la chaîne : " << nombre_voyelles(str) << std::endl;
    std::cout << "Nombre de mots dans la chaîne : " << nombre_mots(str) << std::endl;
    reverse_string(str);
    std::cout << "Chaîne après inversion : " << str << std::endl;
    std::cout << "La chaîne " << (est_entier(str) ? "représente" : "ne représente pas") << " un entier." << std::endl;

    return 0;
}