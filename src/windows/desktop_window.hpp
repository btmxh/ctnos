#pragma once

#include "window.hpp"

namespace ctn {
class DesktopWindow;

class DesktopWindowBuilder
  : public AbstractWindowBuilder<DesktopWindowBuilder> {
    DesktopWindowBuilder& self() { return *this; }
  };

class DesktopWindow : public Window {
 public:
  DesktopWindow(WindowManager& mgr, WindowID id,
                const DesktopWindowBuilder& builder);

  void RenderContent(NvgContext& nvg, float delta);

 private:
  int m_wallpaper;
};
}  // namespace ctn
