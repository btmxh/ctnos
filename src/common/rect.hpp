#pragma once

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

struct Rect2 {
  Vec2 min, max;

  Rect2();
  Rect2(float minX, float minY, float maxX, float maxY);
  Rect2(Vec2 min, Vec2 max);

  bool ContainsPoint(Vec2 point) const;

  bool Intersect(const Rect2& other) const;

  Rect2 Expand(Vec2 amount) const;

  Rect2 operator+(Vec2 translate) const;
};
}  // namespace ctn
