#include <iostream>
#include <math.h>
#include <string>

/* Initialisation */
size_t folding_string_hash(std::string const &s, size_t max);
size_t folding_string_ordered_hash(std::string const &s, size_t max);
size_t polynomial_rolling_hash(std::string const &s, size_t p, size_t m);

/* Implémentation */

/**
 * Fonction de hachage pour les chaînes de caractères utilisant la méthode de
 * pliage. Fais la somme des codes ASCII avec un modulo des caractères et
 * renvoie un entier compris entre 0 et max.
 * @param s La chaîne de caractères à hacher.
 * @param max La valeur maximale pour le résultat du hachage.
 * @return Un entier représentant le hachage de la chaîne de caractères.
 */
size_t folding_string_hash(std::string const &s, size_t max) {
  size_t hash = 0;
  for (char c : s) {
    hash += static_cast<size_t>(c);
  }
  return hash % max;
}

/**
 * Fonction de hashage ordonné pour les chaînes de caractères utilisant la
 * méthode de pliage. Fais la somme des codes ASCII multipliés par leur position
 * dans la chaîne + 1, et un modulo.
 * @param s La chaîne de caractères à hacher.
 * @param max La valeur maximale pour le résultat du hachage.
 * @return Un entier représentant le hachage ordonné de la chaîne de caractères.
 */
size_t folding_string_ordered_hash(std::string const &s, size_t max) {
  size_t hash = 0;
  for (size_t i = 0; i < s.length(); ++i) {
    hash += static_cast<size_t>(s[i]) * (i + 1);
    hash %= max;
  }
  return hash;
}

/**
 * Fonction de hachage polynomiale pour les chaînes de caractères utilisant la
 * méthode du rolling hash. Fais une somme polynomiale des codes ASCII avec un
 * modulo à la fin.
 * @param s La chaîne de caractères à hacher.
 * @param p Un nombre premier utilisé dans le calcul du hachage.
 * @param m La valeur maximale pour le résultat du hachage.
 * @return Un entier représentant le hachage polynomiale de la chaîne de
 * caractères.
 */
size_t polynomial_rolling_hash(std::string const &s, size_t p, size_t m) {
  size_t hash = 0;
  size_t power = 1;

  for (size_t i = 0; i < s.length(); ++i) {
    hash += (s[i] * power);
    hash %= m;
    power *= p;
  }
  return hash;
}

int main() {
  std::string input;
  size_t max;

  std::cout << "Entrez une chaîne de caractères : ";
  std::getline(std::cin, input);

  std::cout << "Entrez la valeur maximale pour le hachage : ";
  std::cin >> max;
  std::cin.ignore();

  size_t hash_value = folding_string_hash(input, max);
  std::cout << "Le hachage de la chaîne \"" << input
            << "\" est : " << hash_value << std::endl;

  size_t ordered_hash_value = folding_string_ordered_hash(input, max);
  std::cout << "Le hachage ordonné de la chaîne \"" << input
            << "\" est : " << ordered_hash_value << std::endl;

  size_t p = 31;
  std::cout << "Changement du max pour le hachage polynomiale à 1e9 + 9"
            << std::endl;
  max = 1e9 + 9;
  size_t polynomial_hash_value = polynomial_rolling_hash(input, p, max);
  std::cout << "Le hachage polynomiale de la chaîne \"" << input
            << "\" est : " << polynomial_hash_value << std::endl;

  return 0;
}