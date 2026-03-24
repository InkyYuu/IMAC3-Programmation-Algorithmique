#include <algorithm>
#include <iostream>
#include <vector>
#include <windows.h>

bool is_sorted(std::vector<int> const &vec) {
  return std::is_sorted(vec.begin(), vec.end());
}

void print_vector(std::vector<int> const &vec) {
  std::cout << "[ ";
  for (int i : vec) {
    std::cout << i << " ";
  }
  std::cout << "]" << std::endl;
}

void print_is_sorted(std::vector<int> const &vec, bool print_vec = true) {
  if (print_vec) {
    print_vector(vec);
  }
  if (is_sorted(vec)) {
    std::cout << "Le tableau est trié." << std::endl;
  } else {
    std::cout << "Le tableau n'est pas trié." << std::endl;
  }
}

/* Prototypes */
void selection_sort(std::vector<int> &vec);
void bubble_sort(std::vector<int> &vec);
void insertion_sort(std::vector<int> &vec);

/* Algorithmes de tri */

/***
 * Tri par sélection : on parcourt le tableau à la recherche du minimum, puis on
 * l’échange avec le premier élément. Ensuite, on recommence pour le reste du
 * tableau, etc
 * @param vec : le tableau à trier
 */
void selection_sort(std::vector<int> &vec) {
  int min;
  int N = vec.size();
  for (int i = 0; i < N - 1; i++) {
    min = i;
    for (int j = i + 1; j < N; j++) {
      if (vec[j] < vec[min]) {
        min = j;
      }
    }
    std::swap(vec[i], vec[min]);
  }
}

/***
 * Tri à bulles : on parcourt le tableau et on échange les éléments adjacents
 * s'ils ne sont pas dans l'ordre voulu. On répète ce processus jusqu'à ce que
 * le tableau soit trié.
 * @param vec : le tableau à trier
 */
void bubble_sort(std::vector<int> &vec) {
  int N = vec.size();
  for (int i = 0; i < N - 1; i++) {
    for (int j = 0; j < N - i - 1; j++) {
      if (vec[j] > vec[j + 1]) {
        std::swap(vec[j], vec[j + 1]);
      }
    }
  }
}

/***
 * Tri par insertion : on parcourt le tableau à partir du deuxième élément, et
 * on insère chaque élément à sa place dans la partie déjà triée.
 * @param vec : le tableau à trier
 */
void insertion_sort(std::vector<int> &vec) {
  int N = vec.size();
  for (int i = 1; i < N; i++) {
    int key = vec[i];
    int j = i - 1;
    while (j >= 0 && vec[j] > key) {
      vec[j + 1] = vec[j];
      j--;
    }
    vec[j + 1] = key;
  }
}

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  std::vector<int> vec1 = {5, 2, 9, 1, 5, 6, 3, 4, 7, 8, 0};
  std::vector<int> vec2 = {6, 5, 3, 1, 8, 7, 2, 4, 9, 0, 10};
  std::vector<int> vec3 = {9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 3};
  std::cout << "Tableau 1 avant tri : ";
  print_is_sorted(vec1);
  selection_sort(vec1);
  std::cout << "Tableau 1 après tri par sélection : ";
  print_is_sorted(vec1);
  std::cout << "Tableau 2 avant tri : ";
  print_is_sorted(vec2);
  bubble_sort(vec2);
  std::cout << "Tableau 2 après tri à bulles : ";
  print_is_sorted(vec2);
  std::cout << "Tableau 3 avant tri : ";
  print_is_sorted(vec3);
  insertion_sort(vec3);
  std::cout << "Tableau 3 après tri par insertion : ";
  print_is_sorted(vec3);
  return 0;
}