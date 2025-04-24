#pragma once

#include <glm/vec3.hpp>

// A ray is defined by an origin and a direction
class ray
{
public:
    ~ray() = default;
    ray() = default;
    ray(const glm::vec3& origin, const glm::vec3& direction) : m_origin{origin}, m_direction{direction} {}
    ray(const ray&) = default;
    ray(ray&&) = default;
    ray& operator=(const ray&) = default;
    ray& operator=(ray&&) = default;

    auto origin() const -> glm::vec3 { return m_origin;}
    auto direction() const -> glm::vec3 { return m_direction; }
    auto at(float t) const -> glm::vec3 { return m_origin + t * m_direction; }

private:
    glm::vec3 m_origin = {};
    glm::vec3 m_direction = {};
};