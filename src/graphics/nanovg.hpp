#pragma once

#include "../common/circle.hpp"
#include "../common/rect.hpp"
#include "glad/gl.h"
#include "nanovg.h"

#define NANOVG_GL3 1
#include "nanovg_gl.h"

namespace ctn {
class NvgContext {
 public:
  NvgContext();
  ~NvgContext();

  // Utility functions with Vec2, Rect2, etc.
  void Rect(const Rect2& rect);
  void Rect(Vec2 min, Vec2 max);

  void Circle(const Circle2& circle);
  void Circle(Vec2 center, float radius);

  void MoveTo(Vec2 point);
  void LineTo(Vec2 point);

  operator NVGcontext*();

 private:
  NVGcontext* m_ctx;
};
}  // namespace ctn

