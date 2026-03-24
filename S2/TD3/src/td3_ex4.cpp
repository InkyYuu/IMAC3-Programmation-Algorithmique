#include <algorithm>
#include <iostream>
#include <optional>
#include <vector>
#include <windows.h>

std::vector<int> generate_random_vector(size_t const size,
                                        int const max = 100) {
  std::vector<int> vec(size);
  std::generate(vec.begin(), vec.end(), [&max]() { return std::rand() % max; });
  return vec;
}

/* Prototype */
std::optional<int> search(std::vector<int> const &vec, int target);

void print_search_result(std::vector<int> const &vec, int target) {
  std::optional<int> result = search(vec, target);
  if (result.has_value()) {
    std::cout << "L'élément " << target << " a été trouvé à l'indice "
              << result.value() << "." << std::endl;
  } else {
    std::cout << "L'élément " << target
              << " n'a pas été trouvé dans le tableau." << std::endl;
  }
}

/* Algorithme de recherche */

/**
 * Recherche dichotomique : on divise le tableau trié en deux parties, puis on
 * compare l'élément du milieu avec l'élément recherché. On décale l'espace de
 * recherche en fonction du résultat de la comparaison.
 * @param vec : le tableau trié dans lequel chercher
 * @param target : l'élément à rechercher
 */
std::optional<int> search(std::vector<int> const &vec, int target) {
  size_t left = 0;
  size_t right = vec.size() - 1;

  if (vec.empty() || target < vec[left] || target > vec[right]) {
    return std::nullopt;
  }

  while (left <= right) {
    size_t middle = (left + right) / 2;
    if (vec[middle] == target) {
      return middle;
    } else if (vec[middle] < target) {
      left = middle + 1;
    } else {
      right = middle - 1;
    }
  }

  return std::nullopt;
}

int main() {
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
#endif
  std::vector<int> vec = {1, 2, 2, 3, 4, 8, 12};
  print_search_result(vec, 8);
  std::vector<int> vec2 = {1, 2, 3, 3, 6, 14, 12, 15};
  print_search_result(vec2, 15);
  std::vector<int> vec3 = {2, 2, 3, 4, 5, 8, 12, 15, 16};
  print_search_result(vec3, 16);
  std::vector<int> vec4 = {5, 6, 7, 8, 9, 10, 11, 12, 13};
  print_search_result(vec4, 6);
  std::vector<int> vec5 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  print_search_result(vec5, 10);
}