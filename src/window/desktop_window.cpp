#include "desktop_window.hpp"

#include <iostream>

#include "../game.hpp"
#include "window_manager.hpp"

ctn::DesktopWindow::DesktopWindow(WindowManager &mgr, WindowID id,
                                  const WindowBuilder<DesktopWindow> &builder)
    : Window(mgr, id, builder) {
  // TODO: add RAII to this
  m_wallpaper = nvgCreateImage(mgr.GetNanoVG(), "res/wallpaper.png", 0);
}

void ctn::DesktopWindow::Render(NvgContext &nvg, float delta) {
  nvgBeginPath(nvg);

  Vec2 framebufferSize = m_mgr.GetDesktopState().GetGame().GetFramebufferSize();
  auto paint = nvgImagePattern(nvg, 0.0f, 0.0f, framebufferSize.x,
                               framebufferSize.y, 0.0f, m_wallpaper, 1.0f);
  nvgRect(nvg, 0.0f, 0.0f, framebufferSize.x, framebufferSize.y);
  nvgFillPaint(nvg, paint);
  nvgFill(nvg);

  nvgClosePath(nvg);
}

