#include "window.hpp"

#include "../common/circle.hpp"
#include "../game.hpp"

const float ctn::Window::BORDER_SIDE = 2.0f;
const float ctn::Window::BORDER_TOP = 18.0f;
const NVGpaint ctn::Window::BORDER_PAINT =
    ctn::ColorAsPaint(nvgRGBf(0.1f, 0.1f, 0.1f));
const float ctn::Window::TITLE_FONT_SIZE = 12.0f;
const NVGpaint ctn::Window::TITLE_PAINT =
    ctn::ColorAsPaint(nvgRGBf(1.0f, 1.0f, 1.0f));
const float ctn::Window::WIN_BUTTON_RADIUS = 6.0f;
const float ctn::Window::WIN_BUTTON_GAP = 4.0f;
std::map<ctn::ButtonData::State, NVGpaint> ctn::Window::WIN_BUTTON_PAINT = {
    {ctn::ButtonData::State::NORMAL,
     ctn::ColorAsPaint(nvgRGBf(0.3f, 0.3f, 0.3f))},
    {ctn::ButtonData::State::HOVER,
     ctn::ColorAsPaint(nvgRGBf(0.5f, 0.5f, 0.5f))},
    {ctn::ButtonData::State::CLICK,
     ctn::ColorAsPaint(nvgRGBf(0.7f, 0.7f, 0.7f))}};
std::map<ctn::ButtonData::State, NVGpaint>
    ctn::Window::WIN_BUTTON_SYMBOL_PAINT = {
        {ctn::ButtonData::State::NORMAL,
         ctn::ColorAsPaint(nvgRGBf(1.0f, 1.0f, 1.0f))},
        {ctn::ButtonData::State::HOVER,
         ctn::ColorAsPaint(nvgRGBf(1.0f, 1.0f, 1.0f))},
        {ctn::ButtonData::State::CLICK,
         ctn::ColorAsPaint(nvgRGBf(1.0f, 1.0f, 1.0f))},
};

void ctn::Window::RenderWindow(NvgContext& ctx, float delta) {
  if (!m_visible) return;
  nvgSave(ctx);

  nvgTranslate(ctx, m_bounds.min.x, m_bounds.min.y);
  auto bounds = m_bounds - m_bounds.min;
  if (m_decorated) {
    // Border
    {
      Rect2 borderBounds(bounds.min - Vec2(BORDER_SIDE, BORDER_TOP),
                         bounds.max + Vec2(BORDER_SIDE, BORDER_SIDE));

      nvgBeginPath(ctx);

      ctx.Rect(borderBounds);

      ctx.Rect(bounds);
      nvgPathWinding(ctx, NVG_HOLE);

      nvgFillPaint(ctx, BORDER_PAINT);
      nvgFill(ctx);

      nvgClosePath(ctx);
    }

    // Title
    {
      nvgBeginPath(ctx);

      nvgFontFace(ctx, Game::SAN_SERIF_FONT);
      nvgFontSize(ctx, TITLE_FONT_SIZE);
      nvgFillPaint(ctx, TITLE_PAINT);

      nvgTextAlign(ctx, NVG_ALIGN_LEFT | NVG_ALIGN_MIDDLE);

      nvgText(ctx, bounds.min.x, bounds.min.y - BORDER_TOP * 0.5f,
              m_title.c_str(), nullptr);

      nvgClosePath(ctx);
    }

    // Buttons
    {
      Circle2 closeButtonBounds{
          bounds.max.x - WIN_BUTTON_GAP - WIN_BUTTON_RADIUS,
          bounds.min.y - BORDER_TOP * 0.5f, WIN_BUTTON_RADIUS};

      Circle2 minimizeButtonBounds =
          closeButtonBounds -
          Vec2(WIN_BUTTON_GAP + WIN_BUTTON_RADIUS * 2, 0.0f);

      Button(closeButtonBounds,
             [&](NvgContext& nvg, const Circle2& bounds, ButtonData data) {
               nvgBeginPath(nvg);

               nvg.Circle(bounds);
               nvgFillPaint(nvg, WIN_BUTTON_PAINT[data.state]);
               nvgFill(nvg);

               nvgClosePath(nvg);

               nvgBeginPath(nvg);

               nvg.MoveTo(bounds.center - Vec2(0.5f) * bounds.radius);
               nvg.LineTo(bounds.center + Vec2(0.5f) * bounds.radius);

               nvg.MoveTo(bounds.center - Vec2(0.5f, -0.5f) * bounds.radius);
               nvg.LineTo(bounds.center + Vec2(0.5f, -0.5f) * bounds.radius);

               nvgStrokePaint(nvg, WIN_BUTTON_SYMBOL_PAINT[data.state]);
               nvgStrokeWidth(nvg, 1.0f);
               nvgStroke(nvg);

               nvgClosePath(nvg);
               if (data.onAction) {
                 Close();
               }
             });
      Button(minimizeButtonBounds,
             [&](NvgContext& nvg, const Circle2& bounds, ButtonData data) {
               nvgBeginPath(nvg);

               nvg.Circle(bounds);
               nvgFillPaint(nvg, WIN_BUTTON_PAINT[data.state]);
               nvgFill(nvg);

               nvgClosePath(nvg);

               nvgBeginPath(nvg);

               nvg.MoveTo(bounds.center - Vec2(bounds.radius * 0.5f, 0.0f));
               nvg.LineTo(bounds.center + Vec2(bounds.radius * 0.5f, 0.0f));
               nvgStrokePaint(nvg, WIN_BUTTON_SYMBOL_PAINT[data.state]);
               nvgStrokeWidth(nvg, 1.0f);
               nvgStroke(nvg);

               nvgClosePath(nvg);
               if (data.onAction) {
                 Hide();
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
void ctn::Window::Close() { m_shouldClose = true; }

