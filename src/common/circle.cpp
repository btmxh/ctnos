#include "circle.hpp"

ctn::Circle2::Circle2(ctn::Vec2 center, float radius)
    : center(center), radius(radius) {}

ctn::Circle2::Circle2(float x, float y, float radius) : Circle2({x, y}, radius) {}

bool ctn::Circle2::ContainsPoint(Vec2 point) const {
  auto sub = point - center;
  return glm::dot(sub, sub) <= radius;
}

ctn::Circle2 ctn::Circle2::operator+(Vec2 translate) const {
  return {center + translate, radius};
}

ctn::Circle2 ctn::Circle2::operator-(Vec2 translate) const {
  return {center - translate, radius};
}

