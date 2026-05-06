#pragma once

#include <raylib.h>

#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

inline glm::vec2 glm_vec_from(Vector2 const& v) { return { v.x, v.y }; }
inline glm::vec3 glm_vec_from(Vector3 const& v) { return { v.x, v.y, v.z }; }
