#include <windows.h>
#include <iostream>

int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD 02 - Ex 04 -\n" << std::endl;

    const int DAYS_IN_YEAR = 360;
    const int DAYS_IN_CENTURY = DAYS_IN_YEAR * 100;
    const int DAYS_IN_MONTH = 30;
    const int DAYS_IN_WEEK = 7;

    int days_total;

    std::cout << "Entrez un nombre de jours : ";
    std::cin >> days_total;

    int centuries = days_total / DAYS_IN_CENTURY;
    int remainder = days_total % DAYS_IN_CENTURY;

    int years = remainder / DAYS_IN_YEAR;
    remainder = remainder % DAYS_IN_YEAR;

    int months = remainder / DAYS_IN_MONTH;
    remainder = remainder % DAYS_IN_MONTH;

    int weeks = remainder / DAYS_IN_WEEK;
    int days = remainder % DAYS_IN_WEEK;

    std::cout << days_total << " jours correspondent à : "
              << centuries << " siècle(s) "
              << years << " année(s) "
              << months << " mois "
              << weeks << " semaine(s) "
              << days << " jour(s)" << std::endl;

    return 0;
}