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
size_t quick_sort_partition(std::vector<int> &vec, size_t left, size_t right);
void quick_sort(std::vector<int> &vec, size_t const left, size_t const right);
void quick_sort(std::vector<int> &vec) { quick_sort(vec, 0, vec.size() - 1); }

void merge_sort_merge(std::vector<int> &vec, size_t const left,
                      size_t const middle, size_t const right);
void merge_sort(std::vector<int> &vec, size_t const left, size_t const right);
void merge_sort(std::vector<int> &vec) { merge_sort(vec, 0, vec.size() - 1); }

/* Algorithmes de tri */

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

/**
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

/**
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

/**
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

  std::vector<int> vec1 = {5, 2, 9, 1, 5, 6, 3, 4, 7, 8, 0, 1};
  std::vector<int> vec2 = {6, 5, 3, 1, 8, 7, 2, 4, 9, 0, 10};
  std::cout << "Tableau 1 avant tri : ";
  print_is_sorted(vec1);
  quick_sort(vec1);
  std::cout << "Tableau 1 après tri rapide : ";
  print_is_sorted(vec1);
  std::cout << "Tableau 2 avant tri : ";
  print_is_sorted(vec2);
  merge_sort(vec2);
  std::cout << "Tableau 2 après tri fusion : ";
  print_is_sorted(vec2);
}