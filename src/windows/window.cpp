#include "window.hpp"

#include <iostream>

#include "../common/circle.hpp"
#include "../game.hpp"

const float ctn::Window::BORDER_SIDE = 2.0f;
const float ctn::Window::BORDER_TOP = 18.0f;

void ctn::Window::RenderWindow(NvgContext& ctx, float delta) {
  if (!m_visible) return;
  nvgSave(ctx);

  nvgTranslate(ctx, m_bounds.min.x, m_bounds.min.y);
  auto bounds = m_bounds - m_bounds.min;
  if (m_decorated) {
    // Border
    {
      const NVGcolor color = nvgRGBf(0.1f, 0.1f, 0.1f);
      Rect2 borderBounds(bounds.min - Vec2(BORDER_SIDE, BORDER_TOP),
                         bounds.max + Vec2(BORDER_SIDE, BORDER_SIDE));

      nvgBeginPath(ctx);

      ctx.Rect(borderBounds);

      ctx.Rect(bounds);
      /* nvgPathWinding(ctx, NVG_HOLE); */

      nvgFillColor(ctx, color);
      nvgFill(ctx);

      nvgClosePath(ctx);
    }

    // Title
    {
      const float size = 12.0f;
      nvgBeginPath(ctx);

      nvgFontFace(ctx, Game::SAN_SERIF_FONT);
      nvgFontSize(ctx, size);
      nvgFillColor(ctx, nvgRGBf(1.0f, 1.0f, 1.0f));

      nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);

      nvgText(ctx, bounds.min.x, bounds.min.y - BORDER_TOP * 0.5f,
              m_title.c_str(), nullptr);

      nvgClosePath(ctx);
    }

    // Buttons
    {
      const float gap = 4.0f;
      const float radius = 6.0f;
      Circle2 closeButtonBounds{bounds.max.x - gap - radius,
                                bounds.min.y - BORDER_TOP * 0.5f, radius};

      Circle2 minimizeButtonBounds =
          closeButtonBounds - Vec2(gap + radius * 2, 0.0f);

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
  nvgScissor(ctx, 0.0f, 0.0f, bounds.max.x - bounds.min.x,
             bounds.max.y - bounds.min.y);

  RenderContent(ctx, delta);

  nvgRestore(ctx);
}

void ctn::Window::RenderContent(NvgContext& ctx, float delta) {}

ctn::Rect2 ctn::Window::GetBounds() const { return m_bounds; }
void ctn::Window::ScreenResize(ctn::Vec2 newSize) {}

ctn::NvgContext& ctn::Window::GetNanoVG() { return m_mgr.GetNanoVG(); }
ctn::Input& ctn::Window::GetInput() { return m_mgr.GetInput(); }

void ctn::Window::Hide() { m_visible = false; }
void ctn::Window::Show() { m_visible = true; }
bool ctn::Window::IsVisible() { return m_visible; }

