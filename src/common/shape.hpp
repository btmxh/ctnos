#pragma once

#include <type_traits>

#include "glm/glm.hpp"

namespace glm {
inline bool operator<(const vec2& v1, const vec2& v2) {
  return v1.x < v2.x && v1.y < v2.y;
}

inline bool operator>(const vec2& v1, const vec2& v2) {
  return v1.x > v2.x && v1.y > v2.y;
}

inline bool operator<=(const vec2& v1, const vec2& v2) {
  return v1.x <= v2.x && v1.y <= v2.y;
}

inline bool operator>=(const vec2& v1, const vec2& v2) {
  return v1.x >= v2.x && v1.y >= v2.y;
}

inline bool operator==(const vec2& v1, const vec2& v2) {
  return v1.x == v2.x && v1.y == v2.y;
}

inline bool operator!=(const vec2& v1, const vec2& v2) { return !(v1 == v2); }
}  // namespace glm

namespace ctn {

using Vec2 = glm::vec2;

template <typename SELF>
class Shape {
  virtual bool ContainsPoint(Vec2 point) const = 0;

  virtual SELF operator+(Vec2 translate) const = 0;
  virtual SELF operator-(Vec2 translate) const = 0;
};

}  // namespace ctn
