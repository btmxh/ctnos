#pragma once

#include "window.hpp"

namespace ctn {
class DesktopWindowBuilder
    : public AbstractWindowBuilder<DesktopWindowBuilder> {};

class DesktopWindow : public Window {
 public:
  DesktopWindow(WindowManager& mgr, WindowID id,
                const DesktopWindowBuilder& builder);

  void RenderContent(NvgContext& nvg, float delta);

  void ScreenResize(Vec2 newSize);

 private:
  int m_wallpaper;
};
}  // namespace ctn
