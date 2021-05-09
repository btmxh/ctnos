#include "calc_window.hpp"

ctn::CalculatorWindowBuilder::CalculatorWindowBuilder() {
  SetTitle("Calculator");
}

ctn::CalculatorWindow::CalculatorWindow(WindowManager &mgr, WindowID id,
                                        const CalculatorWindowBuilder &builder)
    : AppWindow(mgr, id, builder) {}

void ctn::CalculatorWindow::RenderContent(NvgContext &nvg, float delta) {
  nvgBeginPath(nvg);
  nvg.Rect({0.0f, 0.0f}, m_bounds.max - m_bounds.min);
  nvgFillColor(nvg, nvgRGBAf(0.0f, 0.0f, 1.0f, 0.5f));
  nvgFill(nvg);
  nvgClosePath(nvg);
}

