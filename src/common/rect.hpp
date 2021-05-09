#pragma once

#include "glm/glm.hpp"
#include "shape.hpp"

namespace ctn {
struct Rect2 : public Shape<Rect2> {
  Vec2 min, max;

  Rect2();
  Rect2(float minX, float minY, float maxX, float maxY);
  Rect2(Vec2 min, Vec2 max);

  bool ContainsPoint(Vec2 point) const;

  bool Intersect(const Rect2& other) const;

  Rect2 Expand(Vec2 amount) const;

  Rect2 operator+(Vec2 translate) const;
  Rect2 operator-(Vec2 translate) const;

  Rect2& operator+=(Vec2 translate);
  Rect2& operator-=(Vec2 translate);
};
}  // namespace ctn

#ifndef NDEBUG
inline std::ostream& operator<<(std::ostream& ostr, const ctn::Rect2& rect) {
  return ostr << "Rect(" << rect.min << ", " << rect.max << ")";
}
#endif

