#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);


    std::cout << "- TD 02 - Ex 03 -\n" << std::endl;

    int n = 11;

    std::cout << "n = " << n << std::endl;
    std::cout << "n = " << n/2 << " (division par 2)" << std::endl;
    std::cout << "On obtient 5, on perd la partie decimale car on utilise un entier." << std::endl;

    float n_converted = static_cast<float>(n);

    std::cout << "n = " << n_converted/2 << " (n converti en float puis division par 2)" << std::endl;
    std::cout << "n = " << n/2.0f << " (division par 2.0f) fonctionne aussi car on force la division à être en virgule flottante." << std::endl;

    return 0;
}