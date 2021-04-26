#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg.hpp"

ctn::NvgContext::NvgContext() {
#ifndef NDEBUG
  m_ctx = nvgCreateGL3(NVG_DEBUG);
#else
  m_ctx = nvgCreateGL3(0);
#endif
}

ctn::NvgContext::~NvgContext() { nvgDeleteGL3(m_ctx); }

ctn::NvgContext::operator NVGcontext*() { return m_ctx; }

