#include <iostream>
#include <windows.h>
#include <vector>

bool pangramme(const std::string & phrase) {
    std::vector<bool> lettres(26, false);
    for (char c : phrase) {
        if (std::isalpha(c)) {
            char lettre = std::tolower(static_cast<unsigned char>(c));
            lettres[lettre - 'a'] = true;
        }
    }
    for (bool presente : lettres) {
        if (!presente) return false;
    }
    return true;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD05 - EX05 -\n" << std::endl;

    std::string phrase;
    std::cout << "Entrez une phrase : ";
    std::getline(std::cin, phrase);

    // Exemple de pangramme : "Portez ce vieux whisky au juge blond qui fume"
    std::cout << "La phrase \"" << phrase << "\" " << (pangramme(phrase) ? "est" : "n'est pas") << " un pangramme." << std::endl;

    return 0;
}