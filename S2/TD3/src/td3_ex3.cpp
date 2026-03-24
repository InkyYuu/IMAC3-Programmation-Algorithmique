#include "ScopedTimer.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
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

/* Prototypes */
void selection_sort(std::vector<int> &vec);
void bubble_sort(std::vector<int> &vec);
void insertion_sort(std::vector<int> &vec);

size_t quick_sort_partition(std::vector<int> &vec, size_t left, size_t right);
void quick_sort(std::vector<int> &vec, size_t const left, size_t const right);
void quick_sort(std::vector<int> &vec) { quick_sort(vec, 0, vec.size() - 1); }

void merge_sort_merge(std::vector<int> &vec, size_t const left,
                      size_t const middle, size_t const right);
void merge_sort(std::vector<int> &vec, size_t const left, size_t const right);
void merge_sort(std::vector<int> &vec) { merge_sort(vec, 0, vec.size() - 1); }

/* Algorithmes de tri */

/**
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

/**
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

/**
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

/**
 * Partitionne le tableau en deux parties : les éléments inférieurs au pivot et
 * les éléments supérieurs au pivot. Le pivot est choisi comme étant le dernier
 * élément du tableau. La fonction retourne l'indice du pivot après
 * partitionnement.
 * @param vec : le tableau à partitionner
 * @param left : l'indice de gauche du tableau à partitionner
 * @param right : l'indice de droite du tableau à partitionner
 */
size_t quick_sort_partition(std::vector<int> &vec, size_t left, size_t right) {
  int index_pivot = left + rand() % (right - left + 1);
  size_t i = left;

  std::swap(vec[index_pivot], vec[left]);
  for (size_t j = left + 1; j <= right; j++) {
    if (vec[j] < vec[left]) {
      std::swap(vec[i + 1], vec[j]);
      i++;
    }
  }
  std::swap(vec[i], vec[left]);
  return i;
}

/***
 * Tri rapide : on choisit un pivot, puis on partitionne le tableau en deux
 * parties : les éléments inférieurs au pivot et les éléments supérieurs au
 * pivot. Ensuite, on trie récursivement les deux parties.
 * @param vec : le tableau à trier
 * @param left : l'indice de gauche du tableau à trier
 * @param right : l'indice de droite du tableau à trier
 */
void quick_sort(std::vector<int> &vec, size_t const left, size_t const right) {
  if (left < right) {
    size_t pivot_index = quick_sort_partition(vec, left, right);
    if (left < pivot_index) {
      quick_sort(vec, left, pivot_index - 1);
    }
    if (pivot_index < right) {
      quick_sort(vec, pivot_index + 1, right);
    }
  }
}

/***
 * Fusionne deux sous-tableaux triés en un seul tableau trié.
 * @param vec : le tableau à fusionner
 * @param left : l'indice de gauche du premier sous-tableau
 * @param middle : l'indice de droite du premier sous-tableau
 * @param right : l'indice de droite du deuxième sous-tableau
 */
void merge_sort_merge(std::vector<int> &vec, size_t const left,
                      size_t const middle, size_t const right) {
  std::vector<int> tmp(right - left + 1);
  size_t i = left;
  size_t j = middle + 1;
  size_t k = 0;

  while (i <= middle && j <= right) {
    tmp[k++] = (vec[i] <= vec[j]) ? vec[i++] : vec[j++];
  }

  while (i <= middle) {
    tmp[k++] = vec[i++];
  }

  while (j <= right) {
    tmp[k++] = vec[j++];
  }

  for (k = 0; k < tmp.size(); k++) {
    vec[left + k] = tmp[k];
  }
}

/***
 * Tri fusion : on divise le tableau en deux parties, on trie récursivement les
 * deux parties, puis on fusionne les deux parties triées.
 * @param vec : le tableau à trier
 * @param left : l'indice de gauche du tableau à trier
 * @param right : l'indice de droite du tableau à trier
 */
void merge_sort(std::vector<int> &vec, size_t const left, size_t const right) {
  if (left < right) {
    size_t middle = (left + right) / 2;
    if (left < middle) {
      merge_sort(vec, left, middle);
    }
    if (middle + 1 < right) {
      merge_sort(vec, middle + 1, right);
    }
    merge_sort_merge(vec, left, middle, right);
  }
}

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif

  {
    std::vector<int> vec = generate_random_vector(10000);
    ScopedTimer timer("Selection sort");
    selection_sort(vec);
  }

  {
    std::vector<int> vec = generate_random_vector(10000);
    ScopedTimer timer("Bubble sort");
    bubble_sort(vec);
  }

  {
    std::vector<int> vec = generate_random_vector(10000);
    ScopedTimer timer("Insertion sort");
    insertion_sort(vec);
  }

  {
    std::vector<int> vec = generate_random_vector(10000);
    ScopedTimer timer("Quick sort");
    quick_sort(vec);
  }

  {
    std::vector<int> vec = generate_random_vector(10000);
    ScopedTimer timer("Merge sort");
    merge_sort(vec);
  }

  {
    std::vector<int> vec = generate_random_vector(10000);
    ScopedTimer timer("Sort bibliothèque standard");
    std::sort(vec.begin(), vec.end());
  }

  std::cout << "Q1 - Que constatez-vous ?" << std::endl;
  std::cout
      << "- Le tri standard (std::sort) est le plus optimisé et le plus rapide."
      << std::endl;
  std::cout << "- Merge sort et Quick sort sont très performants grâce à leur "
               "complexité O(n log n)."
            << std::endl;
  std::cout << "- Insertion sort est plus efficace que Selection sort et "
               "Bubble sort, mais reste lent pour les grandes listes."
            << std::endl;
  std::cout << "- Bubble sort est le moins efficace en raison de sa complexité "
               "O(n²) et de ses nombreux échanges inutiles."
            << std::endl;

  std::cout << "Q2 - Que pouvez-vous en dire ? ?" << std::endl;
  std::cout << "Pour des applications réelles, privilégiez toujours la "
               "fonction std::sort de la bibliothèque standard car optimisée."
            << std::endl;
  std::cout << "Les algorithmes comme Bubble sort ou Selection sort sont à "
               "éviter pour les grandes listes de données."
            << std::endl;
  std::cout << "Merge sort et Quick sort sont utiles pour comprendre les "
               "concepts, mais std::sort reste le meilleur choix en pratique."
            << std::endl;
  std::cout << "Il reste parfois utile de coder son propre tri pour des "
               "besoins spécifiques, mais dans la plupart des cas, "
               "std::sort est largement suffisant."
            << std::endl;
}