#pragma once

#include <stdint.h>

class RenderAPI {
  public:
    RenderAPI() { throw 1; }
    virtual ~RenderAPI() {}

    virtual bool update() { return false; }

  public:
    uint32_t width, height;

  private:
    // NONE

  private:
    // NONE
};