#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg.hpp"

ctn::NvgContext::NvgContext() {
#ifndef NDEBUG
  m_ctx = nvgCreateGL3(NVG_DEBUG);
#else
  m_ctx = nvgCreateGL3(0);
#endif
}

ctn::NvgContext::~NvgContext() { nvgDeleteGL3(m_ctx); }

void ctn::NvgContext::Rect(const Rect2 &rect) { Rect(rect.min, rect.max); }

void ctn::NvgContext::Rect(Vec2 min, Vec2 max) {
  nvgRect(m_ctx, min.x, min.y, max.x - min.x, max.y - min.y);
}

void ctn::NvgContext::Circle(const Circle2 &circle) {
  Circle(circle.center, circle.radius);
}

void ctn::NvgContext::Circle(Vec2 center, float radius) {
  nvgCircle(m_ctx, center.x, center.y, radius);
}

void ctn::NvgContext::MoveTo(Vec2 point) { nvgMoveTo(m_ctx, point.x, point.y); }

void ctn::NvgContext::LineTo(Vec2 point) { nvgLineTo(m_ctx, point.x, point.y); }

ctn::NvgContext::operator NVGcontext *() { return m_ctx; }

