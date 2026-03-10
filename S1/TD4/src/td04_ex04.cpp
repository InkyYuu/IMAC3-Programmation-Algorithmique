#include <iostream>
#include <vector>
#include <set>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD04 - EX04 -\n" << std::endl;

    int level;
    std::cout << "Entrez un niveau terminé : ";
    std::cin >> level;

    int number_of_ennemies;
    std::cout << "Entrez le nombre d'ennemis vaincus : ";
    std::cin >> number_of_ennemies;

    std::set<int> points_per_ennemy;

    for (int i = 0; i < number_of_ennemies; ++i) {
        int level_ennemy;
        do {
            std::cout << "Entrez le niveau de l'ennemi " << (i + 1) << " (un entier positif) : ";
            std::cin >> level_ennemy;
        } while (level_ennemy <= 0);

        for (int j = level_ennemy; j < level; j += level_ennemy) {
            points_per_ennemy.insert(j);
        }
    }

    int total_points = 0;
    for (int points : points_per_ennemy) {
        total_points += points;
    }

    std::cout << "Le nombre total de points gagnés est : " << total_points << std::endl;
}