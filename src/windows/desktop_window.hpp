#pragma once

#include "window.hpp"

namespace ctn {
class DesktopWindowBuilder
    : public AbstractWindowBuilder<DesktopWindowBuilder> {};

class DesktopWindow : public Window {
 public:
  DesktopWindow(WindowManager& mgr, WindowID id,
                const DesktopWindowBuilder& builder);
  ~DesktopWindow();

  void RenderContent(NvgContext& nvg, float delta);

  void ScreenResize(Vec2 newSize);

  // DesktopWindow is a system window, therefore should not be hidden
  void Hide() {}

 private:
  int m_wallpaper;
};
}  // namespace ctn
