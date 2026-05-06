#pragma once
#include <algorithm>

// Helper for erase remove pattern that work with any container and predicate
template <typename Container, typename Predicate>
void erase_remove_if(Container& container, Predicate predicate) {
    container.erase(std::remove_if(container.begin(), container.end(), predicate), container.end());
}
