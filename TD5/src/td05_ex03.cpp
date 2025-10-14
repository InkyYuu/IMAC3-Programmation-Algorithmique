#include <iostream>
#include <windows.h>
#include <vector>

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    return fibonacci(n-1) + fibonacci(n-2);
}

int fibonacci_iteratif(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

std::vector<int> fibonacci_tableau(int n) {
    std::vector<int> fib(n);
    if (n > 0) fib[0] = 0;
    if (n > 1) fib[1] = 1;
    for (int i = 2; i < n; i++) {
        fib[i] = fib[i-1] + fib[i-2];
    }
    return fib;
}

int main() {

    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD05 - EX03 -\n" << std::endl;
    
    int n;
    do {
    std::cout << "Entrez le nombre de termes de la suite de Fibonacci : ";
    std::cin >> n;
    if (n < 1) {
        std::cout << "Le nombre doit être positif et non nul !" << std::endl;
    }
    } while (n < 1);

    std::cout << "Les " << n << " premiers termes de la suite de Fibonacci (récursive) sont : ";
    for (int i = 0; i < n; i++) {
        std::cout << fibonacci(i);
        if (i < n - 1) std::cout << ", ";
    }
    std::cout << std::endl;

    std::cout << "Fibonacci (en itératif) de " << n << " est : " << fibonacci_iteratif(n) << std::endl;

    std::vector<int> fib_tableau = fibonacci_tableau(n);
    std::cout << "Les " << n << " premiers termes de la suite de Fibonacci (tableau) sont : ";
    for (size_t i = 0; i < fib_tableau.size(); i++)
        std::cout << fib_tableau[i] << (i < fib_tableau.size() - 1 ? ", " : "");
    std::cout << std::endl;

    return 0;
}