#include <iostream>
#include <vector>
#include <cstdlib>
#include <windows.h>

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD04 - EX01 -\n" << std::endl;

    size_t const dwarf_count { 20 };

    std::vector<float> calories {};

    // std::srand permet de fixer la "seed" du générateur aléatoire (pour avoir des résultats reproductibles)
    std::srand(42);

    calories.reserve(dwarf_count); // Pour optimiser, on dit à l'avance au tableau combien d'éléments vont être ajoutés, afin qu'il puisse allouer la mémoire nécessaire en une seule fois. Si on ne fait pas ça, à chaque push_back dans la boucle le tableau va être obligé d'allouer de la mémoire supplémentaire pour contenir le nouvel élément, ce qui est plus lent.
    for (size_t i { 0 }; i < dwarf_count; ++i) {
        float const random_n { static_cast<float>(rand()) / static_cast<float>(RAND_MAX) };
        calories.push_back(100.f + (24000.f-100.f) * random_n);
    }

    /*
    std::cout << "Quantités de provisions transportées par les nains (en calories) :" << std::endl;
    for (float const c : calories) {
        std::cout << c << ", ";
    }
    std::cout << std::endl;
    */

    float max_calories { 0.f };
    float min_calories { calories[0] };
    for (float const c : calories) {
        if (c > max_calories) {
            max_calories = c;
        }
        if (c < min_calories) {
            min_calories = c;
        }
    }

    // Trouver les trois plus grandes valeurs
    float top1 = 0.f, top2 = 0.f, top3 = 0.f;
    for (float const c : calories) {
        if (c > top1) {
            top3 = top2;
            top2 = top1;
            top1 = c;
        } else if (c > top2) {
            top3 = top2;
            top2 = c;
        } else if (c > top3) {
            top3 = c;
        }
    }
    float sum_top3 = top1 + top2 + top3;
    std::cout << "Somme des provisions transportées par les trois nains les plus chargés : " << sum_top3 << std::endl;
    std::cout << "La quantité maximale de provisions transportée par un nain est : " << max_calories << std::endl;
    std::cout << "La quantité minimale de provisions transportée par un nain est : " << min_calories << std::endl;

    return 0;
}