#pragma once

#include <functional>
#include <string>

#include "../common/rect.hpp"
#include "../graphics/nanovg.hpp"
#include "input.hpp"
#include "widget_data.hpp"

namespace ctn {
class WindowManager;
class Window;
using WindowID = size_t;

template <typename SELF>
class AbstractWindowBuilder {
 private:
 public:
  AbstractWindowBuilder() {}

  virtual SELF& self() { return static_cast<SELF&>(*this); }

  SELF& SetBounds(const Rect2& bounds) {
    m_bounds = bounds;
    return self();
  }

  SELF& SetTitle(const std::string& title) {
    m_title = title;
    return self();
  }

  SELF& SetDecorated(bool decorated) {
    m_decorated = decorated;
    return self();
  }

  SELF& SetAlwaysOnTop(bool alwaysOnTop) {
    m_alwaysOnTop = alwaysOnTop;
    return self();
  }

 private:
  Rect2 m_bounds = {0.0f, 0.0f, 0.0f, 0.0f};
  std::string m_title = "Window";
  bool m_decorated = true;
  bool m_alwaysOnTop = false;

  friend class Window;
};

class Window {
 public:
  template <typename SELF>
  Window(WindowManager& mgr, WindowID id,
         const AbstractWindowBuilder<SELF>& builder)
      : m_mgr(mgr),
        m_id(id),
        m_title(builder.m_title),
        m_bounds(builder.m_bounds),
        m_alwaysOnTop(builder.m_alwaysOnTop),
        m_decorated(builder.m_decorated) {}

  void RenderWindow(NvgContext& ctx, float delta);
  virtual void RenderContent(NvgContext& ctx, float delta);

 protected:
  WindowManager& m_mgr;
  WindowID m_id;
  Rect2 m_bounds;
  std::string m_title;
  bool m_decorated;
  bool m_alwaysOnTop;

  NvgContext& GetNanoVG();
  Input& GetInput();

  template <typename RenderFunc, typename StateHandleFunc,
            typename = std::enable_if_t<
                std::is_invocable_v<RenderFunc, NvgContext&, const Rect2&,
                                    ButtonData> &&
                std::is_invocable_v<StateHandleFunc, ButtonData>>>
  void Button(const Rect2& bounds, RenderFunc&& render,
              StateHandleFunc&& handleState) {
    ButtonData data{ButtonData::State::NORMAL, false};

    Rect2 inputBounds = bounds + m_bounds.min;

    auto& input = GetInput();
    const auto& lmb = input[vkfw::MouseButton::eLeft];

    bool mouseInBounds = input.cursor.In(m_bounds);
    bool cursorLastPressedInBounds =
        m_bounds.ContainsPoint(lmb->lastPressedCursorPos);
    bool mouseDown = lmb->down;
    bool mouseReleased = lmb.released();

    if (mouseInBounds && cursorLastPressedInBounds) {
      data.state =
          mouseDown ? ButtonData::State::CLICK : ButtonData::State::HOVER;
      data.onAction = mouseReleased;
    }

    handleState(data);
    render(GetNanoVG(), bounds, data);
  }
};
}  // namespace ctn
