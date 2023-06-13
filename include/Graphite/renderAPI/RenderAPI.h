#pragma once

#include <stdint.h>

class RenderAPI {
  public:
    RenderAPI() {}
    ~RenderAPI() {}

    virtual bool update() { return false; }

  public:
    uint32_t width, height;

  private:
    // NONE

  private:
    // NONE
};