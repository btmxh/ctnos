#include "window.hpp"

ctn::Window::Window(WindowManager &mgr, WindowID id,
                    const WindowBuilder<Window> &builder)
    : m_mgr(mgr),
      m_id(id),
      m_title(builder.m_title),
      m_bounds(builder.m_bounds),
      m_alwaysOnTop(builder.m_alwaysOnTop),
      m_decorated(builder.m_decorated) {}

void ctn::Window::Render(NvgContext &ctx, float delta) {}

