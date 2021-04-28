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
};
}  // namespace ctn
