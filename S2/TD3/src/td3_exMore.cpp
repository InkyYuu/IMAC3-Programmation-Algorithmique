#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>
#include <windows.h>

bool is_sorted(std::vector<int> const &vec) {
  return std::is_sorted(vec.begin(), vec.end());
}

std::vector<int> generate_random_vector(size_t const size,
                                        int const max = 100) {
  std::vector<int> vec(size);
  std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max; });
  return vec;
}

/* Prototype */
void counting_sort(std::vector<int> &vec, int const max);

/* Algorithme de tri */
/**
 * Tri par comptage : on compte le nombre d'occurrences de chaque élément, puis
 * on reconstruit le tableau trié à partir de ces comptes. Cet algorithme est
 * efficace pour les tableaux d'entiers avec une plage de valeurs limitée.
 * @param vec : le tableau d'entier à trier
 * @param max : la valeur maximale dans le tableau
 */
void counting_sort(std::vector<int> &vec, int const max) {
  std::vector<int> count(max + 1, 0);
  for (int num : vec) {
    count[num]++;
  }

  size_t index = 0;
  for (int i = 0; i <= max; i++) {
    while (count[i] > 0) {
      vec[index++] = i;
      count[i]--;
    }
  }
}

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  std::vector<int> vec = generate_random_vector(50);
  int max = 0;

  std::cout << "Tableau avant tri : [ ";
  for (const int element : vec) {
    if (element > max) {
      max = element;
    }
    std::cout << element << " ";
  }
  std::cout << "]" << std::endl;

  counting_sort(vec, max);

  std::cout << "Tableau après tri : [ ";
  for (const int element : vec) {
    std::cout << element << " ";
  }
  std::cout << "]" << std::endl;

  if (is_sorted(vec)) {
    std::cout << "Le tableau est trié." << std::endl;
  } else {
    std::cout << "Le tableau n'est pas trié." << std::endl;
  }

  return 0;
}