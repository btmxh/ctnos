#include "window.hpp"

#include <iostream>

#include "../common/circle.hpp"
#include "../game.hpp"

void ctn::Window::RenderWindow(NvgContext& ctx, float delta) {
  nvgSave(ctx);

  nvgTranslate(ctx, m_bounds.min.x, m_bounds.min.y);
  if (m_decorated) {
    auto bounds = m_bounds - m_bounds.min;

    // Border
    const float top = 16.0f;
    const float side = 2.0f;
    {
      const NVGcolor color = nvgRGBf(0.1f, 0.1f, 0.1f);
      Rect2 borderBounds(bounds.min - Vec2(side, top),
                         bounds.max + Vec2(side, side));

      nvgBeginPath(ctx);

      ctx.Rect(borderBounds);

      ctx.Rect(m_bounds);
      nvgPathWinding(ctx, NVG_HOLE);

      nvgFillColor(ctx, color);
      nvgFill(ctx);

      nvgClosePath(ctx);
    }

    // Title
    {
      const float size = 12.0f;
      nvgBeginPath(ctx);

      nvgFontFace(ctx, Game::SAN_SERIF_FONT);
      nvgFontSize(ctx, 12.0f);
      nvgFillColor(ctx, nvgRGBf(1.0f, 1.0f, 1.0f));

      nvgText(ctx, bounds.min.x, bounds.min.y - 12.0f, m_title.c_str(),
              nullptr);

      nvgClosePath(ctx);
    }

    // Buttons
    {
      const float gap = 4.0f;
      const float radius = 6.0f;
      Circle2 closeButtonBounds{m_bounds.max.x - gap - radius,
                                m_bounds.min.y - top * 0.5f, radius};

      Circle2 minimizeButtonBounds =
          closeButtonBounds - Vec2(gap + radius, 0.0f);

      Button(closeButtonBounds,
             [&](NvgContext& nvg, const Circle2& bounds, ButtonData data) {
               nvgBeginPath(nvg);

               nvg.Circle(bounds);
               nvgFillColor(nvg, nvgRGBf(1.0f, 0.0f, 1.0f));
               nvgFill(nvg);

               nvgClosePath(nvg);
               if (data.onAction) {
                 std::cout << "cosi" << std::endl;
               }
             });
      Button(minimizeButtonBounds,
             [&](NvgContext& nvg, const Circle2& bounds, ButtonData data) {
               nvgBeginPath(nvg);

               nvg.Circle(bounds);
               nvgFillColor(nvg, nvgRGBf(1.0f, 0.0f, 1.0f));
               nvgFill(nvg);

               nvgClosePath(nvg);
               if (data.onAction) {
                 std::cout << "bunhia" << std::endl;
               }
             });
    }
  }
  nvgScissor(ctx, 0.0f, 0.0f, m_bounds.max.x - m_bounds.min.x,
             m_bounds.max.y - m_bounds.min.y);

  RenderContent(ctx, delta);

  nvgRestore(ctx);
}

void ctn::Window::RenderContent(NvgContext& ctx, float delta) {}

ctn::NvgContext& ctn::Window::GetNanoVG() { return m_mgr.GetNanoVG(); }
ctn::Input& ctn::Window::GetInput() { return m_mgr.GetInput(); }

