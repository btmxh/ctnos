#pragma once

#include <ostream>

#include "shape.hpp"

namespace ctn {
struct Circle2 : public Shape<Circle2> {
  Vec2 center;
  float radius;

  Circle2(Vec2 center, float radius);
  Circle2(float x, float y, float radius);

  bool ContainsPoint(Vec2 point) const;

  Circle2 operator+(Vec2 translate) const;
  Circle2 operator-(Vec2 translate) const;
};
}  // namespace ctn

#ifndef NDEBUG
inline std::ostream& operator<<(std::ostream& ostr, const ctn::Circle2& circle) {
  return ostr << "Circle(" << circle.center << ", " << circle.radius << ")";
}
#endif

