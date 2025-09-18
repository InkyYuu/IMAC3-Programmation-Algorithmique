#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD 02 - Ex Bonus -\n" << std::endl;

    int const WEIGHT_OF_A_BAG_OF_POTATOES_IN_KG = 2; // en kg
    float const PRICE_PER_KG_FOR_POTATOES = 1.5; // en euros
    int const WEIGHT_OF_A_CARROT_IN_G = 150; // en grammes
    float const WEIGHT_OF_A_CARROT_IN_KG = WEIGHT_OF_A_CARROT_IN_G / 1000.0f; // en kilogrammes
    float const PRICE_PER_KG_FOR_CARROTS = 2.5; // en euros
    float const PRICE_OF_A_SALAD = 1.2; // en euros

    int number_of_bags_of_potatoes;
    int number_of_carrots;
    int number_of_salads;

    std::cout << "Entrez le nombre de sacs de pommes de terre (2 kg par sac) : ";
    std::cin >> number_of_bags_of_potatoes;

    std::cout << "Entrez le nombre de carottes (150 g par carotte) : ";
    std::cin >> number_of_carrots;

    std::cout << "Entrez le nombre de salades : ";
    std::cin >> number_of_salads;

    float total_weight_of_potatoes_in_kg = number_of_bags_of_potatoes * WEIGHT_OF_A_BAG_OF_POTATOES_IN_KG;
    float total_weight_of_carrots_in_kg = number_of_carrots * WEIGHT_OF_A_CARROT_IN_KG;
    float total_price_of_potatoes = total_weight_of_potatoes_in_kg * PRICE_PER_KG_FOR_POTATOES;
    float total_price_of_carrots = total_weight_of_carrots_in_kg * PRICE_PER_KG_FOR_CARROTS;
    float total_price_of_salads = number_of_salads * PRICE_OF_A_SALAD;

    float total_price = total_price_of_potatoes + total_price_of_carrots + total_price_of_salads;

    std::cout << "\nLe prix total de la commande est de : " << total_price << "€" << std::endl; 

    return 0;
}