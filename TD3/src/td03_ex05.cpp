#include <cstdlib>
#include <ctime>
#include <iostream>
#include <windows.h>
 
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD03 - EX05 -\n" << std::endl;

    std::srand(std::time(nullptr));
    int random_variable = std::rand() % 100 + 1;

    int guess;
    int attempts = 0;

    std::cout << "Devinez le nombre entre 1 et 100 !" << std::endl;

    do {
        std::cout << "Entrez votre proposition : ";
        std::cin >> guess;
        attempts++;
        if (guess < random_variable) {
            std::cout << "C'est plus !" << std::endl;
        } else if (guess > random_variable) {
            std::cout << "C'est moins !" << std::endl;
        }
    } while (guess != random_variable);

    std::cout << "Félicitations ! Vous avez trouvé le nombre " << random_variable << " en " << attempts << " tentatives." << std::endl;

    return 0;
}