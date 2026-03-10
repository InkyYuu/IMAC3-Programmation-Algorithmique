#include <iostream>
#include <windows.h>

enum class Article { Alimentation, Vetements, Chaussures, Autre };

std::istream& operator>>(std::istream& is, Article& article)
{
    std::string articleAsString;
    is >> articleAsString;

    if (articleAsString == "Alimentation") {
        article = Article::Alimentation;
    } else if (articleAsString == "Vetements") {
        article = Article::Vetements;
    } else if (articleAsString == "Chaussures") {
        article = Article::Chaussures;
    } else if (articleAsString == "Autre") {
        article = Article::Autre;
    } else {
        is.setstate(std::ios::failbit);
    }

    return is;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    std::cout << "- TD03 - EX Bonus -\n" << std::endl;

    Article article;
    std::cout << "Saisir un type d'article (\"Alimentation\", \"Vetements\", \"Chaussures\" ou \"Autre\") : ";
    std::cin >> article;

    if (std::cin.fail()) {
        std::cout << "Erreur de saisie, il faut saisir un type d'article valide (\"Alimentation\", \"Vetements\", \"Chaussures\" ou \"Autre\")" << std::endl;

        std::cin.clear();
        std::cin.ignore(255, '\n');

        return 1;
    }

    if (article == Article::Alimentation) {
        std::cout << "Vous avez saisi un article de type Alimentation" << std::endl;
    } else if (article == Article::Vetements) {
        std::cout << "Vous avez saisi un article de type Vetements" << std::endl;
    } else if (article == Article::Chaussures) {
        std::cout << "Vous avez saisi un article de type Chaussures" << std::endl;
    } else if (article == Article::Autre) {
        std::cout << "Vous avez saisi un article de type Autre" << std::endl;
    }

    std::cout << "Quel est le prix de l'article ? ";
    float prix;
    std::cin >> prix;
    if (std::cin.fail() || prix < 0.0f) {
        std::cout << "Erreur de saisie, le prix doit être un nombre positif." << std::endl;
        return 1;
    }

    std::cout << "Avez-vous une carte de fidélité ? (oui/non) : ";
    bool carteFidelite;
    std::string carteFideliteInput;
    std::cin >> carteFideliteInput;
    if (carteFideliteInput != "oui" && carteFideliteInput != "non") {
        std::cout << "Erreur de saisie, il faut répondre par \"oui\" ou \"non\"." << std::endl;
        return 1;
    }
    carteFidelite = (carteFideliteInput == "oui");

    std::cout << "Quel est votre âge ? ";
    int age;
    std::cin >> age;
    if (std::cin.fail() || age < 0) {
        std::cout << "Erreur de saisie, l'âge doit être un entier positif." << std::endl;
        return 1;
    }

    float reduction = 0.0f;
    switch (article) {
        case Article::Alimentation:
            reduction = carteFidelite ? 0.08f : 0.05f;
            break;
        case Article::Vetements:
            reduction = carteFidelite ? 0.15f : 0.10f;
            break;
        case Article::Chaussures:
            reduction = carteFidelite ? 0.18f : 0.12f;
            break;
        case Article::Autre:
            reduction = 0.0f;
            break;
    }

    float prixReduit = prix * (1.0f - reduction);

    if (age < 26) {
        prixReduit *= 0.90f;
    }

    std::cout << "Le prix final après réduction est : " << prixReduit << " euros." << std::endl;

    float bonAchat = prixReduit * 0.10f;
    if (bonAchat > 30.0f) {
        bonAchat = 30.0f;
    }
    std::cout << "Vous bénéficiez d'un bon d'achat de " << bonAchat << " euros à valoir sur un prochain achat." << std::endl;

    return 0;
}