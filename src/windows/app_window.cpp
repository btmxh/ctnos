#include "app_window.hpp"

#include "window_manager.hpp"

void ctn::AppWindow::ClampBounds(WindowBoundChange change) {
  auto screenSize = m_mgr.GetSize();

  if (m_decorated) {
    /* make m_bounds temporarily the decorated bounds of this window */
    m_bounds.min -= Vec2(BORDER_SIDE, BORDER_TOP);
    m_bounds.max += Vec2(BORDER_SIDE, BORDER_SIDE);
  }

  switch (change.type) {
    case WindowBoundChangeType::WINDOW_CREATE:
    case WindowBoundChangeType::SCREEN_RESIZE:
      m_bounds.max = glm::min(m_bounds.max, m_bounds.min + screenSize);
    /* intentional fall-through */
    case WindowBoundChangeType::WINDOW_MOVE:
      m_bounds -= glm::max(Vec2(0.0f), m_bounds.max - screenSize);
      break;
    case WindowBoundChangeType::WINDOW_RESIZE:
      if (change.side & WindowBoundChange::SIDE_TOP) {
        m_bounds.min.y =
            glm::clamp(m_bounds.min.y, 0.0f, m_bounds.max.y - m_minimumSize.y);
      } else if (change.side & WindowBoundChange::SIDE_BOTTOM) {
        m_bounds.max.y = glm::clamp(
            m_bounds.max.y, m_bounds.min.y + m_minimumSize.y, screenSize.y);
      }

      if (change.side & WindowBoundChange::SIDE_LEFT) {
        m_bounds.min.x =
            glm::clamp(m_bounds.min.x, 0.0f, m_bounds.max.x - m_minimumSize.x);
      } else if (change.side & WindowBoundChange::SIDE_RIGHT) {
        m_bounds.max.x = glm::clamp(
            m_bounds.max.x, m_bounds.min.x + m_minimumSize.x, screenSize.x);
      }
  }

  if (m_decorated) {
    /* restore m_bounds */
    m_bounds.min += Vec2(BORDER_SIDE, BORDER_TOP);
    m_bounds.max -= Vec2(BORDER_SIDE, BORDER_SIDE);
  }
}

