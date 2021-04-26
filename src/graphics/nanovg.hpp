#pragma once

#include "nanovg.h"

#include "glad/gl.h"

#define NANOVG_GL3 1
#include "nanovg_gl.h"

namespace ctn {
class NvgContext {
 public:
  NvgContext();
  ~NvgContext();

  operator NVGcontext*();

 private:
  NVGcontext* m_ctx;
};
}  // namespace ctn

