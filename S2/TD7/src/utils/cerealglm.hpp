#pragma once
#include <cereal/cereal.hpp>
#include <glm/glm.hpp>

// This file provides serialization support for all glm::vec types (vec2, vec3, vec4) using the Cereal library.
namespace glm
{
    template<class Archive, typename T, glm::qualifier Q>
    void serialize(Archive & archive, glm::vec<1, T, Q>& v)
    {
        archive(cereal::make_nvp("x", v.x));
    }

    template<class Archive, typename T, glm::qualifier Q>
    void serialize(Archive & archive, glm::vec<2, T, Q>& v)
    {
        archive(cereal::make_nvp("x", v.x), cereal::make_nvp("y", v.y));
    }

    template<class Archive, typename T, glm::qualifier Q>
    void serialize(Archive & archive, glm::vec<3, T, Q>& v)
    {
        archive(cereal::make_nvp("x", v.x), cereal::make_nvp("y", v.y), cereal::make_nvp("z", v.z));
    }

    template<class Archive, typename T, glm::qualifier Q>
    void serialize(Archive & archive, glm::vec<4, T, Q>& v)
    {
        archive(cereal::make_nvp("x", v.x), cereal::make_nvp("y", v.y), cereal::make_nvp("z", v.z), cereal::make_nvp("w", v.w));
    }

} // namespace glm
