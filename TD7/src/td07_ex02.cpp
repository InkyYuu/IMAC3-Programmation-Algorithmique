#include <iostream>
#include <windows.h>
#include <string>
#include <vector>
#include <algorithm>

struct Pokemon {
    std::string nom;
    int pv;
    int attaque;
    int vitesse;
};

struct Dresseur {
    std::string nom;
    std::vector<Pokemon> pokemons;
}; 

void combat(Pokemon& p1, Pokemon& p2) {
    Pokemon* first;
    Pokemon* second;
    if (p1.vitesse > p2.vitesse) {
        first = &p1;
        second = &p2;
    } else if (p1.vitesse < p2.vitesse) {
        first = &p2;
        second = &p1;
    } else {
        int random = rand() % 2;
        if (random == 0) {
            first = &p1;
            second = &p2;
        } else {
            first = &p2;
            second = &p1;
        }
    }

    int tour = 1;
    while (p1.pv > 0 && p2.pv > 0) {
        std::cout << "Tour " << tour << " :\n" << std::endl;
        if (first->pv > 0) {
            second->pv -= first->attaque;
            std::cout << first->nom << " attaque, il reste " << std::max(second->pv, 0) << " PV à " << second->nom << std::endl; // On utilise max pour éviter d'afficher des PV négatifs
        } else {
            std::cout << first->nom << " est KO et ne peut pas attaquer." << std::endl;
        }

        if (second->pv > 0) {
            first->pv -= second->attaque;
            std::cout << second->nom << " attaque, il reste " << std::max(first->pv, 0) << " PV à " << first->nom << std::endl;
        } else {
            std::cout << second->nom << " est KO et ne peut pas attaquer." << std::endl;
        }
        std::cout << std::endl;

        tour++;
    }

    if (p1.pv <= 0 && p2.pv <= 0) {
        std::cout << "Le combat se termine par un match nul !" << std::endl;
    } else if (p1.pv <= 0) {
        std::cout << p2.nom << " remporte le combat !" << std::endl;
    } else {
        std::cout << p1.nom << " remporte le combat !" << std::endl;
    }
}

void combat(Dresseur& d1, Dresseur& d2) {
    int round = 1;
    while (!d1.pokemons.empty() && !d2.pokemons.empty()) {
        Pokemon& p1 = d1.pokemons.front();
        Pokemon& p2 = d2.pokemons.front();

        std::cout << "-- Round " << round << " : " << p1.nom << " vs " << p2.nom << " --\n" << std::endl;
        combat(p1, p2);
        round++;

        if (p1.pv <= 0) {
            d1.pokemons.erase(d1.pokemons.begin());
        }
        if (p2.pv <= 0) {
            d2.pokemons.erase(d2.pokemons.begin());
        }
        std::cout << std::endl;
    }

    std::cout << "- - - - - - - - - - - - - - - - - - - - - - - - -\n" << std::endl;

    if (d1.pokemons.empty() && d2.pokemons.empty()) {
        std::cout << "Le combat se termine par un match nul entre les dresseurs !" << std::endl;
    } else if (d1.pokemons.empty()) {
        std::cout << d2.nom << " remporte le combat entre les dresseurs !" << std::endl;
    } else {
        std::cout << d1.nom << " remporte le combat entre les dresseurs !" << std::endl;
    }
}

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD07 - EX02 -" << std::endl;

    std::cout << "Combat entre deux Pokémons:" << std::endl;
    Pokemon pikachu = {"Pikachu", 50, 10, 8};
    Pokemon bulbasaur = {"Bulbasaur", 30, 20, 3};

    combat(pikachu, bulbasaur);

    std::cout << "\nCombat entre deux Dresseurs:" << std::endl;
    Dresseur dresseur1{"Dresseur1", {
        Pokemon{"Dresseur1_Poke1", 5, 10, 8},
        Pokemon{"Dresseur1_Poke2", 5, 10, 8},
        Pokemon{"Dresseur1_Poke3", 5, 10, 8},
    }};
        
    Dresseur dresseur2{"Dresseur2", {
        Pokemon{"Dresseur2_Poke1", 20, 10, 3},
        Pokemon{"Dresseur2_Poke2", 20, 10, 3},
        Pokemon{"Dresseur2_Poke3", 20, 10, 3},
    }};

    combat(dresseur1, dresseur2);

    return 0;
}