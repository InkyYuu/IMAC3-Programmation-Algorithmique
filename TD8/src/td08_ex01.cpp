#include <iostream>
#include <windows.h>
#include <iomanip>
#include "color.hpp"
#include "color_utils.hpp"
#include "color_hex.hpp"

void displayInHex(unsigned int hex) {
    /* On utilise std::hex, std::setw et std::setfill pour formater l'affichage en hexadécimal
        - std::hex : permet d'afficher le nombre en base hexadécimale
        - std::setw(6) de <iomanip> : fixe la largeur de l'affichage à 6 caractères
        - std::setfill('0') de <iomanip> : remplit les espaces vides avec des zéros
    */
    std::cout << std::hex << std::setw(6) << std::setfill('0') << hex << std::dec << std::endl;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD08 - EX01 -\n" << std::endl;

    std::string hex;

    std::cout << "Entrez la première couleur en hexadécimal (sous la forme 0xRRGGBB ou #RRGGBB ou RRGGBB) : ";
    std::cin >> hex;
    Color::RGB color1 = Color::RGB_from_hex(hex);

    std::cout << "Entrez la deuxième couleur en hexadécimal (sous la forme 0xRRGGBB ou #RRGGBB ou RRGGBB) : ";
    std::cin >> hex;
    Color::RGB color2 = Color::RGB_from_hex(hex);

    std::cout << "Couleur 1 : ";
    color1.display();
    std::cout << " hex : ";
    displayInHex(Color::RGB_to_hex_int(color1));

    std::cout << "Couleur 2 : ";
    color2.display();
    std::cout << " hex : ";
    displayInHex(Color::RGB_to_hex_int(color2));

    Color::RGB mixed = Color::mix(color1, color2);
    std::cout << "Couleur mélangée : ";
    mixed.display();
    std::cout << " hex : ";
    displayInHex(Color::RGB_to_hex_int(mixed));

    float luminance = Color::luminance(mixed);
    std::cout << "Luminance de la couleur mélangée : " << luminance << std::endl;

    Color::RGB inverted = Color::invert(mixed);
    std::cout << "Couleur mélangée inversée : ";
    inverted.display();
    std::cout << " hex : ";
    displayInHex(Color::RGB_to_hex_int(inverted));

    return 0;
}