#pragma once

#include "app_window.hpp"

namespace ctn {
class CalculatorWindowBuilder
    : public AppWindowBuilder<CalculatorWindowBuilder> {
 public:
  CalculatorWindowBuilder();
};

class CalculatorWindow : public AppWindow {
 public:
  CalculatorWindow(WindowManager& mgr, WindowID id,
                   const CalculatorWindowBuilder& builder);

  void RenderContent(NvgContext& nvg, float delta);
};
}  // namespace ctn
