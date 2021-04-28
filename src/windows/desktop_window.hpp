#pragma once

#include "window.hpp"

namespace ctn {
class DesktopWindow;

template <>
class WindowBuilder<DesktopWindow> : public WindowBuilder<Window> {};

class DesktopWindow : public Window {
 public:
  DesktopWindow(WindowManager& mgr, WindowID id,
                const WindowBuilder<DesktopWindow>& builder);

  void Render(NvgContext& nvg, float delta);

 private:
  int m_wallpaper;
};
}  // namespace ctn
