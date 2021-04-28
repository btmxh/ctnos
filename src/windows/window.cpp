#include "window.hpp"

void ctn::Window::RenderWindow(NvgContext &ctx, float delta) {
  nvgSave(ctx);

  nvgTranslate(ctx, m_bounds.min.x, m_bounds.min.y);
  nvgScissor(ctx, 0.0f, 0.0f, m_bounds.max.x - m_bounds.min.x,
             m_bounds.max.y - m_bounds.min.y);

  RenderContent(ctx, delta);

  nvgRestore(ctx);
}

void ctn::Window::RenderContent(NvgContext &ctx, float delta) {}

